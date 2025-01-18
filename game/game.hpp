#ifndef GAME_HPP
#define GAME_HPP
#include <map>

#include "gameplay_state.hpp"
#include "main_menu_state.hpp"
#include "state_base.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class Game {
public:
    Game();

    ~Game();

    auto run() -> void;

    auto update() -> void;

    auto render() -> void;

private:
    GameState currentState;
    StateBase *state;

    MainMenuState *mainMenuState;
    GameplayState *gameplayState;

    sf::RenderWindow window;
    sf::Event event;

    std::map<std::string, sf::Texture> textures;
    sf::Font font;


    auto initTextures() -> void;

    auto initFont() -> void;
};


#endif //GAME_HPP
