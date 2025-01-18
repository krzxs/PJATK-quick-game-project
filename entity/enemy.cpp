#include "enemy.hpp"

#include "ball.hpp"
#include "fmt/ostream.h"

auto Enemy::initAnimations() -> void {
    animationController.addAnimation("IDLE", 15, 0, 0, 4, 1, 48, 48);
    animationController.addAnimation("RUN_LEFT", 11, 0, 1, 8, 2, 48, 48);
    animationController.addAnimation("RUN_RIGHT", 11, 0, 2, 8, 3, 48, 48);
    animationController.addAnimation("RUN_UP", 11, 0, 3, 8, 4, 48, 48);
    animationController.addAnimation("RUN_DOWN", 11, 0, 4, 8, 5, 48, 48);
}

Enemy::Enemy(const float x, const float y, EntityLiving &toFollow, float maxHealth, sf::Texture &texture) : EntityLiving(
        texture, 120, 128, 8, 8, maxHealth,
        Direction(WEST, UNKNOWN_VERTICAL), 2000.f,
        1000.f, 100.f), onCooldown(false), followComponent(*this, toFollow) {
    Enemy::initAnimations();
    sprite.setScale(3.f, 3.f);

    setPosition(x, y);
}

auto Enemy::update(const float &tickDuration) -> void {
    updateAnimation(tickDuration);
    hitboxController.update();
    followComponent.update(tickDuration);
    movementController.updateMovement(tickDuration);
}

auto Enemy::checkCollision(Entity &second) const -> bool {
    const auto currentPosition = getPosition();
    const auto currentSize = getSize();
    const auto secondPosition = second.getPosition();
    const auto secondSize = second.getSize();
    if (second.is<Ball>()) {
        return secondPosition.x >= currentPosition.x &&
               secondPosition.x + secondSize.x <= currentPosition.x + currentSize.x &&
               secondPosition.y >= currentPosition.y
               && secondPosition.y + secondSize.y <= currentPosition.y + currentSize.y;
    }
    return false;
}

auto Enemy::onCollision(Entity &second) -> void {
    if (second.is<Ball>()) {
        removeHealth(50);
        second.die();
        if (getHealth() <= 0) die();
    }
}

auto Enemy::die() -> void {
    alive = false;
}

auto Enemy::getCooldownClock() const -> sf::Clock {
    return cooldownTimer;
}

auto Enemy::restartCooldown() -> void {
    cooldownTimer.restart();
}

auto Enemy::isOnCooldown() const -> bool {
    return onCooldown;
}

auto Enemy::setOnCooldown(const bool onCooldown) -> void {
    this->onCooldown = onCooldown;
}

auto Enemy::updateAnimation(const float &tickDuration) -> void {
    if (movementController.getState(IDLE)) {
        animationController.play("IDLE", tickDuration);
    } else if (movementController.getState(RUN_UP)) {
        animationController.play("RUN_UP", tickDuration);
    } else if (movementController.getState(RUN_DOWN)) {
        animationController.play("RUN_DOWN", tickDuration);
    } else if (movementController.getState(RUN_LEFT)) {
        animationController.play("RUN_LEFT", tickDuration);
    } else if (movementController.getState(RUN_RIGHT)) {
        animationController.play("RUN_RIGHT", tickDuration);
    }
}
