TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    animation.cpp \
    bullet.cpp \
    double_gun.cpp \
    enemies.cpp \
    enemy_bat.cpp \
    enemy_demon.cpp \
    enemy_ghostgroup.cpp \
    enemyboss.cpp \
    exploding_gun.cpp \
    exploding_projectile.cpp \
    exporb.cpp \
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
    animation.h \
    bullet.h \
    double_gun.h \
    enemies.h \
    enemy_bat.h \
    enemy_demon.h \
    enemy_ghostgroup.h \
    enemyboss.h \
    exploding_gun.h \
    exploding_projectile.h \
    exporb.h \
    game.h \
    gun.h \
    hud.h \
    map.h \
    player.h \
    projectile.h \
    range.h \
    weapon.h
