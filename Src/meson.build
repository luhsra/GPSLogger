src_files = files(
    '8x12Font.cpp',
    'BoardInit.cpp',
    'ButtonsThread.cpp',
    'GPS/GPSDataModel.cpp',
    'GPS/GPSOdometer.cpp',
    'GPS/GPSSatellitesData.cpp',
    'GPS/GPSThread.cpp',
    'GPSLogger.cpp',
    'IdleThread.cpp',
    'LEDThread.cpp',
    'PrintUtils.cpp',
    'Screens/AltitudeScreen.cpp',
    'Screens/CurrentPositionScreen.cpp',
    'Screens/CurrentTimeScreen.cpp',
    'Screens/DebugScreen.cpp',
    'Screens/DisplayDriver.cpp',
    'Screens/MemDumpScreen.cpp',
    'Screens/OdometerActionScreen.cpp',
    'Screens/OdometerScreen.cpp',
    'Screens/ParentScreen.cpp',
    'Screens/SatellitesScreen.cpp',
    'Screens/Screen.cpp',
    'Screens/ScreenManager.cpp',
    'Screens/SelectorScreen.cpp',
    'Screens/SettingsGroupScreen.cpp',
    'Screens/SpeedScreen.cpp',
    'Screens/TimeZoneScreen.cpp',
    'SdFatSPIDriver.cpp',
    # 'SdMscDriver.cpp',
    'SDThread.cpp',
    'SerialDebugLogger.cpp',
    'TimeFont.cpp',)
    # 'USBDebugLogger.cpp',)

gpslogger_targets = []
foreach file : src_files
  gpslogger_targets += gpslogger_compilepp.process(file)
endforeach
