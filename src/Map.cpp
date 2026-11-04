#include "Map.h"
#include "Tile.h"

#include <random>
#include <chrono>
#include <iostream>

Map::Map() {
    mapDensity = 40;
    wallFactor = 4;
    width = 500;
    height = 500;
    generateMap();
}

Map::Map(int density, int m_width, int m_height) {
    mapDensity = density;
    wallFactor = 4;
    width = m_width;
    height = m_height;
    generateMap();
}

void Map::generateMap() {
    //1. create map grid
    for (int r = 0; r < height; r++) {
        std::vector<Tile> row;
        for (int c = 0; c < width; c++) {
            Tile tile = Tile();
            row.push_back(tile);
        }
        map.push_back(row);
    }

    //2. random number generation
    unsigned int seed = static_cast<unsigned int> (std::chrono::system_clock::now().time_since_epoch().count());
    std::random_device rd;
    seed ^= rd();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> dis(1, 100);

    //3. random noise while leaving edges clear
    for (int r = 1; r < height-1; ++r) {
        for (int c = 1; c < width-1; ++c) {
            //random number between 1 and 100
            int roll = dis(gen);
            // std::cout << roll << std::endl;
            
            if (roll <= mapDensity) {
                map[r][c].setPassable(false); // Obstacle / Wall
            } else {
                map[r][c].setPassable(true); // Passable
            }
        }
    }
    //4. smoothing iterations
    print({});
    std::cout << std::endl;
    smoothMap(1);
}

void Map::smoothMap(int iterations) {
    for (int i = 0; i < iterations; i++) {

        for (int r = 1; r < height-1; r++) {
            for (int c = 1; c < width-1; c++) {
                // if (map[r][c].isPassable() == false) {
                //     continue;
                // }
                if (checkSurroundingTiles(r, c) < wallFactor) {
                    map[r][c].setPassable(true);
                } else {
                    map[r][c].setPassable(false);
                }
            }
        }

    }
}

int Map::checkSurroundingTiles(int r, int c) {
    int sum = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            //skip current tile
            if (dr == 0 && dc == 0) {
                continue;
            }
            int nr = r + dr;
            int nc = c + dc;

            //handle edges
            // Check boundaries
        if (nr >= 0 && nr < height && nc >= 0 && nc < width) {
            // Safe to access map[nr][nc]
            if (map[nr][nc].isPassable() == false) {
                sum += 1;
            }
        }
        }
    }
    return sum;
}

void Map::print(std::vector<std::pair<int, int>> m_path) {
    for (auto pair : m_path) {
        map[pair.first][pair.second].visit();
    }

    for (auto row : map) {
        for (auto tile : row) {
            if (tile.isVisited()) {
                std::cout << "=";
            } else if (tile.isPassable()) {
                std::cout << ".";
            } else {
                std::cout << "#";
            }
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<Tile>> Map::getMap() {
    return map;
}