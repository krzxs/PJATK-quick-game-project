#include "game_utils.hpp"

#include <random>

auto GameUtils::getRandomFloat(const float min, const float max) -> float {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution dist(min, max);
    return dist(gen);
}

auto GameUtils::getRandomInt(const int min, const int max) -> int {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution dist(min, max);
    return dist(gen);
}
