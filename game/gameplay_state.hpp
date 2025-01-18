#ifndef GAMEPLAY_STATE_HPP
#define GAMEPLAY_STATE_HPP
#include "state_base.hpp"
#include "../entity/player.hpp"
#include "../entity/coin.hpp"
#include "../entity/enemy.hpp"
#include "../gfx/coin_counter.hpp"
#include "../gfx/hp_counter.hpp"
#include "../gfx/tilemap.hpp"


class GameplayState final : public StateBase {
public:
    GameplayState(std::map<std::string, sf::Texture> &textures, sf::Font &font);

    ~GameplayState() override;

    auto spawnEnemies() -> void;

    auto updateDt() -> void;

    auto update(sf::RenderWindow &window) -> void override;

    auto updatePlayerInput(const float &tickDuration) -> void;

    auto render(sf::RenderWindow &window) -> void override;

    auto getNextState() -> GameState override;

private:
    float static inline tickRate = 128.f;
    float static inline tickDuration = 1.0f / tickRate;

    GameState nextState;

    std::map<std::string, sf::Texture> &textures;
    sf::Font &font;

    sf::Clock timer;
    float timeSinceLastUpdate;
    float dt;
    sf::Clock fpsTimer;
    float fps;
    int frameCount;

    Tilemap *tilemap;
    Player *player;
    HpCounter *hpCounter;
    CoinCounter *coinCounter;
    std::vector<Enemy *> enemies;
    std::vector<Entity *> entities;

    int timeSinceLastRespawn;
    sf::Clock respawnTimer;
};


#endif //GAMEPLAY_STATE_HPP
