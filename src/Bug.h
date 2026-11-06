#pragma once
#include <vector>
#include <string>
#include "Tile.h"

//class to create the bug itself
//i've added attributes that i will need for bug 1
//there may or may not be additional attributes needed for bug 2
class Bug {
    private:
        //current, starting, and target position
        // std::vector<int> currentPos; //{x, y}
        // std::vector<int> startingPos; //{x, y}
        // std::vector<int> targetPos; //{x, y}

        std::pair<int, int> currentPos;
        std::pair<int, int> startingPos;
        std::pair<int, int> targetPos;
        //bug states
        bool isCircling; //whether or not the bug is currently circling an obstacle's perimeter
        bool reachedGoal;

        std::vector<std::vector<Tile>> map; //map

        //saving information gathered during navigation
        std::string prevMove; //bugs previous move
        // std::vector<int> currentClosestPoint;

        std::pair<int, int> currentClosestPoint;

    public:
        //constructor
        Bug();
        Bug(std::vector<std::vector<Tile>>& m_map, std::pair<int, int> m_starting, std::pair<int, int> m_target);
        
        //getters/setters
        std::pair<int, int> getPosition(); //current position
        void setTarget(int x, int y); //sets target
        std::pair<int, int> getDistFromTarget(); //return the x and y difference from the target position
        std::string getPrevMove(); //returns the previous move the bug made
        void setPrevMove(std::string m_prevMove); //maually alter what the previous move of the bug was
        void circling(bool circling);
        bool getCircleState();
        std::pair<int, int> getClosestPoint();

        //movement
        /*
        these functions return an int.
        0- path not blocked/move successful
        1- path blocked-> edge of map
        2- path blocked-> obstacle
        */
        int moveUp();
        int moveDown();
        int moveLeft();
        int moveRight();

        //checking adjacent tiles
        /*
        these functions return an int.
        these functions return an int.
        0- path not blocked
        1- path blocked-> edge of map
        2- path blocked-> obstacle
        */
        int checkUp();
        int checkDown();
        int checkLeft();
        int checkRight();
};
