#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Animation {
private:
    std::vector<std::shared_ptr<sf::Texture>> textures;
    std::vector<sf::Sprite> frames;
    float frameTime;
    float timer;
    size_t currentFrame;

public:
    Animation(const std::string& folderPath, const std::string& baseName, int frameCount, float frameDuration, int startIndex=1);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void setPosition(float x, float y);
    void setScale(float x, float y);
    sf::FloatRect getGlobalBounds() const;
    void setFrame(size_t frameInd);
    void setColor(const sf::Color& color);
};

#endif // ANIMATION_H

