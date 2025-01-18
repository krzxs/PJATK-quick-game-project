#include "button.hpp"

#include "SFML/Graphics/RenderTarget.hpp"

Button::Button(const std::string &str, const sf::Font &font, const bool enabled): text(sf::Text(str, font, 64)),
    enabled(enabled) {
    text.setFillColor(sf::Color::White);
}

auto Button::getGlobalBounds() const -> sf::FloatRect {
    return text.getGlobalBounds();
}

auto Button::getText() -> sf::Text & {
    return text;
}

auto Button::setPosition(const float x, const float y) -> void {
    text.setPosition(x, y);
}

auto Button::isEnabled() const -> bool {
    return enabled;
}

auto Button::render(sf::RenderTarget &target) const -> void {
    target.draw(text);
}
