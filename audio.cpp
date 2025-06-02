#include "audio.h"

#include <iostream>

Audio::Audio() {}

bool Audio::playMusic(const std::string& filepath, float volume, bool loop) {
    if (!backgroundMusic.openFromFile(filepath)) {
        return false;
    }
    backgroundMusic.setVolume(volume);
    backgroundMusic.setLoop(loop);
    backgroundMusic.play();
    return true;
}

void Audio::stopMusic() {
    backgroundMusic.stop();
}

bool Audio::loadSoundEffect(const std::string& name, const std::string& filepath) {
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)) {
        std::cerr<<"Cannot loaded the audio file "<<filepath<<std::endl;
        return false;
    }
    soundBuffers[name] = buffer;

    sf::Sound sound;
    sound.setBuffer(soundBuffers[name]);
    sounds[name] = sound;
    return true;
}

void Audio::playSoundEffect(const std::string& name) {
    if (sounds.count(name)) {
        sounds[name].play();
    }
}
