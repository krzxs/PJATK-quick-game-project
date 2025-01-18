#ifndef GAME_HPP
#define GAME_HPP
#include <map>

#include "state_base.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"

class Game {
public:
    Game();

    ~Game();

    auto run() -> void;

    auto updateDt() -> void;

    auto updatePlayerInput(const float &tickDuration) -> void;

    auto update() -> void;

    auto render() -> void;

private:
    float static inline tickRate = 128.f;
    float static inline tickDuration = 1.0f / tickRate;

    GameState currentState;
    StateBase *state;

    sf::RenderWindow window;
    sf::Event event;
    sf::Clock timer;
    float timeSinceLastUpdate;
    float dt;
    sf::Clock fpsTimer;
    float fps;
    int frameCount;
    std::map<std::string, sf::Texture> textures;
    sf::Font font;


    auto initTextures() -> void;

    auto initFont() -> void;
};


#endif //GAME_HPP
