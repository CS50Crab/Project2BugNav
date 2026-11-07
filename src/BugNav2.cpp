#include "BugNav2.h"
#include "Tile.h"
#include <iostream>
#include <cmath>
#include <set>   
#include <tuple>

std::vector<std::vector<bool>> generateMLine(int, int, std::pair<int, int>, std::pair<int, int>);
int getSquareDist(std::pair<int, int>, std::pair<int, int>);

// Constructor
BugNav2::BugNav2(std::vector<std::vector<Tile>> maze, std::pair<int, int> start, std::pair<int, int> goal) {
    this->maze = maze;
    this->start = start;
    this->goal = goal;
    // validate the grid & endpoints before indexing them
    if (maze.empty() || maze[0].empty()) return;
    for (const auto& row : maze)
        if (row.size() != maze[0].size()) return;
    if (start.first < 0 || start.first >= static_cast<int>(maze.size()) ||
        start.second < 0 || start.second >= static_cast<int>(maze[0].size()) ||
        goal.first < 0 || goal.first >= static_cast<int>(maze.size()) ||
        goal.second < 0 || goal.second >= static_cast<int>(maze[0].size())) return;
    mLine = generateMLine(maze.size(), maze[0].size(), start, goal);
} // end Constructor

std::vector<std::pair<int, int>> BugNav2::findPath() {

    const int TURN_DEGREE = 2;
    // reject invalid inputs & include the starting position
    if (mLine.empty() || !maze[start.first][start.second].isPassable() ||
        !maze[goal.first][goal.second].isPassable()) return {};
    std::vector<std::pair<int, int>> path = {start};
    std::pair<int, int> curStep = start;
    // std::cout << "Started pathing" << std::endl;
    std::pair<int, int> greedyDirection;
    int greedyDirectionIndex = -1;
    bool followingObject = false;
    // remember obstacle hit distance and detect boundary loops
    int hitDistance = 0;
    std::set<std::tuple<int, int, int>> boundaryStates;

    while (curStep != goal) {

        // std::cout << "On step " << curStep.first << ", " << curStep.second << std::endl;
        // keep the M-line unchanged. stop if a boundary state repeats
        if (followingObject && !boundaryStates.insert(
                {curStep.first, curStep.second, greedyDirectionIndex}).second)
            return path;
        bool madeGreedyMove = false;

        // Check if can follow lines
        for (int i = 0; i < movableDirections.size(); i++) {

            std::pair<int, int> direction = movableDirections[i];

            std::pair<int, int> nextStep = std::make_pair(curStep.first + direction.first,
                                                          curStep.second + direction.second);
            
            bool inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                           && nextStep.second >= 0 && nextStep.second < maze[0].size();

            // std::cout << "Looking at " << nextStep.first << ", " << nextStep.second << std::endl;
            // move forward on the M-line & leave a wall only after progress
            if (inRange && mLine[nextStep.first][nextStep.second] && !madeGreedyMove &&
                getSquareDist(nextStep, goal) < getSquareDist(curStep, goal) &&
                (!followingObject || (mLine[curStep.first][curStep.second] &&
                 getSquareDist(curStep, goal) < hitDistance &&
                 maze[nextStep.first][nextStep.second].isPassable()))) {
                // std::cout << "Using " << nextStep.first << ", " << nextStep.second << std::endl;
                if (maze[nextStep.first][nextStep.second].isPassable()) {
                    curStep = nextStep;
                    path.push_back(nextStep);
                    madeGreedyMove = true;
                    followingObject = false;
                    boundaryStates.clear(); // a new obstacle gets a fresh loop check
                } // end if

                greedyDirection = direction;
                greedyDirectionIndex = i;
                break; //keep the chosen direction, including when blocked.

            } // end if

        } // end for

        if (!madeGreedyMove) {

            // std::cout << "Can't do greedy move" << std::endl;
            
            std::pair<int, int> nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                                          curStep.second + greedyDirection.second);
            // std::cout << "starting at " << nextStep.first << ", " << nextStep.second << " with index " << greedyDirectionIndex  << std::endl;
            bool inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                           && nextStep.second >= 0 && nextStep.second < maze[0].size();

            bool justHit = !followingObject; // use the 1st safe turn when hitting a wall
            if (!followingObject) {
                // save the hit distance and limit the search to eight neighbors
                hitDistance = getSquareDist(curStep, goal);
                boundaryStates.clear();
                int attempts = 0;

                while (!inRange || !maze[nextStep.first][nextStep.second].isPassable()) {
                    if (attempts++ >= 8) return path; //no available neighbor.

                    // Try rotating left
                    greedyDirectionIndex--;
                    greedyDirectionIndex = greedyDirectionIndex < 0 ?
                        movableDirections.size() - 1 : greedyDirectionIndex;
                    // std::cout << "Current index: " << greedyDirectionIndex << std::endl;
                    greedyDirection = movableDirections[greedyDirectionIndex];

                    nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                              curStep.second + greedyDirection.second);
                    
                    inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                              && nextStep.second >= 0 && nextStep.second < maze[0].size();

                } // end while
                
                followingObject = true;

            } // end if

            // Try to find a movable tile
            if (followingObject && !justHit) {

                bool moved = false;
                int tempDirectionIndex = greedyDirectionIndex;
                std::pair<int, int> tempDirection = greedyDirection;
                std::pair<int, int> tempStep = nextStep;
                
                for (int i = 0; i < TURN_DEGREE; i++) {

                    // Rotate right
                    tempDirectionIndex++;
                    tempDirectionIndex = tempDirectionIndex >= movableDirections.size() ?
                        0 : tempDirectionIndex;
                    tempDirection = movableDirections[tempDirectionIndex];

                    tempStep = std::make_pair(curStep.first + tempDirection.first,
                                            curStep.second + tempDirection.second);

                    inRange = tempStep.first >= 0 && tempStep.first < maze.size()
                              && tempStep.second >= 0 && tempStep.second < maze[0].size();
                    
                    // std::cout << "trying: " << tempStep.first << ", " << tempStep.second << std::endl;
                    if (inRange && maze[tempStep.first][tempStep.second].isPassable()) {
                        // std::cout << "using" << std::endl;
                        nextStep = tempStep;
                        greedyDirectionIndex = tempDirectionIndex;
                        greedyDirection = tempDirection;
                        moved = true;
                    } // end if

                } // end for

                if (!moved) {
                    // check nextStep (not the last tempStep examined above)
                    inRange = nextStep.first >= 0 && nextStep.first < maze.size()
                              && nextStep.second >= 0 && nextStep.second < maze[0].size();
                    int attempts = 0;

                    while (!inRange || !maze[nextStep.first][nextStep.second].isPassable()) {
                        if (attempts++ >= 8) return path; // no available neighbor.

                        // Try rotating left
                        greedyDirectionIndex--;
                        greedyDirectionIndex = greedyDirectionIndex < 0 ?
                            movableDirections.size() - 1 : greedyDirectionIndex;
                        greedyDirection = movableDirections[greedyDirectionIndex];

                        nextStep = std::make_pair(curStep.first + greedyDirection.first,
                                                curStep.second + greedyDirection.second);
                                                
                        // std::cout << "trying position: " << greedyDirectionIndex << std::endl;

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

        // std::cout << curStep.first << ", " << curStep.second << std::endl;
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
    // std::cout << goal.first << ", " << goal.second << std::endl;
    // std::cout << "ending m-line" << std::endl;

    return mLine;

} // end GenerateMLine

int getSquareDist(std::pair<int, int> pos1, std::pair<int, int> pos2) {
    return int(std::pow(pos1.first - pos2.first, 2) + std::pow(pos1.second - pos2.second, 2));
} // end getSquareDist
