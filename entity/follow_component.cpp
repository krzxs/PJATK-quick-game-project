#include "follow_component.hpp"

#include <cmath>

#include "fmt/base.h"

FollowComponent::FollowComponent(EntityLiving &self, EntityLiving &other): self(self), other(other) {
}

auto FollowComponent::update(const float &tickDuration) const -> void {
    auto vec = sf::Vector2f();
    vec.x = other.getPosition().x - self.getPosition().x;
    vec.y = other.getPosition().y - self.getPosition().y;

    if (self.getPosition().x != other.getPosition().x && self.getPosition().y != other.getPosition().y) {
        self.setDirection(Direction(round(vec.x) == 0 ? 0 : vec.x > 0 ? 1 : -1,
                                    round(vec.y) == 0 ? 0 : vec.y > 0 ? 1 : -1));
        self.move(tickDuration);
    }
}
