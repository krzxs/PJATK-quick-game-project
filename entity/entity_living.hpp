#ifndef ENTITY_LIVING_HPP
#define ENTITY_LIVING_HPP
#include "direction.hpp"
#include "entity.hpp"
#include "movement_controller.hpp"


class EntityLiving : public Entity {
public:
    EntityLiving(sf::Texture &texture, float hitboxWidth, float hitboxHeight, float hitboxOffsetX, float hitboxOffsetY,
                 int maxHealth, Direction direction, float acceleration, float deceleration,
                 float maxVelocity);

    //Movement
    auto getLastPosition() const -> sf::Vector2f;

    auto setLastPosition(sf::Vector2f position) -> void;

    auto getDirection() const -> Direction;

    auto setDirection(Direction direction) -> void;

    auto getLastDirection() const -> Direction;

    auto setLastDirection(Direction direction) -> void;

    auto move(const float &tickDuration) -> void;

    auto stopX() -> void;

    auto stopY() -> void;

    auto stop() -> void;

    //Attributes
    auto getHealth() const -> int;

    auto addHealth(int health) -> void;

    auto removeHealth(int health) -> void;

    auto getMaxHealth() const -> int;

private:
    Direction direction, lastDirection;
    sf::Vector2f lastPosition;
    int health, maxHealth;

protected:
    MovementController movementController;
};


#endif //ENTITY_LIVING_HPP
