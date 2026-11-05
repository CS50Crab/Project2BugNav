#pragma once
#include <vector>
#include "Tile.h"

class BugNav {

    private:
        std::vector<std::vector<Tile>> maze;
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> start;
        std::pair<int, int> goal;
    
    public:
        // BugNav(std::vector<std::vector<bool>>, std::pair<int, int>, std::pair<int, int>);
        virtual std::vector<std::pair<int, int>> findPath() = 0;

};