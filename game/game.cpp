#include "game.hpp"

#include <random>

#include "gameplay_state.hpp"
#include "main_menu_state.hpp"
#include "fmt/base.h"
#include "SFML/Graphics/Texture.hpp"

auto Game::initTextures() -> void {
    if (!textures["PLAYER_SHEET"].loadFromFile("../res/player/player_sheet.png")) {
        fmt::println("Failed to load player_sheet.png");
    }
    if (!textures["COIN_SHEET"].loadFromFile("../res/coin/coin_sheet.png")) {
        fmt::println("Failed to load coin_sheet.png");
    }
    if (!textures["EARTH_SHEET"].loadFromFile("../res/map/earth_sheet.png")) {
        fmt::println("Failed to load earth_sheet.png");
    }
    if (!textures["COIN_COUNTER"].loadFromFile("../res/gui/coin_counter.png")) {
        fmt::println("Failed to load coin_counter.png");
    }
    if (!textures["HP_COUNTER"].loadFromFile("../res/gui/hp_counter.png")) {
        fmt::println("Failed to load hp_counter.png");
    }
    if (!textures["BALL_SHEET"].loadFromFile("../res/ball/ball_sheet.png")) {
        fmt::println("Failed to load ball_sheet.png");
    }
    if (!textures["PORTAL_SHEET"].loadFromFile("../res/portal/portal_sheet.png")) {
        fmt::println("Failed to load portal_sheet.png");
    }
    if (!textures["ENEMY_SHEET1"].loadFromFile("../res/enemy/enemy_sheet1.png")) {
        fmt::println("Failed to load enemy_sheet1.png");
    }
    if (!textures["ENEMY_SHEET2"].loadFromFile("../res/enemy/enemy_sheet2.png")) {
        fmt::println("Failed to load enemy_sheet2.png");
    }
    if (!textures["ENEMY_SHEET3"].loadFromFile("../res/enemy/enemy_sheet3.png")) {
        fmt::println("Failed to load enemy_sheet2.png");
    }
    if (!textures["ENEMY_BALL_SHEET"].loadFromFile(("../res/ball/enemy_ball_sheet.png"))) {
        fmt::println("Failed to load enemy_ball_sheet.png");
    }
}

auto Game::initFont() -> void {
    if (!font.loadFromFile("../res/font/font.ttf")) {
        fmt::println("Failed to load font.ttf");
    }
}

Game::Game() : currentState(MAIN_MENU), state(nullptr), mainMenuState(nullptr), gameplayState(nullptr),
               window(sf::RenderWindow(sf::VideoMode(1600, 900), "PJC", sf::Style::Titlebar | sf::Style::Close)) {
    initTextures();
    initFont();
}

auto Game::run() -> void {
    mainMenuState = std::make_unique<MainMenuState>(font);
    gameplayState = std::make_unique<GameplayState>(textures, font);

    while (window.isOpen()) {
        switch (currentState) {
            case MAIN_MENU:
                state = mainMenuState.get();
                break;
            case GAMEPLAY:
                state = gameplayState.get();
                break;
            default:
                window.close();
                break;
        }
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        update();
        render();
        currentState = state->getNextState();
    }
}

auto Game::update() -> void {
    state->update(window);
}

auto Game::render() -> void {
    window.clear();
    state->render(window);
    window.display();
}
