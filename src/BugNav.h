#pragma once
#include <vector>

class BugNav {

    private:
        std::vector<std::vector<bool>> maze;
    
    public:
        std::vector<std::pair<int, int>> findPath(std::vector<std::vector<bool>>);

};