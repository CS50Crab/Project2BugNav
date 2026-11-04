#pragma once
#include "BugNav.h"
#include "Bug.h"
#include "Tile.h"
#include <vector>

class BugNav1 : public BugNav {
    private:
        std::vector<std::vector<Tile>> map;
        Bug bug;
        // std::vector<int> start;
        // std::vector<int> target;
        std::pair<int, int> start;
        std::pair<int, int> target;
        std::vector<std::pair<int, int>> path;

    
    public:
        BugNav1();
        BugNav1(std::vector<std::vector<Tile>> m_map, std::pair<int, int> m_start, std::pair<int, int> m_target);

        std::vector<std::pair<int, int>> findPath() override;
        int moveTowardsTarget();
        std::vector<std::pair<int, int>> circlePerimeter(std::pair<int, int> stopPosition, bool returnCondition);
};