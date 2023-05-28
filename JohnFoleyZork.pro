QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
        Character.cpp \
        Command.cpp \
        CommandWords.cpp \
        Parser.cpp \
        Room.cpp \
        ZorkUL.cpp \
        food.cpp \
        item.cpp \
        mainwindow.cpp \
        player.cpp \
        sharedtextbrowser.cpp

HEADERS += \
    Character.h \
    Command.h \
    CommandWords.h \
    Parser.h \
    Room.h \
    ZorkUL.h \
    food.h \
    item.h \
    mainwindow.h \
    player.h \
    sharedtextbrowser.h

FORMS += \
    mainwindow.ui


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
