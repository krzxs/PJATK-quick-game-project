#ifndef COIN_COUNTER_HPP
#define COIN_COUNTER_HPP
#include "gui_counter.hpp"
#include "SFML/Graphics/Text.hpp"


class CoinCounter final : public GuiCounter {
public:
    CoinCounter(const sf::Texture &texture, const sf::Font &font);

    auto update(unsigned points) -> void override;

    auto render(sf::RenderTarget &target) const -> void override;
};


#endif //COIN_COUNTER_HPP
