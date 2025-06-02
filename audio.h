#ifndef AUDIO_H
#define AUDIO_H
#include <SFML/Audio.hpp>
#include <map>
#include <string>
class Audio{

private:
sf::Music backgroundMusic;
std::map<std::string, sf::SoundBuffer> soundBuffers; //Stores audio data
std::map<std::string, sf::Sound> sounds; //

public:
Audio();

bool playMusic(const std::string& filepath, float volume = 70.f, bool loop = true);
void stopMusic();

bool loadSoundEffect(const std::string& name, const std::string& filepath);
void playSoundEffect(const std::string& name);
};
#endif // AUDIO_H
