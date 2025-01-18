#ifndef BALL_HPP
#define BALL_HPP
#include "collidable.hpp"
#include "entity_living.hpp"


class Ball final : public EntityLiving {
public:
    Ball(float x, float y, sf::Texture &texture, Direction direction);

    auto update(const float &tickDuration) -> void override;

    auto die() -> void override;

private:
    auto updateAnimation(const float &tickDuration) -> void override;

    auto initAnimations() -> void override;
};


#endif //BALL_HPP
