#ifndef RABBIT_HPP
#define RABBIT_HPP

#include "creature.hpp"

class Rabbit : public Creature{   
public:
    Rabbit();
    void makePregnant();
    void eat();
    void step();
    bool isAlive();   
    bool operator ==(const Rabbit& r);
    bool operator !=(const Rabbit& r);
};

#endif // RABBIT_HPP
