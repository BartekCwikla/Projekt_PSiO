TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    axe.cpp \
    axe_projectile.cpp \
    EnemyVortex.cpp \
    animation.cpp \
    audio.cpp \
    boomerang.cpp \
    boomerang_projectile.cpp \
    bullet.cpp \
    double_gun.cpp \
    enemies.cpp \
    enemy_bat.cpp \
    enemy_demon.cpp \
    enemy_ghostgroup.cpp \
    enemyboss.cpp \
    enemyknight.cpp \
    enemyskeleton.cpp \
    exploding_gun.cpp \
    exploding_projectile.cpp \
    exporb.cpp \
    game.cpp \
    gun.cpp \
    hud.cpp \
    map.cpp \
    piercing_gun.cpp \
    player.cpp \
    projectile.cpp \
    quad_gun.cpp \
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
    axe.h \
    axe_projectile.h \
    EnemyVortex.h \
    animation.h \
    audio.h \
    boomerang.h \
    boomerang_projectile.h \
    bullet.h \
    double_gun.h \
    enemies.h \
    enemy_bat.h \
    enemy_demon.h \
    enemy_ghostgroup.h \
    enemyboss.h \
    enemyknight.h \
    enemyskeleton.h \
    exploding_gun.h \
    exploding_projectile.h \
    exporb.h \
    game.h \
    gun.h \
    hud.h \
    map.h \
    piercing_gun.h \
    player.h \
    projectile.h \
    quad_gun.h \
    range.h \
    weapon.h
