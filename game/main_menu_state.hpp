#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP
#include "state_base.hpp"


class MainMenuState final : public StateBase {
public:
    MainMenuState();

    auto update() -> void override;

    auto render(sf::RenderWindow &window) -> void override;

    auto getNextState() -> GameState override;

private:
    GameState nextState;
};


#endif //MAIN_MENU_STATE_HPP
