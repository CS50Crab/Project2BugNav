#include "BugNav1.h"
#include "Tile.h"
#include <iostream>

int main() {
    std::vector<std::vector<Tile>> map;
    int width = 7;
    int height = 7;
    for (int r = 0; r < height; r++) {
        std::vector<Tile> row;
        for (int c = 0; c < width; c++) {
            Tile tile = Tile();
            row.push_back(tile);
        }
        map.push_back(row);
    }

    for (int i = 2; i < 2+3; i++) {
        for (int j = 2; j < 2+3; j++) {
            map[i][j].setPassable(false);
        }
    }

    std::vector<int> start = {0, 3};
    std::vector<int> target = {6, 3};
    BugNav1 bugnav = BugNav1(map, start, target);

    for (int r = 0; r < height; r++) {
        for (int t = 0; t < width; t++) {
            
            if (r == start[0] && t == start[1]) {
                std::cout << "B" << " ";
            } else if (r == target[0] && t == target[1]) {
                std::cout << "G" << " ";
            } else {
                std::cout << map[r][t].isPassable() << " ";
            }
        }
        std::cout << std::endl;
    }

    std::vector<std::pair<int, int>> result = bugnav.findPath();
    for (auto pair : result) {
        std::cout << pair.first << ", " << pair.second << std::endl;
    }

    return 0;
}

