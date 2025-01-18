#include "tilemap.hpp"

#include <fstream>
#include <sstream>

Tilemap::Tilemap(const float tileSize, const sf::Texture &texture): texture(texture), rows(0), cols(0),
                                                                    tileSize(tileSize) {
}

auto Tilemap::loadFromFile(const std::string &path) -> bool {
    auto file = std::fstream(path);
    if (!file.is_open()) {
        return false;
    }
    auto line = std::string();
    unsigned int y = 0;
    while (std::getline(file, line)) {
        auto stream = std::stringstream(line);
        auto tileNumberStr = std::string();
        unsigned int x = 0;
        while (std::getline(stream, tileNumberStr, ',')) {
            auto tileNumber = std::stoi(tileNumberStr);
            tiles.emplace_back(x * tileSize, y * tileSize, tileSize, texture, tileNumber);

            ++x;
        }
        ++y;
    }

    rows = y;
    cols = tiles.size() / y;

    return true;
}

auto Tilemap::render(sf::RenderTarget &target) const -> void {
    for (auto &tile: tiles) {
        tile.render(target);
    }
}
