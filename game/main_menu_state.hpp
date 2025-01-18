#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP
#include "state_base.hpp"
#include "../gfx/button.hpp"


class MainMenuState final : public StateBase {
public:
    explicit MainMenuState(sf::Font &font);

    auto update(sf::RenderWindow &window) -> void override;

    auto render(sf::RenderWindow &window) -> void override;

    auto getNextState() -> GameState override;

private:
    GameState nextState;

    sf::Font &font;

    Button playButton;
    Button exitButton;
};


#endif //MAIN_MENU_STATE_HPP
