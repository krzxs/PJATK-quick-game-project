#include "entity.hpp"

#include "SFML/Graphics/RenderTarget.hpp"


Entity::Entity(sf::Texture &texture, const float hitboxWidth, const float hitboxHeight, const float hitboxOffsetX,
               const float hitboxOffsetY): animationController(AnimationController(&sprite, &texture)),
                                           hitboxController(&sprite, hitboxWidth, hitboxHeight, hitboxOffsetX,
                                                            hitboxOffsetY), alive(true) {
    id = nextId++;
}

auto Entity::getId() const -> unsigned long {
    return id;
}

auto Entity::setTexture(const sf::Texture &texture) -> void {
    sprite.setTexture(texture);
}

auto Entity::getPosition() const -> sf::Vector2f {
    return hitboxController.getPosition();
}

auto Entity::setPosition(const float x, const float y) -> void {
    hitboxController.setPosition(x, y);
}

auto Entity::getCenter() const -> sf::Vector2f {
    return hitboxController.getPosition() + sf::Vector2f(hitboxController.getGlobalBounds().width / 2,
                                                         hitboxController.getGlobalBounds().height / 2);
}

auto Entity::getSize() const -> sf::Vector2f {
    return hitboxController.getSize();
}

auto Entity::render(sf::RenderTarget &target, bool hitbox) const -> void {
    target.draw(sprite);
    if (hitbox) {
        hitboxController.render(target);
    }
}

auto Entity::isAlive() const -> bool {
    return alive;
}
