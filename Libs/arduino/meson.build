src_files= [
  'abi.cpp',
  'Print.cpp',
  'Stream.cpp',
  # 'WString.cpp',
]

c_src_files = [
  # 'dtostrf.c',
  'stm32/stm32_init.c'
]

libarduino_targets = []
foreach file : src_files
  libarduino_targets += gpslogger_compilepp.process(file)
endforeach

foreach file : c_src_files
  libarduino_targets += gpslogger_compile.process(file)
endforeach


libarduino = custom_target('libarduino-link',
                           input: libarduino_targets,
                           output: 'libarduino.ll',
                           command: llvm_link_cmd
                          )

gpslogger_libs += libarduino
