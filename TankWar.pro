QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bomb.cpp \
    buff.cpp \
    bullet.cpp \
    enemytank.cpp \
    home.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    mytank.cpp \
    stone.cpp \
    tipwidow.cpp \
    tree.cpp \
    wall.cpp \
    you_lose.cpp \
    you_pass_the_game.cpp

HEADERS += \
    bomb.h \
    buff.h \
    bullet.h \
    config.h \
    enemytank.h \
    home.h \
    mainscene.h \
    map.h \
    mytank.h \
    stone.h \
    tipwidow.h \
    tree.h \
    wall.h \
    you_lose.h \
    you_pass_the_game.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
