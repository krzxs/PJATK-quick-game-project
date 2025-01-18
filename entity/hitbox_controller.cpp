#include "hitbox_controller.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

HitboxController::HitboxController(sf::Sprite *sprite, float width, float height, float offsetX,
                                   float offsetY): sprite(sprite),
                                                   box(sf::RectangleShape(sf::Vector2f(width, height))),
                                                   offsetX(offsetX),
                                                   offsetY(offsetY) {
    box.setOutlineColor(sf::Color::Red);
    box.setOutlineThickness(-1.f);
    box.setFillColor(sf::Color::Transparent);
    update();
}

auto HitboxController::getPosition() const -> sf::Vector2f {
    return box.getPosition();
}

auto HitboxController::setPosition(const float x, const float y) -> void {
    sprite->setPosition(x - offsetX, y - offsetY);
    box.setPosition(x, y);
}

auto HitboxController::getSize() const -> sf::Vector2f {
    return box.getSize();
}

auto HitboxController::getGlobalBounds() const -> sf::FloatRect {
    return box.getGlobalBounds();
}

auto HitboxController::update() -> void {
    box.setPosition(sprite->getPosition().x + offsetX, sprite->getPosition().y + offsetY);
}

auto HitboxController::render(sf::RenderTarget &target) const -> void {
    target.draw(box);
}
