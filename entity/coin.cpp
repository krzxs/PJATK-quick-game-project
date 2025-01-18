#include "coin.hpp"

auto Coin::initAnimations() -> void {
    animationController.addAnimation("IDLE", 8, 0, 0, 9, 1, 20, 20);
}

Coin::Coin(const float x, const float y, sf::Texture &texture): Entity(texture, 40, 40, 10, 10) {
    Coin::initAnimations();
    sprite.setScale(3.f, 3.f);

    setPosition(x, y);
}

auto Coin::updateAnimation(const float &tickDuration) -> void {
    animationController.play("IDLE", tickDuration);
}

auto Coin::update(const float &tickDuration) -> void {
    updateAnimation(tickDuration);
    hitboxController.update();
}

auto Coin::checkCollision(Entity &second) const -> bool  {
    return false;
}

auto Coin::onCollision(Entity &second) -> void {
}

auto Coin::die() -> void {
    alive = false;
}
