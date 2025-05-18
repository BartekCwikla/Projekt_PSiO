TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    enemies.cpp \
    enemy_demon.cpp \
    game.cpp \
    hud.cpp \
    map.cpp \
    player.cpp \
    projectiles.cpp \
    weapons.cpp

INCLUDEPATH += C:/SFML/include

LIBS += -LC:/SFML/lib \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-audio \
    -lsfml-network

HEADERS += \
    enemies.h \
    enemy_demon.h \
    game.h \
    hud.h \
    map.h \
    player.h \
    projectiles.h \
    weapons.h
