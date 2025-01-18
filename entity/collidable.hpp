#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP
#include "entity.hpp"


class Collidable {
public:
    virtual ~Collidable() = default;

    virtual bool checkCollision(Entity &second) const = 0;

    virtual void onCollision(Entity &second) = 0;
};


#endif //COLLIDABLE_HPP
