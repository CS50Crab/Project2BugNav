#include "BugNav1.h"

BugNav1::BugNav1() {
    map = {{}};
    bug = Bug();
}
BugNav1::BugNav1(std::vector<std::vector<Tile>> m_map, std::vector<int> m_start, std::vector<int> m_target) {
    map = m_map;
    bug = Bug(m_map, m_start, m_start, m_target);
}
//implementation of the bug 1 algorithm
std::vector<std::pair<int, int>> BugNav1::findGoal() {
    std::vector<std::pair<int, int>> path;
    
    while (bug.getPosition() != target) {
        std::vector<int> currPosition = bug.getPosition();
        //exit if the map is unsolveable:
        //case 1: bug is surrounded on all immediate sides
        if ((bug.checkDown() != 0) && (bug.checkLeft() != 0) && (bug.checkRight() != 0) && (bug.checkUp() != 0)) {
            return {{currPosition.at(0), currPosition.at(1)}};
        } else {
            //try to move towards target:
            int movementResult = moveTowardsTarget();
            //check the result of the movement, if it was successful, update the path, and start the loop over
            if (movementResult == 0) {
                path.push_back({bug.getPosition().at(0), bug.getPosition().at(1)});
                continue;
            } else {
                //if movement result is not 0, that means something blocked the path.
                if (movementResult == 2) {
                    //start circling the perimeter
                    bug.circling(true);

                } else {
                    //for some reason, the bug thinks its at the edge of the map
                }
            }
        }
        
    }
}

//returns similar to the bug.move functions. returns 0 if successful, 1 or 2 if blocked
//since, when moving towards the goal, the bug should technically never try to go into the edge of the map, I would expect a return of 0 or 2
int BugNav1::moveTowardsTarget() {
    std::vector<int> currPosition = bug.getPosition();
    //calculate what direction the bug must go in
    int xError = target.at(0) - currPosition.at(0);
    int yError = target.at(1) - currPosition.at(1);
    //decide which direction the bug must go in based on the which error is bigger
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
}