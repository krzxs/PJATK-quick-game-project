#include "main_menu_state.hpp"

#include "fmt/color.h"
#include "fmt/ostream.h"
#include "SFML/Window/Mouse.hpp"

MainMenuState::MainMenuState(sf::Font &font): nextState(MAIN_MENU), font(font) {
    playButton = new Button("PLAY", font, true);
    playButton->setPosition(800 - playButton->getText().getGlobalBounds().width / 2,
                            450 - playButton->getText().getGlobalBounds().height / 2 - 100);

    exitButton = new Button("EXIT", font, true);
    exitButton->setPosition(800 - exitButton->getText().getGlobalBounds().width / 2,
                            450 - exitButton->getText().getGlobalBounds().height / 2 + 100);
}

MainMenuState::~MainMenuState() {
    delete playButton;
    delete exitButton;
}

auto MainMenuState::update(sf::RenderWindow &window) -> void {
    const auto position = sf::Mouse::getPosition(window);

    if (playButton->isEnabled()) {
        if (playButton->getGlobalBounds().
            contains(static_cast<float>(position.x), static_cast<float>(position.y))) {
            playButton->getText().setFillColor(sf::Color(128, 128, 128));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                fmt::println("Play");
                nextState = GAMEPLAY;
            }
        } else {
            playButton->getText().setFillColor(sf::Color::White);
        }
    }
    if (exitButton->isEnabled()) {
        if (exitButton->getGlobalBounds().
            contains(static_cast<float>(position.x), static_cast<float>(position.y))) {
            exitButton->getText().setFillColor(sf::Color(128, 128, 128));
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                fmt::println("Exit");
                window.close();
            }
        } else {
            exitButton->getText().setFillColor(sf::Color::White);
        }
    }
}

auto MainMenuState::render(sf::RenderWindow &window) -> void {
    playButton->render(window);
    exitButton->render(window);
}

auto MainMenuState::getNextState() -> GameState {
    return nextState;
}
