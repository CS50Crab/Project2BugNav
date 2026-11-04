#include "BugNav2.h"

int main() {
    std::vector<std::vector<bool>> maze = {{true, true, true}, {true, true, true}, {true, true, true}};
    BugNav2* nav = new BugNav2(maze, std::make_pair(0, 0), std::make_pair(2, 2));
    return 0;
}