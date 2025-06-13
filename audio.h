#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

//Response to sets
struct SoundSets {
    sf::Sound sound;
    float defaultVolume;
    bool loop;
};





class Audio{

private:
sf::Music backgroundMusic;
std::map<std::string, sf::SoundBuffer> soundBuffers; //Stores audio data
std::map<std::string, SoundSets> sounds;
float volume;

public:
Audio();

bool playMusic(const std::string& filepath, float volume, bool loop = true);
void stopMusic();

bool loadSoundEffect(const std::string& name, const std::string& filepath, float volume, bool loop);
void playSoundEffect(const std::string& name);
void cleanupStoppedSounds();
};
#endif // AUDIO_H
