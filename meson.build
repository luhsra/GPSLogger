project('gpslogger', 'cpp',
    default_options : ['warning_level=3',
                       'cpp_std=c++17',
                       'buildtype=debugoptimized'])

fs = import('fs')

toolchains = subproject('toolchains')
arm_enabled = toolchains.get_variable('arm_enabled')
assert(arm_enabled, 'The GPSLogger can only be build with an ARM toolchain.')

clang = toolchains.get_variable('clang')
llvm_link_cmd = toolchains.get_variable('llvm_link_cmd')
ir_flags = toolchains.get_variable('ir_flags')
clang_base = toolchains.get_variable('clang_base')
cxx_std = toolchains.get_variable('cxx_std')
c_std = toolchains.get_variable('c_std')

libplatforms = subproject('ara-libplatforms')
clang_flags = libplatforms.get_variable('clang_flags')
arm_clang_flags = libplatforms.get_variable('arm_clang_flags')
arm_ld_flags = libplatforms.get_variable('arm_ld_flags')

freertos_proj = subproject('freertos')
freertos_includes = []
foreach dir : freertos_proj.get_variable('header_dirs') + freertos_proj.get_variable('arm_header_dirs')
  freertos_includes += ['-I', dir]
endforeach

libsra_proj = subproject('ara-libsra')
libsra_includes = []
foreach dir : libsra_proj.get_variable('libsra_include_directories')
  libsra_includes += ['-I', dir]
endforeach

gpslogger_cflags = [
  '-mcpu=cortex-m3',
  '-march=armv7-m',
  '-mfloat-abi=soft',
  '-mabi=aapcs',
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


here = meson.current_source_dir()
gpslogger_includes = [
  '-I', here / 'Src/',
  '-I', here / 'Libs/FreeRTOS',
  '-I', here / 'Libs/arduino',
  '-I', here / 'Libs/arduino/stm32',
  '-I', here / 'Libs/NeoGPS',
  '-I', here / 'Libs/AdafruitGFX',
  '-I', here / 'Libs/Adafruit_SSD1306',
  '-I', here / 'Libs/USB',
  '-I', here / 'Libs/USB/Core',
  '-I', here / 'Libs/USB/CDC',
  '-I', here / 'Libs/USB/MSC',
  '-I', here / 'Libs/USB/MSC_CDC',
  '-I', here / 'Libs/STM32generic/',
  '-I', here / 'Libs/STM32generic/variants/NUCLEO_F103RB',
  '-I', here / 'Libs/STM32generic/system/CMSIS',
  '-I', here / 'Libs/STM32generic/system/STM32F1/HAL_Inc',
  '-I', here / 'Libs/STM32generic/system/STM32F1/CMSIS_Inc',
  '-I', here / 'Libs/STM32generic/libraries/SPI/src',
  '-I', here / 'Libs/SdFat',
] + freertos_includes + libsra_includes

gpslogger_compile = generator(clang,
                              output: '@BASENAME@.ll',
                              depfile: '@BASENAME@_dep',
                              arguments: clang_base +
                                         [c_std] +
                                         gpslogger_includes +
                                         ir_flags +
                                         gpslogger_cflags +
                                         clang_flags +
                                         arm_clang_flags +
                                         arm_ld_flags
                             )

gpslogger_compilepp = generator(clang,
                                output: '@BASENAME@.ll',
                                depfile: '@BASENAME@_dep',
                                arguments: clang_base +
                                           [cxx_std] +
                                           gpslogger_includes +
                                           ir_flags +
                                           gpslogger_cflags +
                                           clang_flags +
                                           arm_clang_flags +
                                           arm_ld_flags
                               )


gpslogger_libs = []  # collection of gpslogger_libs (compiled in IR), fill in subdir
subdir('Libs')


subdir('Src')

gpslogger_application = custom_target('gpslogger_app.ll',
  input: gpslogger_targets + gpslogger_libs,
  output: 'gpslogger_app.ll',
  command: llvm_link_cmd,
  build_by_default: true
)

freertos_config = fs.copyfile(freertos_proj.get_variable('default_config'), 'FreeRTOSConfig.h')
