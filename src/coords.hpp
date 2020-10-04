#ifndef COORDS_HPP
#define COORDS_HPP

#include "defs.hpp"

class Coords
{
public:
    Coords();
    Coords(int i, int j);
    Coords(std::pair< int, int> p);
    unsigned x(){ return coords.first; }
    unsigned y(){ return coords.second; }
    void set(std::pair<int, int> c);
    void setX(int x);
    void setY(int y);
    Coords operator+(std::pair<int, int> p);
    Coords& operator+=(std::pair<int, int> p);
    bool operator!=(const Coords& c);
    static void fixCoords(int &newx, int &newy);
private:
    static std::pair<int, int> normalize(std::pair<int, int> c);
    std::pair<unsigned , unsigned> coords;
};

#endif // COORDS_HPP
