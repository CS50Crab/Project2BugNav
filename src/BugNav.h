#pragma once
#include <vector>

class BugNav {

    private:
        std::vector<std::vector<bool>> maze;
        std::vector<std::pair<int, int>> path;
        std::pair<int, int> start;
        std::pair<int, int> goal;
    
    public:
        // BugNav(std::vector<std::vector<bool>>, std::pair<int, int>, std::pair<int, int>);
        virtual std::vector<std::pair<int, int>> findPath() = 0;

};