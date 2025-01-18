#include "game.hpp"

#include <random>

#include "main_menu_state.hpp"
#include "../entity/ball.hpp"
#include "../entity/enemy.hpp"
#include "../entity/enemy_ball.hpp"
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
    if (!textures["ENEMY_BALL_SHEET"].loadFromFile(("../res/ball/enemy_ball_sheet.png"))) {
        fmt::println("Failed to load enemy_ball_sheet.png");
    }
}

auto Game::initFont() -> void {
    if (!font.loadFromFile("../res/font/font.ttf")) {
        fmt::println("Failed to load font.ttf");
    }
}

Game::Game() : currentState(MAIN_MENU), state(nullptr),
               window(sf::RenderWindow(sf::VideoMode(1600, 900), "PJC", sf::Style::Titlebar | sf::Style::Close)),
               timeSinceLastUpdate(0.f), dt(0.f), fps(0.f), frameCount(0) {
    initTextures();
    initFont();

    tilemap = new Tilemap(50.f, textures["EARTH_SHEET"]);
    tilemap->loadFromFile("../res/map/map.txt");

    player = new Player(0, 0, textures["PLAYER_SHEET"]);
    player->setPosition(800 - player->getCenter().x, 450 - player->getCenter().y);

    hpCounter = new HpCounter(textures["HP_COUNTER"], font);
    coinCounter = new CoinCounter(textures["COIN_COUNTER"], font);
}

Game::~Game() {
    delete tilemap;

    delete player;

    delete hpCounter;
    delete coinCounter;

    if (!entities.empty()) {
        for (const auto *e: entities) {
            delete e;
        }
    }
    if (!enemies.empty()) {
        for (const auto *e: enemies) {
            delete e;
        }
    }
}

void Game::run() {
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        updateDt();
        state->update();
        state->render(window);
    }
}

void Game::updateDt() {
    dt = timer.restart().asSeconds();
    timeSinceLastUpdate += dt;
}

auto Game::updatePlayerInput(const float &tickDuration) -> void {
    int x = 0, y = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        y -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        y += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        x -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        x += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (!player->isOnCooldown()) {
            const auto pos = player->getCenter();
            const auto dir = player->getDirection() != Direction(0, 0)
                                 ? player->getDirection()
                                 : player->getLastDirection();
            entities.push_back(new Ball(pos.x, pos.y, textures["BALL_SHEET"], dir));
            player->setOnCooldown(true);
            player->restartCooldown();
        }
    }
    if (const auto direction = Direction(x, y); player->getDirection() != direction) {
        player->setLastDirection(player->getDirection());
        player->setDirection(direction);
    }
    player->move(tickDuration);
}

void Game::update() {
    ++frameCount;
    if (fpsTimer.getElapsedTime().asSeconds() >= 1.f) {
        fps = frameCount / fpsTimer.restart().asSeconds();
        fmt::println("FPS: {}", fps);
        frameCount = 0;
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(1.000, 3.000);

    while (timeSinceLastUpdate >= tickDuration) {
        if (player->isOnCooldown() && player->getCooldownClock().getElapsedTime().asSeconds() >= 1.f) {
            player->setOnCooldown(false);
        }
        updatePlayerInput(timeSinceLastUpdate);
        player->update(timeSinceLastUpdate);
        for (auto *e: entities) {
            if (e->isAlive()) {
                e->update(timeSinceLastUpdate);
                if (player->checkCollision(*e)) {
                    player->onCollision(*e);
                }
            } else {
                entities.erase(std::ranges::find(entities, e));
                delete e;
            }
        }
        for (auto *e: enemies) {
            if (e->isAlive()) {
                auto random = dist(gen);
                if (e->isOnCooldown() && e->getCooldownClock().getElapsedTime().asSeconds() >= random) {
                    e->setOnCooldown(false);
                }
                e->update(timeSinceLastUpdate);
                if (!e->isOnCooldown()) {
                    const auto pos = e->getCenter();
                    const auto dir = e->getDirection() != Direction(0, 0)
                                         ? e->getDirection()
                                         : e->getLastDirection();
                    entities.push_back(new EnemyBall(pos.x, pos.y, textures["ENEMY_BALL_SHEET"], dir));
                    e->setOnCooldown(true);
                    e->restartCooldown();
                }
                for (auto *f: entities) {
                    if (e->checkCollision(*f)) {
                        e->onCollision(*f);
                    }
                }
            } else {
                enemies.erase(std::ranges::find(enemies, e));
                entities.push_back(new Coin(e->getCenter().x, e->getCenter().y, textures["COIN_SHEET"]));
                delete e;
            }
        }
        hpCounter->update(player->getHealth());
        coinCounter->update(player->getCoins());
        timeSinceLastUpdate -= tickDuration;
    }
}

void Game::render() {
    window.clear();
    tilemap->render(window);
    if (!entities.empty()) {
        for (const auto *e: entities) {
            e->render(window, true);
        }
    }
    if (!enemies.empty()) {
        for (const auto *e: enemies) {
            e->render(window, true);
        }
    }
    player->render(window, true);
    hpCounter->render(window);
    coinCounter->render(window);
    window.display();
}
