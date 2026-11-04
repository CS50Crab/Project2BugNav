#include "BugNav1.h"
#include <iostream>

BugNav1::BugNav1() {
    map = {};
    bug = Bug();
}
BugNav1::BugNav1(std::vector<std::vector<Tile>> m_map, std::pair<int, int> m_start, std::pair<int, int> m_target) {
    map = m_map;
    bug = Bug(m_map, m_start, m_target);
    target = m_target;
    start = m_start;

    path = {};
}



//implementation of the bug 1 algorithm
std::vector<std::pair<int, int>> BugNav1::findPath() {
    std::pair<int, int> currPosition = bug.getPosition();
    path = {currPosition};
    // std::cout << "starting Bug1 algorithm" << std::endl;
    
    while (bug.getPosition() != target) {
        // std::cout << "get current position" << std::endl;
        currPosition = bug.getPosition();
        //exit if the map is unsolveable:
        //case 1: bug is surrounded on all immediate sides
        // std::cout << "checking all sides" << std::endl;
        if ((bug.checkDown() != 0) && (bug.checkLeft() != 0) && (bug.checkRight() != 0) && (bug.checkUp() != 0)) {
            std::cout << "map unsolvable (surrounded)" << std::endl;
            return path;
        } else {
            // std::cout << "not immediately surrounded" << std::endl;
            //try to move towards target:
            // std::cout << "move towards target" << std::endl;
            int movementResult = moveTowardsTarget();
            //check the result of the movement, if it was successful, update the path, and start the loop over
            if (movementResult == 0) {
                // std::cout << "movement successful" << std::endl;
                path.push_back(bug.getPosition());
                continue;
            } else {
                // std::cout << "movement unsuccessful" << std::endl;
                //if movement result is not 0, that means something blocked the path.
                if (movementResult == 2) {
                    bug.setPrevMove(getDesiredDirection()); //this sets the prevMove to be the direction the bug would go in if it hits the obstacle head on
                    //circle the perimeter
                    bug.circling(true);
                    // std::cout << "circling obstacle" << std::endl;
                    
                    std::vector<std::pair<int, int>> circlePath = circlePerimeter(bug.getPosition(), false);
                    path.insert(path.end(), circlePath.begin(), circlePath.end());
                    //if the closest point after circling the obstacle is still the previous starting point, then the map must be unsolveable because there is no way to get closer to the obstacle.
                    if (bug.getClosestPoint() == bug.getPosition()) {
                        std::cout << "map unsolvable (blocked)" << std::endl;
                        return path;
                    }
                    //return to the closest point
                    bug.circling(true);
                    // std::cout << "Trying: return to closest point" << std::endl;
                    circlePath = circlePerimeter(bug.getClosestPoint(), true);
                    path.insert(path.end(), circlePath.begin(), circlePath.end());
                
                    bug.circling(false);
                    int leaveObstacle = moveTowardsTarget();
                    if (leaveObstacle == 0) {
                        path.push_back(bug.getPosition());
                    } else if (leaveObstacle == 2) {
                        //obstacle is hit immedately after finishing circling, can figure out what the head on collision should have been to manually set it
                        bug.setPrevMove(getDesiredDirection());
                        // if (bug.getPrevMove() == "up") {
                        //     bug.setPrevMove("left");
                        // } else if (bug.getPrevMove() == "right") {
                        //     bug.setPrevMove("up");
                        // } else if (bug.getPrevMove() == "down") {
                        //     bug.setPrevMove("right");
                        // } else if (bug.getPrevMove() == "left") {
                        //     bug.setPrevMove("down");
                        // } else {
                        //     std::cout << "incorrect previous direction somehow" << std::endl;
                        // }
                    }
                } else {
                    //for some reason, the bug thinks its at the edge of the map
                    std::cout << "Error: blocked by edge of map" << std::endl;
                }
            }
        }
        
    }
    // std::cout << "DONE" << std::endl;
    return path;
}

//returns similar to the bug.move functions. returns 0 if successful, 1 or 2 if blocked
//since, when moving towards the goal, the bug should technically never try to go into the edge of the map, I would expect a return of 0 or 2
int BugNav1::moveTowardsTarget() {
    // std::cout << "get current position (M): ";
    std::pair<int, int> currPosition = bug.getPosition();
    // std::cout << "(" << currPosition.first << ", " << currPosition.second << std::endl;
    //calculate what direction the bug must go in
    //std::cout << "access index 0 and 1 of current position (M)" << std::endl;

    // int targetX = target.at(0);
    // int targetY = target.at(1);
    // int currX = currPosition.at(0);
    // int currY = currPosition.at(1);

    int yError = target.first - currPosition.first;
    int xError = target.second - currPosition.second;

    //decide which direction the bug must go in based on the which error is bigger
    // std::cout << "Trying: moving (M)" << std::endl;
    if (std::abs(yError) > std::abs(xError)) {
        //move in y direction
        if (yError < 0) {
            return bug.moveUp();
        } else {
            return bug.moveDown();
        }
    } else {
        //move in x direction
        if (xError < 0) {
            return bug.moveLeft();
        } else {
            return bug.moveRight();
        }
    }        
}

