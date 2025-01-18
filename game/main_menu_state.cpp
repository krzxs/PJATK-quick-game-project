#include "main_menu_state.hpp"

MainMenuState::MainMenuState(): nextState(MAIN_MENU) {
}

auto MainMenuState::update() -> void {
}

auto MainMenuState::render(sf::RenderWindow &window) -> void {
    window.clear(sf::Color::Black);
}

auto MainMenuState::getNextState() -> GameState {
    return nextState;
}
