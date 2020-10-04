#ifndef WOLF_HPP
#define WOLF_HPP

#include "creature.hpp"

class Wolf : public Creature{
public:
    Wolf();
    void makePregnant();   
    void step();
    void eat();
    bool isAlive();  
    bool operator ==(const Wolf& w);    
    bool operator !=(const Wolf& w);
};

#endif // WOLF_HPP
