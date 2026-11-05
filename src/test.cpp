#include "BugNav2.h"
#include <iostream>

int main() {
    std::vector<std::vector<bool>> maze = {{true, false, true, false, true},
                                           {true, false, true, false, true},
                                           {true, false, true, true, true},
                                           {true, false, false, false, true},
                                           {true, true, true, true, true}};

    BugNav2* nav = new BugNav2(maze, std::make_pair(0, 0), std::make_pair(0, 4));
    std::vector<std::pair<int, int>> path = nav->findPath();
    std::cout << "path: " << std:: endl;
    for (std::pair<int, int> t : path) std::cout << t.first << ", " << t.second << std::endl;
    return 0;
}