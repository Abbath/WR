#include "coords.hpp"

Coords::Coords() : Coords(0, 0) {
    
}

Coords::Coords(int i, int j) {
    coords = normalize(std::make_pair(i, j));
}

Coords::Coords(std::pair<int, int> p) : coords(normalize(p)) {
}

void Coords::set(std::pair<int, int> c) {
    coords = normalize(c);
}

void Coords::setX(int x) {
    coords.first = normalize(std::make_pair(x, coords.second)).first;
}

void Coords::setY(int y) {
    coords.second = normalize(std::make_pair(coords.first, y)).second;    
}

Coords Coords::operator+(std::pair<int, int> p) {
    return Coords(std::make_pair(coords.first + p.first, coords.second + p.second));
}

Coords& Coords::operator+=(std::pair<int, int> p) {
    coords = normalize(std::make_pair(coords.first + p.first, coords.second + p.second));
    return *this;
}

bool Coords::operator!=(const Coords &c) {
    return coords.first != c.coords.first || coords.second != c.coords.second;
}

std::pair<int, int> Coords::normalize(std::pair<int, int> c) {
    if(c.first < 0) {
        c.first = FIELD_WIDTH - 1;
    } else if(c.first >= FIELD_WIDTH) {
        c.first = 0;
    }

    if(c.second < 0) {
        c.second = FIELD_HEIGHT - 1;
    } else if(c.second >= FIELD_HEIGHT) {
        c.second = 0;
    }

    return c;
}

void Coords::fixCoords(int& newx, int& newy) {
    if(newx < 0) {
        newx = FIELD_WIDTH - 1;
    } else if(newx > FIELD_WIDTH - 1) {
        newx = 0;
    }

    if(newy < 0) {
        newy = FIELD_HEIGHT - 1;
    } else if(newy > FIELD_HEIGHT - 1) {
        newy = 0;
    }
}
