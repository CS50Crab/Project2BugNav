#pragma once

class Tile {
    private:
        bool passable;
        bool visited;

    public:
        Tile();
        bool isPassable();
        void setPassable(bool m_passable);
        void visit();
};