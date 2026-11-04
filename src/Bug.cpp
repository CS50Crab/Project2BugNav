#include "Bug.h"
#include <cmath>
#include <iostream>

//constructors
Bug::Bug() 
    : map({{}}), currentPos({0,0}), startingPos({0,0}), targetPos({0,0}), isCircling(false), reachedGoal(false), currentClosestPoint({0,0}) {}

Bug::Bug(std::vector<std::vector<Tile>>& m_map, std::vector<int> m_current, std::vector<int> m_starting, std::vector<int> m_target)
    : map(m_map), currentPos(m_current), startingPos(m_starting), targetPos(m_target), isCircling(false), reachedGoal(false), currentClosestPoint(m_current) {}

//getters & setters
std::vector<int> Bug::getPosition() {
    return currentPos;
}
void Bug::setTarget(int x, int y) {
    targetPos = {x, y};
}
std::vector<int> Bug::getDistFromTarget() {
    //using goal - current
    int xdiff = targetPos.at(0) - currentPos.at(0);
    int ydiff = targetPos.at(1) - currentPos.at(1);
    return {xdiff, ydiff};
}
std::string Bug::getPrevMove() {
    return prevMove;
}
void Bug::circling(bool circling) {
    isCircling = circling;
    std::cout << "toggle circling obstacle" << std::endl;
}
bool Bug::getCircleState() {
    return isCircling;
}
std::vector<int> Bug::getClosestPoint() {
    return currentClosestPoint;
}

//movement
int Bug::moveUp() {
    //return 1 if at edge of map
    if (currentPos.at(0) == 0) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0) - 1).at(currentPos.at(1)).isPassable() == false) {
        return 2;
    //otherwise move up and return 0;
    } else {
        std::cout << "up" << std::endl;
        currentPos[0] = currentPos[0] - 1;
        prevMove = "up";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos[0] - currentPos[0], 2) + std::pow(targetPos[1] - currentPos[1], 2));
        double prevDist = std::sqrt(std::pow(targetPos[0] - currentClosestPoint[0], 2) + std::pow(targetPos[1] - currentClosestPoint[1], 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos[0], currentPos[1]};
        }
        return 0;
    }
}
int Bug::moveDown() {
    //return 1 if at edge of map
    if (currentPos.at(0) == map.size() - 1) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0) + 1).at(currentPos.at(1)).isPassable() == false) {
        return 2;
    //otherwise move down and return 0;
    } else {
        std::cout << "down" << std::endl;
        currentPos[0] = currentPos[0] + 1;
        prevMove = "down";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos[0] - currentPos[0], 2) + std::pow(targetPos[1] - currentPos[1], 2));
        double prevDist = std::sqrt(std::pow(targetPos[0] - currentClosestPoint[0], 2) + std::pow(targetPos[1] - currentClosestPoint[1], 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos[0], currentPos[1]};
        }
        return 0;
    }
}
int Bug::moveLeft() {
    //return 1 if at edge of map
    if (currentPos.at(1) == 0) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0)).at(currentPos.at(1) - 1).isPassable() == false) {
        return 2;
    //otherwise move left and return 0;
    } else {
        std::cout << "left" << std::endl;
        currentPos[1] = currentPos[1] - 1;
        prevMove = "left";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos[0] - currentPos[0], 2) + std::pow(targetPos[1] - currentPos[1], 2));
        double prevDist = std::sqrt(std::pow(targetPos[0] - currentClosestPoint[0], 2) + std::pow(targetPos[1] - currentClosestPoint[1], 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos[0], currentPos[1]};
        }
        return 0;
    }
}
int Bug::moveRight() {
    //return 1 if at edge of map
    if (currentPos.at(1) == map.at(0).size() - 1) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0)).at(currentPos.at(1) + 1).isPassable() == false) {
        return 2;
    //otherwise move right and return 0;
    } else {
        std::cout << "right" << std::endl;
        currentPos[1] = currentPos[1] + 1;
        prevMove = "right";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos[0] - currentPos[0], 2) + std::pow(targetPos[1] - currentPos[1], 2));
        double prevDist = std::sqrt(std::pow(targetPos[0] - currentClosestPoint[0], 2) + std::pow(targetPos[1] - currentClosestPoint[1], 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos[0], currentPos[1]};
        }
        return 0;
    }
}

int Bug::checkUp() {
    //return 1 if at edge of map
    if (currentPos.at(0) == 0) {
        std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0) - 1).at(currentPos.at(1)).isPassable() == false) {
        std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkDown() {
    //return 1 if at edge of map
    if (currentPos.at(0) == map.size() - 1) {
        std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0) + 1).at(currentPos.at(1)).isPassable() == false) {
        std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkLeft() {
    //return 1 if at edge of map
    if (currentPos.at(1) == 0) {
        std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0)).at(currentPos.at(1) - 1).isPassable() == false) {
        std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkRight() {
    //return 1 if at edge of map
    if (currentPos.at(1) == map.at(0).size() - 1) {
        std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.at(0)).at(currentPos.at(1) + 1).isPassable() == false) {
        std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        std::cout << "passable" << std::endl;
       return 0;
    }
}