#include "ball.hpp"

auto Ball::initAnimations() -> void {
    animationController.addAnimation("RUN_UP", 10, 0, 0, 4, 1, 64, 64);
    animationController.addAnimation("RUN_DOWN", 10, 0, 1, 4, 2, 64, 64);
    animationController.addAnimation("RUN_LEFT", 10, 0, 2, 4, 3, 64, 64);
    animationController.addAnimation("RUN_RIGHT", 10, 0, 3, 4, 4, 64, 64);
}

Ball::Ball(const float x, const float y, sf::Texture &texture, const Direction direction): EntityLiving(
    texture, 22, 21, 21, 22, 1,
    direction, 10000000.f,
    0, 800.f) {
    Ball::initAnimations();

    setPosition(x, y);
}

auto Ball::update(const float &tickDuration) -> void {
    if (getPosition().x > 2000 || getPosition().x < -400 || getPosition().y > 1300 || getPosition().y < -400) {
        die();
    }
    if (alive) {
        move(tickDuration);
        movementController.updateMovement(tickDuration);
        updateAnimation(tickDuration);
        hitboxController.update();
    }
}

auto Ball::die() -> void {
    alive = false;
}


auto Ball::updateAnimation(const float &tickDuration) -> void {
    if (movementController.getState(RUN_UP)) {
        animationController.play("RUN_UP", tickDuration);
    } else if (movementController.getState(RUN_DOWN)) {
        animationController.play("RUN_DOWN", tickDuration);
    } else if (movementController.getState(RUN_LEFT)) {
        animationController.play("RUN_LEFT", tickDuration);
    } else if (movementController.getState(RUN_RIGHT)) {
        animationController.play("RUN_RIGHT", tickDuration);
    }
}
