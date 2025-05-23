TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    bullet.cpp \
    enemies.cpp \
    enemy_demon.cpp \
    game.cpp \
    gun.cpp \
    hud.cpp \
    map.cpp \
    player.cpp \
    projectile.cpp \
    range.cpp \
    weapon.cpp

INCLUDEPATH += C:/SFML/include

LIBS += -LC:/SFML/lib \
    -lsfml-graphics \
    -lsfml-window \
    -lsfml-system \
    -lsfml-audio \
    -lsfml-network

HEADERS += \
    bullet.h \
    enemies.h \
    enemy_demon.h \
    game.h \
    gun.h \
    hud.h \
    map.h \
    player.h \
    projectile.h \
    range.h \
    weapon.h
