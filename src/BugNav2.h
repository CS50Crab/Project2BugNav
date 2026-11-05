#pragma once
#include "BugNav.h"
#include <vector>

class BugNav2 : public BugNav {

    private:
        std::vector<std::vector<bool>> maze;
        std::vector<std::vector<bool>> mLine;
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> start;
        std::pair<int, int> goal;

        const std::vector<std::pair<int, int>> movableDirections = {
            std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 1),
            std::make_pair(1, 0), std::make_pair(1, -1), std::make_pair(0, -1),
            std::make_pair(-1, -1), std::make_pair(-1, 0)
        };
    
    public:
        BugNav2(std::vector<std::vector<bool>>, std::pair<int, int>, std::pair<int, int>);
        std::vector<std::pair<int, int>> findPath() override;

};