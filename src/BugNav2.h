#pragma once
#include "BugNav.h"
#include <vector>

class BugNav2 {

    private:
        std::vector<std::vector<bool>> maze;
    
    public:
        BugNav2(std::vector<std::vector<bool>>);
        std::vector<std::pair<int, int>> findPath();

};