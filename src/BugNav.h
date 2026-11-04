#pragma once
#include <vector>

class BugNav {

    private:
        std::vector<std::vector<bool>> maze;
    
    public:
        BugNav();
        BugNav(std::vector<std::vector<bool>>);
        std::vector<std::pair<int, int>> findPath();

};