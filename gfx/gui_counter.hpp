#ifndef GUI_COUNTER_HPP
#define GUI_COUNTER_HPP
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"


class GuiCounter {
public:
    GuiCounter(const sf::Texture &texture, const sf::Font &font);

    virtual ~GuiCounter() = default;

    virtual auto update(unsigned int points) -> void = 0;

    virtual auto render(sf::RenderTarget &target) const -> void = 0;

protected:
    sf::Sprite background;
    sf::Text textCounter;
};


#endif //GUI_COUNTER_HPP
