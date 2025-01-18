#include "hp_counter.hpp"

#include "fmt/format.h"
#include "SFML/Graphics/RenderTarget.hpp"

HpCounter::HpCounter(const sf::Texture &texture, const sf::Font &font) : GuiCounter(texture, font) {
    background.setPosition(sf::Vector2f(0, 900 - texture.getSize().y));

    textCounter.setFillColor(sf::Color::White);
    textCounter.setOutlineColor(sf::Color::Black);
    textCounter.setOutlineThickness(1.6f);

    textCounter.setOrigin(textCounter.getGlobalBounds().getSize() / 2.f + textCounter.getLocalBounds().getPosition());
    textCounter.setPosition(background.getPosition().x + background.getGlobalBounds().getSize().x / 1.55f,
                            background.getPosition().y + background.getGlobalBounds().getSize().y / 2.f);
}

auto HpCounter::update(unsigned points) -> void {
    textCounter.setString(fmt::format("{:03}", points));
}

auto HpCounter::render(sf::RenderTarget &target) const -> void {
    target.draw(background);
    target.draw(textCounter);
}
