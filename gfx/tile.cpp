#include "tile.hpp"

#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/Graphics/Text.hpp"

Tile::Tile(const float x, const float y, const float size, const sf::Texture &texture, int tileNumber) {
    rect.setTexture(texture);
    rect.setPosition(x, y);
    rect.setTextureRect(sf::IntRect(tileNumber * size, 0, size, size));
}

auto Tile::render(sf::RenderTarget &target) const -> void {
    target.draw(rect);
}
