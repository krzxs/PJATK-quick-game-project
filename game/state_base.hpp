#ifndef STATE_BASE_HPP
#define STATE_BASE_HPP
#include "SFML/Graphics/RenderWindow.hpp"

enum GameState {
    MAIN_MENU,
    GAMEPLAY,
    PAUSE_MENU,
    EXIT
};

class StateBase {
public:
    virtual ~StateBase() = default;

    virtual auto update() -> void = 0;

    virtual auto render(sf::RenderWindow &window) -> void = 0;

    virtual auto getNextState() -> GameState = 0;
};


#endif //STATE_BASE_HPP
