#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <vector>
class Map
{
private:
    sf::Texture MapTexture;
    std::vector<sf::Sprite> tiles;
    int tileSize;
    int mapHeight, mapWidth;
public:
    Map();
    bool load(const std::string& texturePath, int tile_size, int width, int height);
    void draw(sf::RenderWindow& window);
};

#endif // MAP_H
