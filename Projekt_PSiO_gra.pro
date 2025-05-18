TEMPLATE = app
CONFIG += console c++17
CONFIG -= qt

SOURCES += main.cpp \
    bullet.cpp \
    enemies.cpp \
    game.cpp \
    gun.cpp \
    hud.cpp \
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
    game.h \
    gun.h \
    hud.h \
    player.h \
    projectile.h \
    range.h \
    weapon.h
