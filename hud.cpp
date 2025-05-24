
#include "HUD.h"
#include "player.h"
#include <iostream>
#include <sstream> //To convert variables of class sf::Fonts to ostream

HUD::HUD() {
    //HP and EXP bars color settings. back bars are transparent
    hpBarFront.setFillColor(sf::Color::Red);
    hpBarBack.setFillColor(sf::Color(80, 80, 80, 150));

    expBarFront.setFillColor(sf::Color::Green);
    expBarBack.setFillColor(sf::Color(60, 60, 60,150));



    // Font loading
    if (!font.loadFromFile("./assets/fonts/MinimalPixel.ttf")) {
        std::cerr << "Font MinimalPixel.ttf didn't load!"<<std::endl;
    }

    // HP, EXP, Level text informations settings -  size and color:
    hpText.setFont(font);
    hpText.setCharacterSize(24);
    hpText.setFillColor(sf::Color::White);

    expText.setFont(font);
    expText.setCharacterSize(24);
    expText.setFillColor(sf::Color::White);

    lvlText.setFont(font);
    lvlText.setCharacterSize(24);
    lvlText.setFillColor(sf::Color::White);
}

void HUD::update(const Player& player, const sf::RenderWindow& window) {
    float screenWidth = static_cast<float>(window.getSize().x);
    float screenHeight = static_cast<float>(window.getSize().y);

    float barWidth = screenWidth*0.75f;
    float barHeight = screenHeight*0.01f;
    float spacing = screenHeight*0.018f;


    float xCenter = (screenWidth-barWidth)/2.f;

    // HP Bar
    float hpPercent = player.getHP() / player.getMaxHP();
    float hpY = screenHeight*0.15f;

    //Gray, static bar behind the dynamic red HP bar
    hpBarBack.setSize({barWidth, barHeight});
    hpBarBack.setPosition(xCenter, hpY);

    hpBarFront.setSize({barWidth * hpPercent, barHeight});
    hpBarFront.setPosition(xCenter, hpY);

    // EXP Bar
    float expPercent = player.getExp() / player.getExpNextLvl();
    float expY = hpY + barHeight + spacing;

    //Gray, static bar behind dynamic green EXP bar
    expBarBack.setSize({barWidth, barHeight});
    expBarBack.setPosition(xCenter, expY);

    expBarFront.setSize({barWidth * expPercent, barHeight});
    expBarFront.setPosition(xCenter, expY);

    // HP text information
    std::ostringstream hpStream;
    hpStream << "HP: " << static_cast<int>(player.getHP()) << " / " << static_cast<int>(player.getMaxHP());
    hpText.setString(hpStream.str());
    hpText.setPosition(xCenter, hpY - barHeight * 1.2f);

    // EXP text information
    std::ostringstream expStream;
    expStream << "EXP: " << static_cast<int>(player.getExp()) << " / " << static_cast<int>(player.getExpNextLvl());
    expText.setString(expStream.str());
    expText.setPosition(xCenter, expY - barHeight * 1.2f);

    //Level text information
    float lvlY = expY + barHeight + 10.f;
    std::ostringstream lvlStream;
    lvlStream << "Level: " << static_cast<int>(player.getLvl());
    lvlText.setString(lvlStream.str());
    lvlText.setPosition(xCenter, lvlY);

}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(hpBarBack);
    window.draw(hpBarFront);
    window.draw(expBarBack);
    window.draw(expBarFront);

    window.draw(hpText);
    window.draw(expText);
    window.draw(lvlText);
}
