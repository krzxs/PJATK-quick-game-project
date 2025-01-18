#include "entity_living.hpp"

EntityLiving::EntityLiving(sf::Texture &texture, const float hitboxWidth, const float hitboxHeight,
                           const float hitboxOffsetX,
                           const float hitboxOffsetY, const int maxHealth,
                           const Direction direction, const float acceleration, const float deceleration,
                           const float maxVelocity) : Entity(texture, hitboxWidth, hitboxHeight, hitboxOffsetX,
                                                             hitboxOffsetY),
                                                      direction(direction),
                                                      lastDirection(Direction()),
                                                      maxHealth(maxHealth),
                                                      movementController(
                                                          sprite, acceleration, deceleration, maxVelocity) {
    health = maxHealth;
}

auto EntityLiving::getLastPosition() const -> sf::Vector2f {
    return lastPosition;
}

auto EntityLiving::setLastPosition(const sf::Vector2f position) -> void {
    lastPosition = position;
}

auto EntityLiving::getDirection() const -> Direction {
    return direction;
}

void EntityLiving::setDirection(const Direction direction) {
    this->direction = direction;
}

auto EntityLiving::getLastDirection() const -> Direction {
    return lastDirection;
}

void EntityLiving::setLastDirection(const Direction direction) {
    lastDirection = direction;
}

auto EntityLiving::move(const float &tickDuration) -> void {
    movementController.move(direction, tickDuration);
}

auto EntityLiving::stopX() -> void {
    movementController.stopX();
}

auto EntityLiving::stopY() -> void {
    movementController.stopY();
}

auto EntityLiving::stop() -> void {
    movementController.stop();
}

auto EntityLiving::getHealth() const -> int {
    return health;
}

auto EntityLiving::addHealth(const int health) -> void {
    if (const int temp = this->health + health; temp > maxHealth) {
        this->health = maxHealth;
    } else {
        this->health = temp;
    }
}

auto EntityLiving::removeHealth(const int health) -> void {
    if (const int temp = this->health - health; temp < 0) {
        this->health = 0;
    } else {
        this->health = temp;
    }
}

auto EntityLiving::getMaxHealth() const -> int {
    return maxHealth;
}
