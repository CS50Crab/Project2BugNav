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

    const int TURN_DEGREE = 2;
    std::vector<std::pair<int, int>> path;
    std::pair<int, int> curStep = start;
    std::cout << "Started pathing" << std::endl;
    std::pair<int, int> greedyDirection;
    int greedyDirectionIndex = -1;
    bool followingObject = false;

    while (curStep != goal) {

        std::cout << "On step " << curStep.first << ", " << curStep.second << std::endl;
        mLine[curStep.first][curStep.second] = false;
        bool madeGreedyMove = false;

        // Check if can follow lines
        for (int i = 0; i < movableDirections.size(); i++) {

            std::pair<int, int> direction = movableDirections[i];

            std::pair<int, int> nextStep = std::make_pair(curStep.first + direction.first,
                                                          curStep.second + direction.second);
            
            bool inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                           && nextStep.second >= 0 && nextStep.second < maze[0].size();

            // std::cout << "Looking at " << nextStep.first << ", " << nextStep.second << std::endl;
            if (inRange && mLine[nextStep.first][nextStep.second] && !madeGreedyMove) {
                std::cout << "Using " << nextStep.first << ", " << nextStep.second << std::endl;
                if (maze[nextStep.first][nextStep.second]) {
                    curStep = nextStep;
                    path.push_back(nextStep);
                    madeGreedyMove = true;
                    followingObject = false;
                } // end if

                greedyDirection = direction;
                greedyDirectionIndex = i;
                mLine[nextStep.first][nextStep.second] = false;

            } // end if

        } // end for

        if (!madeGreedyMove) {

            std::cout << "Can't do greedy move" << std::endl;
            
            std::pair<int, int> nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                                          curStep.second + greedyDirection.second);
            std::cout << "starting at " << nextStep.first << ", " << nextStep.second << " with index " << greedyDirectionIndex  << std::endl;
            bool inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                           && nextStep.second >= 0 && nextStep.second < maze[0].size();

            if (!followingObject) {

                while (!inRange || !maze[nextStep.first][nextStep.second]) {

                    greedyDirectionIndex++;
                    greedyDirectionIndex = greedyDirectionIndex >= movableDirections.size() ?
                        0 : greedyDirectionIndex;
                    std::cout << "Current index: " << greedyDirectionIndex << std::endl;
                    greedyDirection = movableDirections[greedyDirectionIndex];

                    nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                              curStep.second + greedyDirection.second);
                    
                    inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                              && nextStep.second >= 0 && nextStep.second < maze[0].size();

                } // end while
                
                followingObject = true;

            } // end if

            // Try to find a movable tile
            if (followingObject) {

                bool moved = false;
                int tempDirectionIndex = greedyDirectionIndex;
                std::pair<int, int> tempDirection = greedyDirection;
                std::pair<int, int> tempStep = nextStep;
                
                for (int i = 0; i < TURN_DEGREE; i++) {

                    // Rotate left
                    tempDirectionIndex--;
                    tempDirectionIndex = tempDirectionIndex < 0 ?
                        movableDirections.size() - 1 : tempDirectionIndex;
                    tempDirection = movableDirections[tempDirectionIndex];

                    tempStep = std::make_pair(curStep.first + tempDirection.first,
                                            curStep.second + tempDirection.second);

                    inRange = tempStep.first >= 0 && tempStep.first < maze.size()
                              && tempStep.second >= 0 && tempStep.second < maze[0].size();
                    
                    std::cout << "trying: " << tempStep.first << ", " << tempStep.second << std::endl;
                    if (inRange && maze[tempStep.first][tempStep.second]) {
                        std::cout << "using" << std::endl;
                        nextStep = tempStep;
                        greedyDirectionIndex = tempDirectionIndex;
                        greedyDirection = tempDirection;
                        moved = true;
                    } // end if

                } // end for

                if (!moved) {

                    while (!inRange || !maze[nextStep.first][nextStep.second]) {

                        greedyDirectionIndex++;
                        greedyDirectionIndex = greedyDirectionIndex >= movableDirections.size() ?
                            0 : greedyDirectionIndex;
                        greedyDirection = movableDirections[greedyDirectionIndex];

                        nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                                curStep.second + greedyDirection.second);
                                                
                        std::cout << "trying position: " << greedyDirectionIndex << std::endl;

                        inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                                  && nextStep.second >= 0 && nextStep.second < maze[0].size();

                    } // end while
                } // end if

            } // end while

            // maze[curStep.first][curStep.second] = false;
            curStep = nextStep;
            path.push_back(nextStep);

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

        std::cout << curStep.first << ", " << curStep.second << std::endl;
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
    std::cout << goal.first << ", " << goal.second << std::endl;
    std::cout << "ending m-line" << std::endl;

    return mLine;

} // end GenerateMLine

int getSquareDist(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    return int(std::pow(pos1.first - pos2.first, 2) + std::pow(pos1.second - pos2.second, 2));
} // end getSquareDist