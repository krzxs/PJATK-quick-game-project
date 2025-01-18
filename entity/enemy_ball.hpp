#ifndef ENEMY_BALL_HPP
#define ENEMY_BALL_HPP
#include "entity_living.hpp"


class EnemyBall final : public EntityLiving {
public:
    EnemyBall(float x, float y, sf::Texture &texture, Direction direction);

    auto update(const float &tickDuration) -> void override;

    auto die() -> void override;

private:
    auto updateAnimation(const float &tickDuration) -> void override;

    auto initAnimations() -> void override;
};


#endif //ENEMY_BALL_HPP
