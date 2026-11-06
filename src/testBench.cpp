#include "BugNav1.h"
#include "Tile.h"
#include "Map.h"
#include <iostream>

int main() {
    int height = 100;
    int width = 100;
    Map map = Map(34, height, width);

    //starting point and target point should always be along the edge of the map because I ensured that the edge tiles will always be clear
    std::pair<int, int> target = {99, 99};
    std::pair<int, int> start = {0, 0};
    BugNav1 bugnav = BugNav1(map.getMap(), start, target);

    map.print({});


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


    std::vector<std::pair<int, int>> result = bugnav.findPath();
    std::cout << std::endl;
    map.print(result);
    for (auto pair : result) {
        std::cout << "(" << pair.first << ", " << pair.second << "), ";
    }

    return 0;
}

