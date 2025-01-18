#ifndef ENEMY_HPP
#define ENEMY_HPP
#include "collidable.hpp"
#include "entity_living.hpp"
#include "follow_component.hpp"
#include "SFML/System/Clock.hpp"


class Enemy : public EntityLiving, public Collidable {
public:
    Enemy(float x, float y, EntityLiving &toFollow, float maxHealth, sf::Texture &texture);

    auto update(const float &tickDuration) -> void override;

    auto checkCollision(Entity &second) const -> bool override;

    auto onCollision(Entity &second) -> void override;

    auto attack() -> void;

    auto die() -> void override;

    auto getCooldownClock() const -> sf::Clock;

    auto restartCooldown() -> void;

    auto isOnCooldown() const -> bool;

    auto setOnCooldown(bool onCooldown) -> void;

private:
    auto updateAnimation(const float &tickDuration) -> void override;

    auto initAnimations() -> void override;

    bool onCooldown;
    sf::Clock cooldownTimer;

protected:
    FollowComponent followComponent;
};


#endif //ENEMY_HPP
