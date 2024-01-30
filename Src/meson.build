src_files = files(
    '8x12Font.cpp',
    'BoardInit.cpp',
    'SDThread.cpp',
    'SerialDebugLogger.cpp',
    'IdleThread.cpp',
    'LEDThread.cpp',
    'ButtonsThread.cpp',
    'PrintUtils.cpp',
    'SdFatSPIDriver.cpp',
    'Screens/Screen.cpp',
    'Screens/AltitudeScreen.cpp',
    'Screens/CurrentPositionScreen.cpp',
    'Screens/CurrentTimeScreen.cpp',
    'Screens/DebugScreen.cpp',
    'Screens/MemDumpScreen.cpp',
    'Screens/OdometerScreen.cpp',
    'Screens/OdometerActionScreen.cpp',
    'Screens/ParentScreen.cpp',
    'Screens/SatellitesScreen.cpp',
    'Screens/SelectorScreen.cpp',
    'Screens/SettingsGroupScreen.cpp',
    'Screens/TimeZoneScreen.cpp',
    'Screens/ScreenManager.cpp',
    'Screens/SpeedScreen.cpp',
    'Screens/DisplayDriver.cpp',
    'TimeFont.cpp',
    'GPS/GPSThread.cpp',
    'GPS/GPSDataModel.cpp',
    'GPS/GPSOdometer.cpp',
    'GPS/GPSSatellitesData.cpp',
    'GPSLogger.cpp',
    'USBDebugLogger.cpp',
)

gpslogger_targets = []
foreach file : src_files
  gpslogger_targets += gpslogger_compilepp.process(file)
endforeach
