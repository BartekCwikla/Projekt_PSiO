#include "waves.h"
#include <sstream>
#include <iostream>

Waves::Waves() {
    if(!font.loadFromFile("assets/fonts/MinimalPixel.ttf")){
        std::cerr<<"Font didn't load!!!"<<std::endl;
    }


    waveText.setFont(font);
    waveText.setCharacterSize(24);
    waveText.setFillColor(sf::Color::White);


    timerText.setFont(font);
    timerText.setCharacterSize(30);
    timerText.setFillColor(sf::Color::White);
    timerText.setPosition(20.f, 60.f);
}

void Waves::update(const sf::RenderWindow& window) {
    float elapsedTime = gameClock.getElapsedTime().asSeconds();
    float waveTime_ = waveClock.getElapsedTime().asSeconds();

    // Wave counter text
    std::stringstream ss;
    ss<<"Wave: "<< currentWave;
    waveText.setString(ss.str());

    // Timer text
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;
    std::stringstream tt;
    tt<<minutes<<":"<<(seconds < 10 ? "0" : "")<<seconds;
    timerText.setString(tt.str());


    float screenWidth = static_cast<float>(window.getSize().x);

    //Setting timer and wave counter text messages positions
    float timeY = window.getSize().y*0.2f ;
    float waveY = timeY+30.f;

    waveText.setPosition(screenWidth *0.125f, waveY);
    timerText.setPosition((screenWidth - timerText.getLocalBounds().width)/2.f, timeY);

    // Obsługa końca fali
    if (waveTime_ >=this->waveTime) {
        waveActive=false;
    }
}
void Waves::draw(sf::RenderWindow& window) {

    window.draw(timerText);
    window.draw(waveText);
}

bool Waves::isNewWaveReady() const {
    return !waveActive;
}

void Waves::nextWave() {
    currentWave++;
    if(currentWave % 3 == 0){
        waveTime=std::max(20.f, waveTime - 5.f); // minimal duration = 20s
        enemyHP+=10.f;
        enemyDamage+=2.f;
    }
    enemiesToSpawn+=5;
    waveActive=true;
    waveClock.restart();
}

int Waves::getEnemiesToSpawn() const {
    return enemiesToSpawn;
}

float Waves::getEnemyHP() const {
    return enemyHP;
}

float Waves::getEnemyDamage() const {
    return enemyDamage;
}

int Waves::getCurrentWave() const {
    return currentWave;
}
