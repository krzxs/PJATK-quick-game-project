#include "player.hpp"

#include "coin.hpp"
#include "enemy_ball.hpp"
#include "fmt/ostream.h"
#include "SFML/Graphics/RenderTarget.hpp"

auto Player::initAnimations() -> void {
    animationController.addAnimation("IDLE", 15, 0, 0, 4, 1, 48, 48);
    animationController.addAnimation("RUN_LEFT", 11, 0, 1, 8, 2, 48, 48);
    animationController.addAnimation("RUN_RIGHT", 11, 0, 2, 8, 3, 48, 48);
    animationController.addAnimation("RUN_UP", 11, 0, 3, 8, 4, 48, 48);
    animationController.addAnimation("RUN_DOWN", 11, 0, 4, 8, 5, 48, 48);
}

Player::Player(const float x, const float y, sf::Texture &texture): EntityLiving(
                                                                        texture, 120, 128, 8, 8, 100,
                                                                        Direction(WEST, UNKNOWN_VERTICAL), 4000.f,
                                                                        3000.f, 300.f),
                                                                    coins(0), onCooldown(false) {
    Player::initAnimations();
    sprite.setScale(3.f, 3.f);

    setPosition(x, y);
}

auto Player::getCoins() const -> unsigned int {
    return coins;
}

auto Player::addCoins(const unsigned int coins) -> void {
    if (this->coins + coins > 999) {
        this->coins = 999;
    } else {
        this->coins += coins;
    }
}

auto Player::removeCoins(const unsigned int coins) -> bool {
    if (this->coins - coins < 0) {
        return false;
    }
    this->coins -= coins;
    return true;
}

auto Player::updateAnimation(const float &tickDuration) -> void {
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

auto Player::update(const float &tickDuration) -> void {
    auto nextPosition = movementController.getVelocity() * tickDuration + getPosition();

    if (nextPosition.x >= 0 && nextPosition.x <= 1600 - getSize().x &&
        nextPosition.y >= 0 && nextPosition.y <= 900 - getSize().y) {
        movementController.updateMovement(tickDuration);
    } else {
        stop();
    }
    updateAnimation(tickDuration);
    hitboxController.update();
}

auto Player::checkCollision(Entity &second) const -> bool {
    const auto currentPosition = getPosition();
    const auto currentSize = getSize();
    const auto secondPosition = second.getPosition();
    const auto secondSize = second.getSize();
    if (second.is<Coin>()) {
        return secondPosition.x >= currentPosition.x &&
               secondPosition.x + secondSize.x <= currentPosition.x + currentSize.x &&
               secondPosition.y >= currentPosition.y
               && secondPosition.y + secondSize.y <= currentPosition.y + currentSize.y;
    }
    if (second.is<EnemyBall>()) {
        return secondPosition.x >= currentPosition.x &&
               secondPosition.x + secondSize.x <= currentPosition.x + currentSize.x &&
               secondPosition.y >= currentPosition.y
               && secondPosition.y + secondSize.y <= currentPosition.y + currentSize.y;
    }
    return false;
}

auto Player::onCollision(Entity &second) -> void {
    if (second.is<Coin>()) {
        addCoins(1);
        second.die();
    }
    if (second.is<EnemyBall>()) {
        removeHealth(25);
        second.die();
    }
}

auto Player::die() -> void {
    alive = false;
}

auto Player::getCooldownClock() const -> sf::Clock {
    return cooldownTimer;
}

auto Player::restartCooldown() -> void {
    cooldownTimer.restart();
}

auto Player::isOnCooldown() const -> bool {
    return onCooldown;
}

auto Player::setOnCooldown(const bool onCooldown) -> void {
    this->onCooldown = onCooldown;
}
