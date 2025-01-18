#ifndef FOLLOW_COMPONENT_HPP
#define FOLLOW_COMPONENT_HPP
#include "entity_living.hpp"


class FollowComponent {
public:
    FollowComponent(EntityLiving &self, EntityLiving &other);

    auto update(const float &tickDuration) const -> void;

private:
    EntityLiving &self;
    EntityLiving &other;
};


#endif //FOLLOW_COMPONENT_HPP
