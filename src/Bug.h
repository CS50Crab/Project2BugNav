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
        std::vector<int> currentPos; //{x, y}
        std::vector<int> startingPos; //{x, y}
        std::vector<int> targetPos; //{x, y}
        //bug states
        bool isCircling; //whether or not the bug is currently circling an obstacle's perimeter
        bool reachedGoal;

        std::vector<std::vector<Tile>> map; //map

        //saving information gathered during navigation
        std::string prevMove; //bugs previous move
        std::vector<int> currentClosestPoint;

    public:
        //constructor
        Bug();
        Bug(std::vector<std::vector<Tile>>& m_map, std::vector<int> m_current, std::vector<int> m_starting, std::vector<int> m_target);
        
        //getters/setters
        std::vector<int> getPosition(); //current position
        void setTarget(int x, int y); //sets target
        std::vector<int> getDistFromTarget(); //return the x and y difference from the target position
        std::string getPrevMove(); //returns the previous move the bug made
        void circling(bool circling);

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
