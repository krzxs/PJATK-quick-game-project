#ifndef BUTTON_HPP
#define BUTTON_HPP
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"


class Button {
public:
    Button(const std::string &str, const sf::Font &font, bool enabled);

    auto getGlobalBounds() const -> sf::FloatRect;

    auto getText() -> sf::Text &;

    auto setPosition(float x, float y) -> void;

    auto isEnabled() const -> bool;

    auto render(sf::RenderTarget &target) const -> void;

private:
    sf::Text text;

    bool enabled;
};


#endif //BUTTON_HPP
