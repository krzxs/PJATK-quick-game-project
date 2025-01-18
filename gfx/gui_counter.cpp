#include "gui_counter.hpp"

GuiCounter::GuiCounter(const sf::Texture &texture, const sf::Font &font) : background(sf::Sprite(texture)),
                                                                           textCounter(sf::Text("000", font, 30)) {
}
