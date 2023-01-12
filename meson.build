project('gpslogger', 'cpp',
    default_options : ['warning_level=3',
                       'cpp_std=c++17',
                       'buildtype=debugoptimized'])

freertos_proj = subproject('freertos')
freertos_includes = freertos_proj.get_variable('freertos_includes')

libsra_proj = subproject('ara-libsra')
libsra_includes = libsra_proj.get_variable('libs_includes')

# transfer to Parrot
freertos_src_list = freertos_proj.get_variable('freertos_src_list')
libfreertos_src_vanilla = freertos_proj.get_variable('libfreertos_src_vanilla')
libsra_ar = libsra_proj.get_variable('libsra_ar')
default_linkerscript = libsra_proj.get_variable('default_linkerscript')

fs = import('fs')

# Python
py3_mod = import('python')
py3_inst = py3_mod.find_installation('python3', modules: [])
if py3_inst.language_version().version_compare('<3.9')
    error('At least Python 3.9 is required.')
endif

## tools
nop = find_program('true')

## llvm dependencies
llvm_version = ['>=14', '<16']
llvm_dep = dependency('llvm', method: 'config-tool', version: llvm_version, include_type: 'system')

llvm_bindir = llvm_dep.get_variable(configtool: 'bindir')
clang = find_program(llvm_bindir / 'clang', version: llvm_version)
llvm_link = find_program(llvm_bindir / 'llvm-link', version: llvm_version)

## ara-link
ara_link = find_program('ara-link', version: llvm_version, required: false)
if not ara_link.found()
    ara_link_proj = subproject('ara-link')
    ara_link = ara_link_proj.get_variable('ara_link')
    message('Using ara-link from subproject.')
endif

## arch specific build tools
if get_option('arch') == 'i386'
    target_triple='x86_64-linux-gnu'
elif get_option('arch') == 'arm'
    target_triple = 'arm-none-eabi'
else
    error('unknown arch ' + get_option('arch'))
endif

foreach prog_name : ['ar', 'ld']
    full_prog_name = target_triple + '-' + prog_name
    prog = find_program(full_prog_name, required: false)
    if not prog.found()
        error(arch_error.format(get_option('arch').to_upper()))
    endif
    set_variable(prog_name, prog)
endforeach

subdir('tools')
subdir('settings')

gpslogger_dir = meson.current_source_dir()
gpslogger_cflags = [
    '-DconfigINCLUDE_ALL_DECLS=1',
    '-DMCU_STM32F103RB',
    '-DSTM32F1',
    '-DSTM32F103RB',
    '-DSTM32F103xB',
    '-DARDUINO=10801',
    '-DF_CPU=72000000L',
    '-DUSE_USB_COMPOSITE',
    '-Wno-deprecated-register',
    '-Wno-unused',
    '-Wno-typedef-redefinition',
    '-DENABLE_ARDUINO_FEATURES=0',
    '-ffast-math',
]


gpslogger_includes = [
    '-I', join_paths([gpslogger_dir, 'Src/']),
    '-I', join_paths([gpslogger_dir, 'Libs/FreeRTOS']),
    '-I', join_paths([gpslogger_dir, 'Libs/arduino']),
    '-I', join_paths([gpslogger_dir, 'Libs/arduino/stm32']),
    '-I', join_paths([gpslogger_dir, 'Libs/NeoGPS']),
    '-I', join_paths([gpslogger_dir, 'Libs/AdafruitGFX']),
    '-I', join_paths([gpslogger_dir, 'Libs/Adafruit_SSD1306']),
    '-I', join_paths([gpslogger_dir, 'Libs/USB']),
    '-I', join_paths([gpslogger_dir, 'Libs/USB/Core']),
    '-I', join_paths([gpslogger_dir, 'Libs/USB/CDC']),
    '-I', join_paths([gpslogger_dir, 'Libs/USB/MSC']),
    '-I', join_paths([gpslogger_dir, 'Libs/USB/MSC_CDC']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/variants/NUCLEO_F103RB']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/system/CMSIS']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/system/STM32F1/HAL_Inc']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/system/STM32F1/CMSIS_Inc']),
    '-I', join_paths([gpslogger_dir, 'Libs/STM32generic/libraries/SPI/src']),
    '-I', join_paths([gpslogger_dir, 'Libs/SdFat']),
] + freertos_includes + libsra_includes


gpslogger_ldflags = [
    '-lm',
    '-lgcc',
    ]

gpslogger_targets = []

gpslogger_compile = generator(clang,
                              output: '@BASENAME@.ll',
                              depfile: '@BASENAME@_dep',
                              arguments: clang_base +
                                         [c_std] +
                                         gpslogger_includes +
                                         ir_flags +
                                         gpslogger_cflags +
                                         clang_flags
                             )

gpslogger_compilepp = generator(clang,
                                output: '@BASENAME@.ll',
                                depfile: '@BASENAME@_dep',
                                arguments: clang_base +
                                           [cxx_std] +
                                           gpslogger_includes +
                                           ir_flags +
                                           gpslogger_cflags +
                                           clang_flags
                               )

subdir('Libs')

src_files = [
    'Src/8x12Font',
    'Src/BoardInit',
    'Src/SDThread',
    'Src/SerialDebugLogger',
    'Src/IdleThread',
    'Src/LEDThread',
    'Src/ButtonsThread',
    'Src/PrintUtils',
    'Src/SdFatSPIDriver',
    'Src/Screens/Screen',
    'Src/Screens/AltitudeScreen',
    'Src/Screens/CurrentPositionScreen',
    'Src/Screens/CurrentTimeScreen',
    'Src/Screens/DebugScreen',
    'Src/Screens/MemDumpScreen',
    'Src/Screens/OdometerScreen',
    'Src/Screens/OdometerActionScreen',
    'Src/Screens/ParentScreen',
    'Src/Screens/SatellitesScreen',
    'Src/Screens/SelectorScreen',
    'Src/Screens/SettingsGroupScreen',
    'Src/Screens/TimeZoneScreen',
    'Src/Screens/ScreenManager',
    'Src/Screens/SpeedScreen',
    'Src/Screens/DisplayDriver',
    'Src/TimeFont',
    'Src/GPS/GPSThread',
    'Src/GPS/GPSDataModel',
    'Src/GPS/GPSOdometer',
    'Src/GPS/GPSSatellitesData',
    'Src/GPSLogger',
    'Src/USBDebugLogger',
]

foreach file : src_files
  gpslogger_targets += gpslogger_compilepp.process(file + '.cpp')
endforeach

gpslogger_application = custom_target('gpslogger_app.ll',
                              input: gpslogger_targets + gpslogger_libs,
                              output: 'gpslogger_app.ll',
                              command: llvm_link_cmd,
                              build_by_default: true
                              )

gpslogger_runtarget = run_target('gpslogger-full',
                                 command: nop,
                                 depends: gpslogger_application)
