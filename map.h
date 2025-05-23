#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
class Map
{
private:
    sf::Texture MapTexture;
    std::vector<sf::Sprite> tiles;
    sf::FloatRect mapBounds;
    int tileSize;
    int mapHeight;
    int mapWidth;
public:
    Map();
    bool load(const std::string& texturePath, int tile_size, int width, int height);
    void draw(sf::RenderWindow& window);
    sf::Vector2f getSize() const;
    sf::FloatRect getBounds() const;
   // sf::Vector2f getCenter() const;
};

#endif // MAP_H
