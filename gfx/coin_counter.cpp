#include "coin_counter.hpp"

#include "fmt/format.h"
#include "SFML/Graphics/RenderTarget.hpp"

CoinCounter::CoinCounter(const sf::Texture &texture, const sf::Font &font) : GuiCounter(texture, font) {
    background.setPosition(sf::Vector2f(1600 - texture.getSize().x, 900 - texture.getSize().y));

    textCounter.setFillColor(sf::Color::White);
    textCounter.setOutlineColor(sf::Color::Black);
    textCounter.setOutlineThickness(1.6f);

    textCounter.setOrigin(textCounter.getGlobalBounds().getSize() / 2.f + textCounter.getLocalBounds().getPosition());
    textCounter.setPosition(background.getPosition().x + background.getGlobalBounds().getSize().x / 1.55f,
                            background.getPosition().y + background.getGlobalBounds().getSize().y / 2.f);
}


auto CoinCounter::update(unsigned int points) -> void {
    textCounter.setString(fmt::format("{:03}", points));
}

auto CoinCounter::render(sf::RenderTarget &target) const -> void {
    target.draw(background);
    target.draw(textCounter);
}
