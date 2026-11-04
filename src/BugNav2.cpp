#include "BugNav2.h"
#include <iostream>
#include <cmath>

std::vector<std::vector<bool>> generateMLine(int, int, std::pair<int, int>, std::pair<int, int>);
int getSquareDist(std::pair<int, int>, std::pair<int, int>);

// Constructor
BugNav2::BugNav2(std::vector<std::vector<bool>> maze, std::pair<int, int> start, std::pair<int, int> goal) {
    this->maze = maze;
    this->start = start;
    this->goal = goal;
    mLine = generateMLine(maze.size(), maze[0].size(), start, goal);
} // end Constructor

std::vector<std::pair<int, int>> BugNav2::findPath() {

    std::vector<std::pair<int, int>> path;
    std::pair<int, int> curStep = start;

    while (curStep != goal) {

        bool madeGreedyMove = false;

        // Check if can follow lines
        for (std::pair<int, int> direction : movableDirections) {

            std::pair<int, int> nextStep = std::make_pair(curStep.first + direction.first,
                                                          curStep.second + direction.second);
            
            if (mLine[nextStep.first][nextStep.second] && maze[nextStep.first][nextStep.second]) {
                path.push_back(nextStep);
                mLine[nextStep.first][nextStep.second] = false;
                madeGreedyMove = true;
                break;
            } // end if

        } // end for

        if (!madeGreedyMove) {

        } // end if

    } // end while

    return path;

}

std::vector<std::vector<bool>> generateMLine(int width, int height, std::pair<int, int> start, std::pair<int, int> goal) {

    // Initialize array for getting neighbors
    std::pair<int, int> neighborOffsets[] = {
        std::make_pair(-1, 1), std::make_pair(0, 1), std::make_pair(1, 1),
        std::make_pair(-1, 0), std::make_pair(1, 0),
        std::make_pair(-1, -1), std::make_pair(0, -1), std::make_pair(1, -1)
    };

    // Create maze with all tiles set to false
    std::vector<std::vector<bool>> mLine(width);
    for (std::vector<bool>& v : mLine) {
        std::vector<bool> column(height);
        v = column;
    } // end for

    // Get m-line by following straight from start line to goal
    std::pair<int, int> curStep = start;
    while (curStep != goal) {

        mLine[curStep.first][curStep.second] = true;
        int bestDist = getSquareDist(curStep, goal);
        std::pair<int, int> bestStep = curStep;
        for (int i = 0; i < 8; i++) {

            std::pair<int, int> offset = neighborOffsets[i];

            std::pair<int, int> nextStep = std::make_pair(curStep.first + offset.first,
                                                          curStep.second + offset.second);
            int curDist = getSquareDist(nextStep, goal);

            if (curDist < bestDist) {
                bestDist = curDist;
                bestStep = nextStep;
            } // end if

        } // end for

        curStep = bestStep;

    } // end while

    mLine[goal.first][goal.second] = true;

    return mLine;

} // end GenerateMLine

int getSquareDist(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    return int(std::pow(pos1.first - pos2.first, 2) + std::pow(pos1.second - pos2.second, 2));
} // end getSquareDist