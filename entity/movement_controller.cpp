#include "movement_controller.hpp"

MovementController::MovementController(sf::Sprite &sprite, const float acceleration, const float deceleration,
                                       const float maxVelocity): sprite(sprite),
                                                                 acceleration(acceleration), deceleration(deceleration),
                                                                 maxVelocity(maxVelocity) {
}

auto MovementController::getVelocity() const -> sf::Vector2f {
    return velocity;
}

auto MovementController::getMaxVelocity() const -> float {
    return maxVelocity;
}

auto MovementController::stopX() -> void {
    velocity.x = 0;
}

auto MovementController::stopY() -> void {
    velocity.y = 0;
}

auto MovementController::stop() -> void {
    velocity.x = 0;
    velocity.y = 0;
}

auto MovementController::getState(const unsigned int state) const -> bool {
    switch (state) {
        case IDLE:
            if (velocity.x == 0 && velocity.y == 0) return true;
            break;
        case RUN_UP:
            if (velocity.y < 0) return true;
            break;
        case RUN_DOWN:
            if (velocity.y > 0) return true;
            break;
        case RUN_LEFT:
            if (velocity.x > 0) return true;
            break;
        case RUN_RIGHT:
            if (velocity.x < 0) return true;
            break;
        default:
            return false;
    }
    return false;
}

auto MovementController::move(const Direction direction, const float &tickDuration) -> void {
    const auto dirX = static_cast<float>(direction.getHorizontal());
    const auto dirY = static_cast<float>(direction.getVertical());

    velocity.x += acceleration * dirX * tickDuration;
    velocity.y += acceleration * dirY * tickDuration;
}

auto MovementController::updateMovement(const float &tickDuration) -> void {
    if (velocity.y > 0) {
        if (velocity.y > maxVelocity) velocity.y = maxVelocity;
        if ((velocity.y -= deceleration * tickDuration) < 0) velocity.y = 0;
    } else if (velocity.y < 0) {
        if (velocity.y < -maxVelocity) velocity.y = -maxVelocity;
        if ((velocity.y += deceleration * tickDuration) > 0) velocity.y = 0;
    }
    if (velocity.x < 0) {
        if (velocity.x < -maxVelocity) velocity.x = -maxVelocity;
        if ((velocity.x += deceleration * tickDuration) > 0) velocity.x = 0;
    } else if (velocity.x > 0) {
        if (velocity.x > maxVelocity) velocity.x = maxVelocity;
        if ((velocity.x -= deceleration * tickDuration) < 0) velocity.x = 0;
    }
    sprite.move(velocity * tickDuration);
}
