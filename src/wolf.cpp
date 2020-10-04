#include "wolf.hpp"
#include "field.hpp"
#include "randomgenerator.hpp"

Wolf::Wolf() : Creature(WOLF_START_HUNGRY){}

void Wolf::makePregnant(){ 
    if(pregnancyTime == 0 && !male && age > 365*1.3) pregnancyTime = WOLF_PREGNANCY_TIME; 
}

void Wolf::step(){ 
    static std::pair<int, int> direction = {1, 1};    
    if(pregnancyTime)pregnancyTime--;
    hungry--;
    age++; 
    for(int i = 0; i < 8; ++i){
        int newx = coords.x() + (RandomGenerator::dice() % 3 - 1);
        int newy = coords.y() + (RandomGenerator::dice() % 3 - 1);
        Coords::fixCoords(newx, newy);
        if(field->wasRabbitHere({newx, newy}) ||
           field->getCreatureCell({newx, newy}).getRabbitIndexes().size() > 0){
            field->getCell(coords).removeWolfIndex(idx);
            coords = Coords{newx, newy};
            field->getCell(coords).addPredator(idx);
            field->wolfWasHere(coords, idx);
            return; 
        }
        for(int i = 0; i < 3; ++i){
            int newx = coords.x() + (RandomGenerator::dice() % 3 - 1);
            int newy = coords.y() + (RandomGenerator::dice() % 3 - 1);
            Coords::fixCoords(newx, newy);
            if(field->wasWolfHere(std::pair{newx, newy}, idx)){
                field->getCell(coords).removeWolfIndex(idx);
                coords = Coords{newx, newy};
                field->getCell(coords).addPredator(idx);
                field->wolfWasHere(coords, idx); 
                return;
            }
        }
        if(RandomGenerator::dice() < std::numeric_limits<int>::max() / 50.0){
            direction = {rand() % 3 - 1, rand() % 3 - 1};
        }
        field->getCell(coords).removeWolfIndex(idx);
        coords += direction;
        field->getCell(coords).addPredator(idx);
        field->wolfWasHere(coords, idx);    
    }
}

void Wolf::eat()
{
    if(hungry < WOLF_START_HUNGRY) hungry+=4*9;
}

bool Wolf::isAlive() {
    return hungry > 0 && age <= WOLF_MAX_AGE;
}

bool Wolf::operator ==(const Wolf &w){ 
    return this->idx == w.idx;
}

bool Wolf::operator !=(const Wolf &w){
    return this->idx != w.idx;
}
