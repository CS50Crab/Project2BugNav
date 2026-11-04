#include "BugNav1.h"
#include <iostream>

BugNav1::BugNav1() {
    map = {};
    bug = Bug();
}
BugNav1::BugNav1(std::vector<std::vector<Tile>> m_map, std::vector<int> m_start, std::vector<int> m_target) {
    map = m_map;
    bug = Bug(m_map, m_start, m_start, m_target);
    target = m_target;
    start = m_start;
}
//implementation of the bug 1 algorithm
std::vector<std::pair<int, int>> BugNav1::findPath() {    
    std::vector<std::pair<int, int>> path = {};
    std::cout << "starting Bug1 algorithm" << std::endl;
    
    while (bug.getPosition() != target) {
        std::cout << "get current position" << std::endl;
        std::vector<int> currPosition = bug.getPosition();
        //exit if the map is unsolveable:
        //case 1: bug is surrounded on all immediate sides
        std::cout << "checking all sides" << std::endl;
        if ((bug.checkDown() != 0) && (bug.checkLeft() != 0) && (bug.checkRight() != 0) && (bug.checkUp() != 0)) {
            std::cout << "map unsolveable" << std::endl;
            return {{currPosition.at(0), currPosition.at(1)}};
        } else {
            std::cout << "not immediately surrounded" << std::endl;
            //try to move towards target:
            std::cout << "Trying: move towards target" << std::endl;
            int movementResult = moveTowardsTarget();
            //check the result of the movement, if it was successful, update the path, and start the loop over
            if (movementResult == 0) {
                std::cout << "movement successful" << std::endl;
                path.push_back({bug.getPosition().at(0), bug.getPosition().at(1)});
                continue;
            } else {
                std::cout << "movement unsuccessful" << std::endl;
                //if movement result is not 0, that means something blocked the path.
                if (movementResult == 2) {
                    //circle the perimeter
                    bug.circling(true);
                    std::cout << "Trying: circling obstacle" << std::endl;
                    std::vector<std::pair<int, int>> circlePath = circlePerimeter(bug.getPosition());
                    path.insert(path.end(), circlePath.begin(), circlePath.end());
                    //return to the closest point
                    bug.circling(true);
                    std::cout << "Trying: return to closest point" << std::endl;
                    circlePath = circlePerimeter(bug.getClosestPoint());
                    path.insert(path.end(), circlePath.begin(), circlePath.end());
                } else {
                    //for some reason, the bug thinks its at the edge of the map
                    std::cout << "Error: blocked by edge of map" << std::endl;
                }
            }
        }
        
    }
    std::cout << "success" << std::endl;
    return path;
}

//returns similar to the bug.move functions. returns 0 if successful, 1 or 2 if blocked
//since, when moving towards the goal, the bug should technically never try to go into the edge of the map, I would expect a return of 0 or 2
int BugNav1::moveTowardsTarget() {
    std::cout << "get current position (M): ";
    std::vector<int> currPosition = bug.getPosition();
    std::cout << "(" << currPosition.at(0) << ", " << currPosition.at(1) << std::endl;
    //calculate what direction the bug must go in
    //std::cout << "access index 0 and 1 of current position (M)" << std::endl;

    // int targetX = target.at(0);
    // int targetY = target.at(1);
    // int currX = currPosition.at(0);
    // int currY = currPosition.at(1);

    int xError = target.at(0) - currPosition.at(0);
    int yError = target.at(1) - currPosition.at(1);

    //decide which direction the bug must go in based on the which error is bigger
    std::cout << "Trying: moving (M)" << std::endl;
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

std::vector<std::pair<int, int>> BugNav1::circlePerimeter(std::vector<int> stopPosition) {
    //TODO- implement
    std::vector<std::pair<int, int>> path = {};
    std::cout << "getting current position (C)" << std::endl;
    std::vector<int> currPosition = bug.getPosition();
    bool start = false;
    while(bug.getCircleState()) {
        // std::vector<int> currPosition = bug.getPosition();
        if (currPosition == stopPosition && start) {
            bug.circling(false);
            std::cout << "reached stop position (C)" << std::endl;
            break;
        } else {
            start = true;
            //should handle inside corners / obstacle edges
            if ((bug.checkRight() != 0) && (bug.checkUp() == 0)) {
                bug.moveUp();
            } else if ((bug.checkDown() != 0) && (bug.checkRight() == 0)) {
                bug.moveRight();
            } else if ((bug.checkLeft() != 0) && (bug.checkDown() == 0)) {
                bug.moveDown();
            } else if ((bug.checkUp() != 0) && (bug.checkLeft() == 0)) {
                bug.moveLeft();
            } else {
                //not edge/inside corner = outside corner
                if ((bug.getPrevMove() == "up") && (bug.checkRight() == 0)) {
                    bug.moveRight();
                } else if ((bug.getPrevMove() == "right") && (bug.checkDown() == 0)) {
                    bug.moveDown();
                } else if ((bug.getPrevMove() == "down") && (bug.checkLeft() == 0)) {
                    bug.moveLeft();
                } else if ((bug.getPrevMove() == "left") && (bug.checkUp() == 0)) {
                    bug.moveUp();
                } else {
                    //obstacle is lost somehow
                    std::cout << "obstacle lost while circling somehow (C)" << std::endl;
                    std::cout << "(C) (" << currPosition.at(0) << ", " << currPosition.at(1) << ")" << std::endl;
                }
            }
            currPosition = bug.getPosition();
        }
        currPosition = bug.getPosition();
        // std::cout << "(C) currPos: ()" << currPosition.at(0) << ", " << currPosition.at(1) << ")" << std::endl;
        path.push_back({currPosition[0], currPosition[1]});
    }
    std::cout << "circling successful (C)" << std::endl;
    std::vector<int> temp_cp = bug.getClosestPoint();
    std::cout << "(C) current closest position: (" << temp_cp.at(0) << ", " << temp_cp.at(1) << ")" << std::endl;
    return path;
}