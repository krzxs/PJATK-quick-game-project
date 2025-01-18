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
    GameplayState();

    ~GameplayState();

    auto update() -> void override;

    auto render(sf::RenderWindow &window) -> void override;

    auto getNextState() -> GameState override;

private:
    GameState nextState;

    Tilemap *tilemap;
    Player *player;
    HpCounter *hpCounter;
    CoinCounter *coinCounter;
    std::vector<Enemy *> enemies;
    std::vector<Entity *> entities;
};


#endif //GAMEPLAY_STATE_HPP
