TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    enemies.cpp \
    game.cpp \
    hud.cpp \
    player.cpp \
    projectiles.cpp \
    weapons.cpp

INCLUDEPATH += C:\SFML\include

LIBS += -LC:/SFML/lib \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-audio \
    -lsfml-network

HEADERS += \
    enemies.h \
    game.h \
    hud.h \
    player.h \
    projectiles.h \
    weapons.h
