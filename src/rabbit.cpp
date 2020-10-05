#include "rabbit.hpp"
#include "field.hpp"

Rabbit::Rabbit() : Creature(RABBIT_START_HUNGRY) {}

void Rabbit::makePregnant() { 
    if(pregnancyTime == 0 && !male && age > 365) pregnancyTime = RABBIT_PREGNANCY_TIME; 
}

void Rabbit::eat() {
    if(hungry < RABBIT_START_HUNGRY) hungry+=4*2;
}

void Rabbit::step() { 
    static std::pair<int, int> direction = {1, 1};
    if(pregnancyTime)pregnancyTime--; 
    hungry--; 
    age++;
    if(!field->getCell(coords).isThereGrass() || field->getCell(coords).getRabbitIndexes().size() < 2) {
        for(int i = 0; i < 8; ++i) {
            int a = rand() % 3 - 1;
            int b = rand() % 3 - 1;
            int newx = coords.x() + a;
            int newy = coords.y() + b;
            Coords::fixCoords(newx, newy);
            if(field->wasWolfHere({newx, newy}) ||
                    field->getCreatureCell({newx, newy}).getWolfIndexes().size() > 0) {
                field->getCell(coords).removeRabbitIndex(idx);
                coords = Coords{coords.x() - a, coords.y() - b};
                field->getCell(coords).addVictim(idx);
                field->rabbitWasHere(coords, idx);
                return;
            }
        }
        for(int i = 0; i < 8; ++i) {
            int newx = coords.x() + (rand() % 3 - 1);
            int newy = coords.y() + (rand() % 3 - 1);
            Coords::fixCoords(newx, newy);
            if(field->getCell(coords).isThereGrass()) {
                field->getCell(coords).removeRabbitIndex(idx);
                coords = Coords{newx, newy};
                field->getCell(coords).addVictim(idx);
                field->rabbitWasHere(coords, idx); 
                return;
            }
        }
        for(int i = 0; i < 8; ++i) {
            int newx = coords.x() + (rand() % 3 - 1);
            int newy = coords.y() + (rand() % 3 - 1);
            Coords::fixCoords(newx, newy);
            if(field->wasRabbitHere({newx, newy}, idx)) {
                field->getCell(coords).removeRabbitIndex(idx);
                coords = Coords{newx, newy};
                field->getCell(coords).addVictim(idx);
                field->rabbitWasHere(coords, idx); 
                return;
            }
        }
    }
    if(rand() < std::numeric_limits<int>::max() / 7.0) {
        direction = {rand() % 3 - 1 , rand() % 3 - 1};
    }
    field->getCell(coords).removeRabbitIndex(idx);
    coords += direction;
    field->getCell(coords).addVictim(idx);
    field->rabbitWasHere(coords, idx);
}

bool Rabbit::isAlive() {
    return hungry > 0 && age <= RABBIT_MAX_AGE;
}

bool Rabbit::operator ==(const Rabbit &r) { 
    return this->idx == r.idx;
}

bool Rabbit::operator !=(const Rabbit &r) { 
    return this->idx != r.idx;
}
