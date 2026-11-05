#include "BugNav2.h"
#include "Tile.h"
#include <iostream>

int main() {

    std::vector<std::vector<bool>> tempMaze = {
        {true, false, true, false, true},
        {true, false, true, false, true},
        {true, false, true, true, true},
        {true, false, false, false, true},
        {true, true, true, true, true}
    };

    std::vector<std::vector<Tile>> maze;

    for (int i = 0; i < tempMaze.size(); i++) {

        maze.push_back({});

        for (int j = 0; j < tempMaze[i].size(); j++) {
            Tile t;
            t.setPassable(tempMaze[i][j]);
            std::vector<Tile>& row = maze[i];
            row.push_back(t);
        } // end for
    } // end for

    BugNav2* nav = new BugNav2(maze, std::make_pair(0, 0), std::make_pair(0, 4));
    std::vector<std::pair<int, int>> path = nav->findPath();
    std::cout << "path: " << std:: endl;
    for (std::pair<int, int> t : path) std::cout << t.first << ", " << t.second << std::endl;
    return 0;
}