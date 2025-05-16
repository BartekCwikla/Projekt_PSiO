#include "map.h"

Map::Map() : mapHeight(0), mapWidth(0), tileSize(0) {}

//Map loading method
bool Map::load(const std::string& texturePath, int tile_size, int width, int height) {
    if (!MapTexture.loadFromFile(texturePath))
        return false;

    tileSize = tile_size;
    mapWidth = width;
    mapHeight = height;

    tiles.clear();
    for (int y = 0; y < mapHeight; ++y) {
        for (int x = 0; x < mapWidth; ++x) {
            sf::Sprite tile(MapTexture);
            tile.setPosition(static_cast<float>(x * tileSize), static_cast<float>(y * tileSize));
            tiles.push_back(tile);
        }
    }
    return true;
}

//Map drawing method
void Map::draw(sf::RenderWindow& window) {
    for (const auto& tile : tiles)
        window.draw(tile);

}
