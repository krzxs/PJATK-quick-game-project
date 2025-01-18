#ifndef TILE_HPP
#define TILE_HPP
#include "SFML/Graphics/Sprite.hpp"


class Tile {
public:
    Tile(float x, float y, float size, const sf::Texture &texture, int tileNumber);

    auto render(sf::RenderTarget &target) const -> void;

private:
    sf::Sprite rect;
};


#endif //TILE_HPP
