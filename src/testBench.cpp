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

    map[0][2].setPassable(false);
    map[0][3].setPassable(false);
    map[0][4].setPassable(false);

    map[1][2].setPassable(false);
    map[1][3].setPassable(true);
    map[1][4].setPassable(false);

    map[2][2].setPassable(false);
    map[2][3].setPassable(true);
    map[2][4].setPassable(false);

    map[3][2].setPassable(false);
    map[3][3].setPassable(false);
    map[3][4].setPassable(false);

    map[4][2].setPassable(true);
    map[4][3].setPassable(false);
    map[4][4].setPassable(false);

    std::vector<int> start = {1, 3};
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

