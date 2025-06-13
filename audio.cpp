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

bool Audio::loadSoundEffect(const std::string& name, const std::string& filepath, float volume, bool loop) {

    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile(filepath)){
        std::cerr<<"Failed to load"<<filepath<<std::endl;
        return false;
    }
    soundBuffers[name]=buffer;
    sf::Sound s;
    s.setBuffer(soundBuffers[name]);
    s.setVolume(volume);
    s.setLoop(loop);
    sounds[name] = SoundSets{s, volume, loop};
    return true;
}
void Audio::playSoundEffect(const std::string& name) {
    if (sounds.count(name)) {
        auto& meta = sounds[name];

        // reset, jeśli już gra
        if (meta.sound.getStatus() == sf::Sound::Playing)
            meta.sound.stop();

        meta.sound.setVolume(meta.defaultVolume);
        meta.sound.setLoop(meta.loop);
        meta.sound.play();
    }
}
