#ifndef HITBOX_CONTROLLER_HPP
#define HITBOX_CONTROLLER_HPP
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Sprite.hpp"


class HitboxController {
public:
    HitboxController(sf::Sprite *sprite, float width, float height, float offsetX, float offsetY);

    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float x, float y) -> void;

    auto getSize() const -> sf::Vector2f;

    auto getGlobalBounds() const -> sf::FloatRect;

    auto update() -> void;

    auto render(sf::RenderTarget &target) const -> void;

private:
    sf::Sprite *sprite;
    sf::RectangleShape box;
    float offsetX, offsetY;
};


#endif //HITBOX_CONTROLLER_HPP
