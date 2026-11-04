#include "Bug.h"
#include <cmath>
#include <iostream>

//constructors
Bug::Bug() 
    : map({{}}), currentPos({0,0}), startingPos({0,0}), targetPos({0,0}), isCircling(false), reachedGoal(false), currentClosestPoint({0,0}) {}

Bug::Bug(std::vector<std::vector<Tile>>& m_map, std::pair<int, int> m_starting, std::pair<int, int> m_target)
    : map(m_map), currentPos(m_starting), startingPos(m_starting), targetPos(m_target), isCircling(false), reachedGoal(false), currentClosestPoint(m_starting) {}

//getters & setters
std::pair<int, int> Bug::getPosition() {
    return currentPos;
}
void Bug::setTarget(int x, int y) {
    targetPos = {x, y};
}
std::pair<int, int> Bug::getDistFromTarget() {
    //using goal - current
    int xdiff = targetPos.first - currentPos.first;
    int ydiff = targetPos.second - currentPos.second;
    return {xdiff, ydiff};
}
std::string Bug::getPrevMove() {
    return prevMove;
}
void Bug::setPrevMove(std::string m_prevMove) {
    prevMove = m_prevMove;
}
void Bug::circling(bool circling) {
    isCircling = circling;
    //std::cout << "toggle circling obstacle" << std::endl;
}
bool Bug::getCircleState() {
    return isCircling;
}
std::pair<int, int> Bug::getClosestPoint() {
    return currentClosestPoint;
}

//movement
int Bug::moveUp() {
    //return 1 if at edge of map
    if (currentPos.first == 0) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first - 1).at(currentPos.second).isPassable() == false) {
        return 2;
    //otherwise move up and return 0;
    } else {
        // std::cout << "up" << std::endl;
        currentPos.first = currentPos.first - 1;
        prevMove = "up";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos.first - currentPos.first, 2) + std::pow(targetPos.second - currentPos.second, 2));
        double prevDist = std::sqrt(std::pow(targetPos.first - currentClosestPoint.first, 2) + std::pow(targetPos.second - currentClosestPoint.second, 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos.first, currentPos.second};
        }
        return 0;
    }
}
int Bug::moveDown() {
    //return 1 if at edge of map
    if (currentPos.first == map.size() - 1) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first + 1).at(currentPos.second).isPassable() == false) {
        return 2;
    //otherwise move down and return 0;
    } else {
        // std::cout << "down" << std::endl;
        currentPos.first = currentPos.first + 1;
        prevMove = "down";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos.first - currentPos.first, 2) + std::pow(targetPos.second - currentPos.second, 2));
        double prevDist = std::sqrt(std::pow(targetPos.first - currentClosestPoint.first, 2) + std::pow(targetPos.second - currentClosestPoint.second, 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos.first, currentPos.second};
        }
        return 0;
    }
}
int Bug::moveLeft() {
    //return 1 if at edge of map
    if (currentPos.second == 0) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first).at(currentPos.second - 1).isPassable() == false) {
        return 2;
    //otherwise move left and return 0;
    } else {
        // std::cout << "left" << std::endl;
        currentPos.second = currentPos.second - 1;
        prevMove = "left";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos.first - currentPos.first, 2) + std::pow(targetPos.second - currentPos.second, 2));
        double prevDist = std::sqrt(std::pow(targetPos.first - currentClosestPoint.first, 2) + std::pow(targetPos.second - currentClosestPoint.second, 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos.first, currentPos.second};
        }
        return 0;
    }
}
int Bug::moveRight() {
    //return 1 if at edge of map
    if (currentPos.second == map.at(0).size() - 1) {
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first).at(currentPos.second + 1).isPassable() == false) {
        return 2;
    //otherwise move right and return 0;
    } else {
        // std::cout << "right" << std::endl;
        currentPos.second = currentPos.second + 1;
        prevMove = "right";
        //update closest point
        double newDist = std::sqrt(std::pow(targetPos.first - currentPos.first, 2) + std::pow(targetPos.second - currentPos.second, 2));
        double prevDist = std::sqrt(std::pow(targetPos.first - currentClosestPoint.first, 2) + std::pow(targetPos.second - currentClosestPoint.second, 2));
        if (newDist < prevDist) {
            currentClosestPoint = {currentPos.first, currentPos.second};
        }
        return 0;
    }
}

int Bug::checkUp() {
    //return 1 if at edge of map
    if (currentPos.first == 0) {
        // std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first - 1).at(currentPos.second).isPassable() == false) {
        // std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        // std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkDown() {
    //return 1 if at edge of map
    if (currentPos.first == map.size() - 1) {
        // std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first + 1).at(currentPos.second).isPassable() == false) {
        // std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        // std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkLeft() {
    //return 1 if at edge of map
    if (currentPos.second == 0) {
        // std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first).at(currentPos.second - 1).isPassable() == false) {
        // std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        // std::cout << "passable" << std::endl;
        return 0;
    }
}
int Bug::checkRight() {
    //return 1 if at edge of map
    if (currentPos.second == map.at(0).size() - 1) {
        // std::cout << "edge" << std::endl;
        return 1;
    //return 2 if blocked by obstacle
    } else if (map.at(currentPos.first).at(currentPos.second + 1).isPassable() == false) {
        // std::cout << "obstacle" << std::endl;
        return 2;
    //otherwise return 0;
    } else {
        // std::cout << "passable" << std::endl;
       return 0;
    }
}