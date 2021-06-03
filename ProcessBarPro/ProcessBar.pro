QT += core gui widgets

CONFIG += c++11

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    processbar.cpp

HEADERS += \
    mainwindow.h \
    processbar.h

FORMS += \
    mainwindow.ui

TRANSLATIONS = chinese.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    rc.qrc
