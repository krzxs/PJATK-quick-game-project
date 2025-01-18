#include "gameplay_state.hpp"

#include <random>

#include "game_utils.hpp"
#include "../entity/ball.hpp"
#include "../entity/enemy_ball.hpp"
#include "fmt/base.h"
#include "SFML/Window/Keyboard.hpp"

GameplayState::GameplayState(std::map<std::string, sf::Texture> &textures, sf::Font &font): nextState(GAMEPLAY),
    textures(textures), font(font), timeSinceLastUpdate(0.f), dt(0.f), fps(0.f), frameCount(0),
    timeSinceLastRespawn(3) {
    tilemap = std::make_unique<Tilemap>(50.f, textures["EARTH_SHEET"]);
    tilemap->loadFromFile("../res/map/map.txt");

    player = std::make_unique<Player>(0, 0, textures["PLAYER_SHEET"]);
    player->setPosition(800 - player->getCenter().x, 450 - player->getCenter().y);

    hpCounter = std::make_unique<HpCounter>(textures["HP_COUNTER"], font);
    coinCounter = std::make_unique<CoinCounter>(textures["COIN_COUNTER"], font);
}

GameplayState::~GameplayState() {
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

auto GameplayState::spawnEnemies() -> void {
    const auto howMany = GameUtils::getRandomInt(1, 3);
    for (int i = 0; i < howMany; i++) {
        const auto level = GameUtils::getRandomInt(1, 10);
        const auto playerPos = player->getCenter();
        float x, y;
        do {
            x = GameUtils::getRandomFloat(100.f, 1500.f);
            y = GameUtils::getRandomFloat(100.f, 800.f);
        } while (std::sqrt(std::pow(x - playerPos.x, 2) + std::pow(y - playerPos.y, 2)) < 300.f);
        Enemy *enemy = nullptr;
        if (level > 9) {
            enemy = new Enemy(x, y, *player, 250, textures["ENEMY_SHEET3"]);
        } else if (level > 6) {
            enemy = new Enemy(x, y, *player, 100, textures["ENEMY_SHEET2"]);
        } else {
            enemy = new Enemy(x, y, *player, 50, textures["ENEMY_SHEET1"]);
        }
        enemies.push_back(enemy);
    }
}

auto GameplayState::updatePlayerInput(const float &tickDuration) -> void {
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


auto GameplayState::updateDt() -> void {
    dt = timer.restart().asSeconds();
    timeSinceLastUpdate += dt;
}

auto GameplayState::update(sf::RenderWindow &window) -> void {
    updateDt();

    ++frameCount;
    if (fpsTimer.getElapsedTime().asSeconds() >= 1.f) {
        fps = frameCount / fpsTimer.restart().asSeconds();
        fmt::println("FPS: {}", fps);
        frameCount = 0;
    }

    if (respawnTimer.getElapsedTime().asSeconds() >= timeSinceLastRespawn) {
        timeSinceLastRespawn = GameUtils::getRandomInt(10, 25);
        spawnEnemies();
        respawnTimer.restart();
    }

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
                if (e->isOnCooldown() && e->getCooldownClock().getElapsedTime().asSeconds() >=
                    GameUtils::getRandomFloat(1.000f, 3.000f)) {
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
        if (enemies.empty()) {
            timeSinceLastRespawn = GameUtils::getRandomInt(10, 25);
            spawnEnemies();
            respawnTimer.restart();
        }
        hpCounter->update(player->getHealth());
        coinCounter->update(player->getCoins());
        timeSinceLastUpdate -= tickDuration;
    }
}

auto GameplayState::render(sf::RenderWindow &window) -> void {
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
}

auto GameplayState::getNextState() -> GameState {
    return nextState;
}
