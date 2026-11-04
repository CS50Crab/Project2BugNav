#pragma once
#include <vector>

class BugNav {

    private:
        std::vector<std::vector<bool>> maze;
    
    public:
        BugNav() = default;
        BugNav(std::vector<std::vector<bool>> inputMaze) : maze(inputMaze) {}
        virtual ~BugNav() = default;
        virtual std::vector<std::pair<int, int>> findPath() = 0;

};