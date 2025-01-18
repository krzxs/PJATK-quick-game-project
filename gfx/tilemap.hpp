#ifndef TILEMAP_HPP
#define TILEMAP_HPP
#include <string>
#include <vector>

#include "tile.hpp"
#include "SFML/Graphics/Texture.hpp"


class Tilemap {
public:
    Tilemap(float tileSize, const sf::Texture &texture);

    auto loadFromFile(const std::string &path) -> bool;

    auto render(sf::RenderTarget &target) const -> void;

private:
    sf::Texture texture;
    std::vector<Tile> tiles;
    unsigned int rows, cols;
    float tileSize;
};


#endif //TILEMAP_HPP
