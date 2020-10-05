#include "creature.hpp"
#include "field.hpp"
#include <cassert>

int Creature::getAge() const {
    return age;
}

int Creature::getid() {
    static int id = 0;
    return id++;
}

Creature::Creature(int _hungry) : idx(getid()), male(RandomGenerator::dice() % 2), hungry(_hungry), age(0), pregnancyTime(0) {
    
}

bool Creature::timeToGiveBirth() {
    return pregnancyTime == 1;
}

void Creature::eat() { 
    hungry++; 
}

int Creature::getId() const {
    return idx;
}

bool Creature::operator ==(const Creature &r) { 
    return this->idx == r.idx;
}

bool Creature::operator !=(const Creature &r) { 
    return this->idx != r.idx;
} 

bool Creature::isMale() const
{
    return male;
}

void Creature::setIsMale(bool value) {
    male = value;
}

int Creature::getParentId() const
{
    return parentId;
}

void Creature::setParentId(int value) {
    parentId = value;
}

Field *Creature::getField() const
{
    return field;
}

void Creature::setField(Field *value) {
    assert(value);
    field = value;
}

bool Creature::isHungry() {
    return hungry < WOLF_START_HUNGRY;
}
Coords Creature::getCoords() const
{
    return coords;
}

void Creature::setCoords(const Coords &value) {
    coords = value;
}

