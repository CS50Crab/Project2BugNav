#include "Tile.h"

Tile::Tile() : passable(true), visited(false) {}

bool Tile::isPassable() {
    return passable;
}
void Tile::setPassable(bool m_passable) {
    passable = m_passable;
}
void Tile::visit() {
    visited = true;
}