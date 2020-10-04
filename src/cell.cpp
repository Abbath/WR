#include "cell.hpp"

bool Cell::detectCreaturesSmell(const Smells& smells, int index) const
{
    if ( smells.empty() ) { return false; }
    if ( smells.find(index) == smells.end() ) { return true; }
    if ( ( smells.find(index) != smells.end() ) && smells.size() > 1 ) { return true; }    
    return false;
}

bool Cell::getRabbitWasHere(int index) const
{
    return detectCreaturesSmell(rabbitSmells, index);
}

bool Cell::getWolfWasHere(int index) const
{
    return detectCreaturesSmell(wolfSmells, index);
}

void Cell::setRabbitWasHere(bool value, int index)
{
    if(value){
        rabbitSmells[index] = RABBIT_SMELL_TIME;
        totalSmell += RABBIT_SMELL_TIME;
    }else{
        rabbitSmells.clear();
        totalSmell = 0;
    }
}

void Cell::removeRabbitIndexes(const Indexes &indexes)
{
    for(auto& x : indexes){
        rabbitIndexes.erase(x);
    }
}

void Cell::removeWolfIndexes(const Indexes &indexes)
{
    for(auto& x : indexes){
        wolfIndexes.erase(x);
    }
}

unsigned Cell::getTotalSmell() const
{
    return totalSmell;
}

void Cell::setTotalSmell(const unsigned &value)
{
    totalSmell = value;
}

Cell::Cell(): totalSmell(0),  grass(GRASS_PER_CELL) {
    
}

Indexes Cell::getWolfIndexes() const
{
    return wolfIndexes;
}

size_t Cell::getWolfIndexesSize() const
{
    return wolfIndexes.size();
}

void Cell::decreaseWolfSmell()
{
    Indexes itdw;
    for (auto it = wolfSmells.begin(); it != wolfSmells.end(); ++it) {
        if(it->second){
            it->second--;
            totalSmell = totalSmell ? totalSmell - 1 : totalSmell;
        }else{
            itdw.insert(it->first);
        }
    }
    for(auto it = itdw.cbegin(); it  !=  itdw.cend(); ++it){
        wolfSmells.erase(*it);
    }
}

void Cell::decreaseRabbitSmell()
{
    Indexes itdr;
    for(auto it = rabbitSmells.begin(); it != rabbitSmells.end(); ++it){        
        if(it->second){ 
            it->second--;
            totalSmell = totalSmell ? totalSmell - 1 : totalSmell;
        }
        else{ 
            itdr.insert(it->first);
        }
    }
    for(auto it = itdr.cbegin(); it != itdr.cend(); ++it){
        rabbitSmells.erase(*it);
    }
}

void Cell::growGrass()
{
    if(grass < GRASS_PER_CELL) {
        grass+=3;
    }
}

void Cell::eatGrass()
{
    if(grass > GRASS_PER_RABBIT) {
        grass-=GRASS_PER_RABBIT;
    } else {
        grass = 0;
    }
}

void Cell::setWolfIndexes(const Indexes &value)
{
    wolfIndexes = value;
}

Indexes Cell::getRabbitIndexes() const
{
    return rabbitIndexes;
}

size_t Cell::getRabbitIndexesSize() const
{
    return rabbitIndexes.size();
}

void Cell::setRabbitIndexes(const Indexes &value)
{
    rabbitIndexes = value;
}

void Cell::removeWolfIndex(int index){
    wolfIndexes.erase(index);
}

void Cell::removeRabbitIndex(int index){
    rabbitIndexes.erase(index);
}

int Cell::getFirstRabbitIndex() const {
    return *(rabbitIndexes.begin()); 
}

void Cell::removeFirstRabbitIndex() { 
    rabbitIndexes.erase(rabbitIndexes.begin());
}


void Cell::setWolfWasHere(bool value, int index)
{
    if(value){
        wolfSmells[index] = WOLF_SMELL_TIME;
        totalSmell += WOLF_SMELL_TIME;
    }else{
        wolfSmells.clear();
        totalSmell = 0;
    }
}

void Cell::addPredator(int index){ 
    wolfIndexes.insert(index);
}

void Cell::addVictim(int index){ 
    rabbitIndexes.insert(index); 
}

bool Cell::isThereGrass() const
{
    return grass >= GRASS_PER_RABBIT;
}

void Cell::setGrass(bool value)
{
    grass = value;
}