//the return condition parameter tells the algorithm whether or not we are returning to a closest point or making a full circle pass.
std::vector<std::pair<int, int>> BugNav1::circlePerimeter(std::pair<int, int> stopPosition, bool returnCondition) {
    std::vector<std::pair<int, int>> circlePath = {};
    // std::cout << "getting current position (C)" << std::endl;
    //std::vector<int> currPosition = bug.getPosition();
    bool init = false;
    while(bug.getCircleState()) {
        std::pair<int, int> currPosition = bug.getPosition();
        
        //check if circle is completed, but only if we've started circling already
        // std::cout << "check if done" << std::endl;
        if (currPosition == stopPosition && init) {
            bug.circling(false);
            // std::cout << "reached stop position (C)" << std::endl;
            break;
        
        } else {
            // std::cout << "circle step: ";
            //NEW CIRCLING ALGORITHM
            std::string prevMove = bug.getPrevMove();
            int right = bug.checkRight();
            int down = bug.checkDown();
            int left = bug.checkLeft();
            int up = bug.checkUp();

            //modify the initial step of the circle from previous logic
            if (!init && !returnCondition) {
                if (prevMove == "up") {
                    if (left == 0) {
                        bug.moveLeft();
                    } else if (down == 0) {
                        bug.moveDown();
                    } else {
                        bug.moveRight();
                    }
                } else if (prevMove == "right") {
                    if (up == 0) {
                        bug.moveUp();
                    } else if (left == 0) {
                        bug.moveLeft();
                    } else {
                        bug.moveDown();
                    }
                } else if (prevMove == "down") {
                    if (right == 0) {
                        bug.moveRight();
                    } else if (up == 0) {
                        bug.moveUp();
                    } else {
                        bug.moveLeft();
                    }
                } else if (prevMove == "left") {
                    if (down == 0) {
                        bug.moveDown();
                    } else if (right == 0) {
                        bug.moveRight();
                    } else {
                        bug.moveUp();
                    }
                }
                init = true;
                circlePath.push_back(bug.getPosition());
                continue;
            }

            //OLD INITIAL LOGIC (inconsistent)
            //only initialize circling if we hit the obstacle head on
            //if we are in the returning pass, the bug just completed a full circle, so the previous direction already works with the default algorithm
            //handle if an obstacle is hit immediately when starting (path is empty)
            // if (start == false && path.size() == 1) {
            //     if (bug.checkDown() != 0) {
            //         bug.moveRight();
            //     } else if (bug.checkLeft() != 0) {
            //         bug.moveDown();
            //     } else if (bug.checkRight() != 0) {
            //         bug.moveUp();
            //     } else if (bug.checkUp() != 0) {
            //         bug.moveLeft();
            //     } else {
            //         std::cout << "all paths clear" << std::endl;
            //         return circlePath;
            //     }
            //     start=true;
            //     currPosition = bug.getPosition();
            //     circlePath.push_back(currPosition);
            //     continue;
            // }
            // if (start == false && returnCondition) {
            //     //initialize circling immediately after obstacle hit
            //     if (prevMove == "up") {
            //         bug.moveDown();
            //     } else if (prevMove == "right") {
            //         bug.moveLeft();
            //     } else if (prevMove == "down") {
            //         bug.moveUp();
            //     } else if (prevMove == "left") {
            //         bug.moveRight();
            //     }
            //     start = true;
            //     returnCondition = false;
            //     currPosition = bug.getPosition();
            //     circlePath.push_back(currPosition);
            //     continue;
            // }
            init = true;

            if (prevMove == "up") {
                if (right == 0) {
                    bug.moveRight();
                } else if (up == 0) {
                    bug.moveUp();
                } else if (left == 0) {
                    bug.moveLeft();
                } else {
                    bug.moveDown();
                }
            } else if (prevMove == "right") {
                if (down == 0) {
                    bug.moveDown();
                } else if (right == 0) {
                    bug.moveRight();
                } else if (up == 0) {
                    bug.moveUp();
                } else {
                    bug.moveLeft();
                }
            } else if (prevMove == "down") {
                if (left == 0) {
                    bug.moveLeft();
                } else if (down == 0) {
                    bug.moveDown();
                } else if (right == 0) {
                    bug.moveRight();
                } else {
                    bug.moveUp();
                }
            } else if (prevMove == "left") {
                if (up == 0) {
                    bug.moveUp();
                } else if (left == 0) {
                    bug.moveLeft();
                } else if (down == 0) {
                    bug.moveDown();
                } else {
                    bug.moveRight();
                }
            } else {
                //obstacle is lost somehow
                std::cout << "obstacle lost while circling somehow (C)" << std::endl;
            }
            // std::cout << "(" << bug.getPosition().first << ", " << bug.getPosition().second << ")" << std::endl;
        }
        currPosition = bug.getPosition();
        // std::cout << "(C) currPos: (" << currPosition.first << ", " << currPosition.second << ")" << std::endl;
        circlePath.push_back(currPosition);
    }
    // std::cout << "circling successful (C)" << std::endl;
    std::pair<int, int> temp_cp = bug.getClosestPoint();
    // std::cout << "(C) current closest position: (" << temp_cp.first << ", " << temp_cp.second << ")" << std::endl;
    return circlePath;
}

std::string BugNav1::getDesiredDirection() {
    int yError = target.first - bug.getPosition().first;
    int xError = target.second - bug.getPosition().second;

    if (std::abs(yError) > std::abs(xError)) {
        if (yError < 0) {
            return "up";
        } else {
            return "down";
        }
    } else {
        if (xError < 0) {
            return "left";
        } else {
            return "right";
        }
    }
}