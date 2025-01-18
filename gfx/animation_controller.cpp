#include "animation_controller.hpp"

AnimationController::AnimationController(sf::Sprite *sprite, sf::Texture *texture): sprite(sprite), texture(texture) {
}

AnimationController::~AnimationController() {
    animations.clear();
}

auto AnimationController::isDone(const std::string &name) const -> bool {
    if (!animations.contains(name)) return false;
    return animations.at(name).isDone();
}

auto AnimationController::addAnimation(const std::string &name, const float frameTime, const int firstFrameX,
                                       const int firstFrameY,
                                       const int framesLengthX, const int framesLengthY, const int width,
                                       const int height) -> void {
    animations.insert_or_assign(name, Animation(sprite, texture, frameTime, firstFrameX, firstFrameY, framesLengthX,
                                                framesLengthY,
                                                width, height));
}

auto AnimationController::play(const std::string &name, const float &tickDuration) -> bool {
    if (lastAnimation != name) {
        if (lastAnimation.empty()) {
            lastAnimation = name;
        } else {
            if (animations.contains(lastAnimation)) {
                animations.at(lastAnimation).reset();
                lastAnimation = name;
            }
        }
    }
    if (animations.contains(name)) {
        animations.at(name).play(tickDuration);
        return animations.at(name).isDone();
    }
    return false;
}
