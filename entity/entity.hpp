#ifndef ENTITY_HPP
#define ENTITY_HPP
#include <string>

#include "hitbox_controller.hpp"
#include "../gfx/animation_controller.hpp"


class Entity {
public:
    Entity(sf::Texture &texture, float hitboxWidth, float hitboxHeight, float hitboxOffsetX, float hitboxOffsetY);

    virtual ~Entity() = default;

    auto getId() const -> unsigned long;

    template<typename T>
    auto is() -> bool {
        return dynamic_cast<T *>(this) != nullptr;
    }

    template<typename T>
    auto as() -> T {
        return dynamic_cast<T *>(this);
    }

    auto setTexture(const sf::Texture &texture) -> void;

    //Movement
    auto getPosition() const -> sf::Vector2f;

    auto setPosition(float x, float y) -> void;

    auto getCenter() const -> sf::Vector2f;

    //Size
    auto getSize() const -> sf::Vector2f;

    //Update
    virtual auto update(const float &tickDuration) -> void = 0;

    virtual auto render(sf::RenderTarget &target, bool hitbox) const -> void;

    auto isAlive() const -> bool;

    virtual auto die() -> void = 0;

private:
    static inline unsigned long nextId = 0;
    unsigned long id;

    virtual auto updateAnimation(const float &tickDuration) -> void = 0;

    virtual auto initAnimations() -> void = 0;

protected:
    sf::Sprite sprite;
    AnimationController animationController;
    HitboxController hitboxController;

    bool alive;
};


#endif //ENTITY_HPP
