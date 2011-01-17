SOURCEPATH += . \
    ../../../msyncd
    
INCLUDEPATH += /usr/include/iphbd/ \
/usr/include/signon-qt
DEFINES +=  UNIT_TEST
QT += xml \
    dbus
CONFIG += qdbus \
    link_pkgconfig \
    silent \
    mobility

MOBILITY += systeminfo

PKGCONFIG += dbus-1
LIBS += -liphb -lqttracker -lsignon-qt

SOURCES += ServerThread.cpp \
    ServerThreadTest.cpp \
    StorageBookerTest.cpp \
    StorageBooker.cpp \
    SyncQueueTest.cpp \
    SyncQueue.cpp \
    AccountsHelperTest.cpp \
    AccountsHelper.cpp \
    SyncSchedulerTest.cpp \
    SyncScheduler.cpp \
    SyncSession.cpp \
    SyncSessionTest.cpp \
    PluginRunner.cpp \
    ClientThread.cpp \
    ClientThreadTest.cpp\
    TransportTracker.cpp \
    TransportTrackerTest.cpp \
    PluginRunnerTest.cpp \
    ClientPluginRunner.cpp \
    ServerActivator.cpp \
    ServerActivatorTest.cpp \
    ClientPluginRunnerTest.cpp \
    synchronizer.cpp \
    SyncDBusAdaptor.cpp \
    SyncBackupAdaptor.cpp \
    SyncBackup.cpp \
    SyncBackupTest.cpp \
    ServerPluginRunner.cpp \
    ServerPluginRunnerTest.cpp \
    SynchronizerTest.cpp \
    SyncAlarmInventory.cpp \
    IPHeartBeat.cpp \
    NetworkManager.cpp \
    IPHeartBeatTest.cpp \
    SyncSigHandler.cpp \
    SyncSigHandlerTest.cpp

HEADERS += ServerThread.h \
    ServerThreadTest.h \
    StorageBookerTest.h \
    SyncQueueTest.h \
    AccountsHelperTest.h \
    AccountsHelper.h \
    SyncSchedulerTest.h \
    SyncScheduler.h \
    SyncSession.h \
    SyncSessionTest.h \
    PluginRunner.h \
    ClientThread.h \
    ClientThreadTest.h\
    TransportTracker.h \
    TransportTrackerTest.h \
    PluginRunnerTest.h \
    ClientPluginRunner.h \
    ServerActivator.h \
    ServerActivatorTest.h \
    ClientPluginRunnerTest.h \
    synchronizer.h \
    SyncDBusAdaptor.h \
    SyncDBusInterface.h \
    SyncBackupProxy.h \
    SyncBackupAdaptor.h \
    SyncBackup.h \
    SyncBackupTest.h \
    ServerPluginRunner.h \
    ServerPluginRunnerTest.h \
    SyncAlarmInventory.h \
    SynchronizerTest.h \
    IPHeartBeat.h \
    NetworkManager.h \
    IPHeartBeatTest.h \
    SyncSigHandler.h \
    SyncSigHandlerTest.h

OTHER_FILES += 

# for compiling on meego
linux-g++-maemo {
  message("Compiling with USBModed support")
  DEFINES += __USBMODED__
  HEADERS += USBModedProxy.h
  SOURCES += USBModedProxy.cpp
} else {
  message("Compiling without USBModed")
}

