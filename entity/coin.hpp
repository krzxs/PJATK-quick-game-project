#ifndef COIN_HPP
#define COIN_HPP
#include "collidable.hpp"
#include "entity.hpp"


class Coin final : public Entity, public Collidable {
public:
    Coin(float x, float y, sf::Texture &texture);

    auto update(const float &tickDuration) -> void override;

    auto checkCollision(Entity &second) const -> bool override;

    auto onCollision(Entity &second) -> void override;

    auto die() -> void override;

private:
    auto updateAnimation(const float &tickDuration) -> void override;

    auto initAnimations() -> void override;
};


#endif //COIN_HPP
