QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win32:RC_ICONS += appIcon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    explorer.cpp \
    folder.cpp \
    main.cpp \
    mainwindow.cpp \
    namefile.cpp

HEADERS += \
    explorer.h \
    folder.h \
    mainwindow.h \
    namefile.h

FORMS += \
    explorer.ui \
    folder.ui \
    mainwindow.ui \
    namefile.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    source.qrc
