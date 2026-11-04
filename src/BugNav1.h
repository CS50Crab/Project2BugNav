#pragma once
#include "BugNav.h"
#include "Bug.h"
#include "Tile.h"
#include <vector>

class BugNav1 : public BugNav {
    private:
        std::vector<std::vector<Tile>> map;
        Bug bug;
        std::vector<int> start;
        std::vector<int> target;
    
    public:
        BugNav1();
        BugNav1(std::vector<std::vector<Tile>> m_map, std::vector<int> m_start, std::vector<int> m_target);
        std::vector<std::pair<int, int>> findGoal();
        int moveTowardsTarget();
        std::vector<std::pair<int, int>> circlePerimeter(std::vector<int> stopPosition);
};