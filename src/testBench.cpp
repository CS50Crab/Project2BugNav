#include "BugNav1.h"
#include "Tile.h"
#include "Map.h"
#include <iostream>

int main() {
    int height = 50;
    int width = 50;
    Map map = Map(34, height, width);

    std::pair<int, int> target = {10, 10};
    std::pair<int, int> start = {0, 0};
    BugNav1 bugnav = BugNav1(map.getMap(), start, target);

    map.print();


    // for (int r = 0; r < height; r++) {
    //     for (int t = 0; t < width; t++) {
            
    //         if (r == start.first && t == start.second) {
    //             std::cout << "B" << " ";
    //         } else if (r == target.first && t == target.second) {
    //             std::cout << "G" << " ";
    //         } else {
    //             std::cout << map.getMap()[r][t].isPassable() << " ";
    //         }
    //     }
    //     std::cout << std::endl;
    // }


    // std::vector<std::pair<int, int>> result = bugnav.findPath();
    // for (auto pair : result) {
    //     std::cout << pair.first << ", " << pair.second << std::endl;
    // }

    return 0;
}

