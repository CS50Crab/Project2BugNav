#pragma once
#include <vector>
#include "Tile.h"

class Map {
    private:
        std::vector<std::vector<Tile>> map;
        int mapDensity; //1-100
        int wallFactor; //default 4 (to be tuned)
        int width;
        int height;

    public:
        Map();
        Map(int density, int width, int height);
        void generateMap();
        void smoothMap(int iterations);
        void print();
        int checkSurroundingTiles(int r, int c);
        std::vector<std::vector<Tile>> getMap();

};