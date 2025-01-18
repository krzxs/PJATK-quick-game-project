#ifndef HP_COUNTER_HPP
#define HP_COUNTER_HPP
#include "gui_counter.hpp"


class HpCounter final : public GuiCounter {
public:
    HpCounter(const sf::Texture &texture, const sf::Font &font);

    auto update(unsigned points) -> void override;

    auto render(sf::RenderTarget &target) const -> void override;
};


#endif //HP_COUNTER_HPP
