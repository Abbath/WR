#include "field.hpp"
#include <QThread>

void Field::stop() {
    // printf("STOP\n");
    running.store(false, std::memory_order_relaxed);
}

Field::Field(QObject *parent) : QObject(parent), creaturesCounter(0), stepCounter(0) {  
    RandomGenerator::init();
    setAutoDelete(false);
    cells.resize(FIELD_WIDTH * FIELD_HEIGHT);
    generatePopulations();
    running.store(true, std::memory_order_relaxed);
    stopped.store(false, std::memory_order_relaxed);
}

Cell &Field::getCell(Coords c) {
    return cells[c.y() * FIELD_WIDTH + c.x()];
}

Cells &Field::getCells() {
    return cells;
}

bool Field::isEmpty() {
    return rabbits.size() < 3 && wolfs.size() < 3;
}

bool Field::noRabbits() {
    return rabbits.size() < 3;
}

bool Field::noWolfs() {
    return wolfs.size() < 3;
}

void Field::populateRabbits() {
    for (int i = 0; i < viCount; ++i) {
        Rabbit r;
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        r.setField(this);
        r.setCoords(Coords(std::make_pair(x,y)));
        rabbits[r.getId()] = r;
        cells[y * FIELD_WIDTH + x].addVictim(r.getId());
        creaturesCounter++;
        allCreatureCounter++;
    }
}

void Field::populateWolfs() {
    for (int i = 0; i < prCount; ++i) {
        Wolf w;
        int x = rand() % FIELD_WIDTH;
        int y = rand() % FIELD_HEIGHT;
        w.setField(this);
        w.setCoords(Coords(std::make_pair(x,y)));
        wolfs[w.getId()] = w;
        cells[y * FIELD_WIDTH + x].addPredator(w.getId());
        creaturesCounter++;
        allCreatureCounter++;
    }
}

void Field::generatePopulations() {
    populateWolfs();
    populateRabbits();
}

void Field::print() {
//    for (int i = 0; i < FIELD_WIDTH ; ++i) {
//        for (int j = 0; j < FIELD_HEIGHT; ++j) {
//            if(getCell(Coords(std::make_pair(i, j))).getWolfIndexes().size() &&
//                    getCell(Coords(std::make_pair(i, j))).getRabbitIndexes().size()) {
//                std::cout << "B";
//            }else if(getCell(Coords(std::make_pair(i, j))).getWolfIndexes().size()) {
//                std::cout << "W";
//            }else if(getCell(Coords(std::make_pair(i, j))).getRabbitIndexes().size()) {
//                std::cout << "R";
//            }else if(wasWolfHere(Coords(std::make_pair(i, j)))) {
//                std::cout << "!";
//            }else if(wasRabbitHere(Coords(std::make_pair(i,j)))) {
//                std::cout << "?";
//            }else if(getCell(Coords(std::make_pair(i, j))).isThereGrass()) {
//                std::cout << ",";
//            }else{
//                std::cout << ".";
//            }
//        }
//        std::cout << std::endl;
//    }
    std::cout << "Step: "<< stepCounter << 
                 " W: " << wolfs.size() << 
                 " R: " << rabbits.size() <<  
                 " CC: " << creaturesCounter <<
                 " AC: " << allCreatureCounter <<
                 " DW: " << deadWolfs << 
                 " DR: " << deadRabbits <<
                 " ER: " << eatenRabbits << std::endl;
}

void Field::fixCoords() {
    for(int i = 0; i < FIELD_WIDTH; ++i) {
        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            Cell& c =  cells[j * FIELD_WIDTH + i];
            const auto cached_pair = std::make_pair(i, j);
            Indexes itdw;
            for(int x : c.getWolfIndexes()) {
                if(wolfs[x].getCoords() != cached_pair) {
                    getCell(wolfs[x].getCoords()).addPredator(x);
                    itdw.insert(x);
                }
            }
            c.removeWolfIndexes(itdw);
            Indexes itdr;
            for(int x : c.getRabbitIndexes()) {
                if(rabbits[x].getCoords() != cached_pair) {
                    getCell(rabbits[x].getCoords()).addVictim(x);
                    itdr.insert(x);
                }
            }
            c.removeRabbitIndexes(itdr);
        }
    }
}

void Field::cleanDead(Indexes itdw, Indexes itdr) {
    for (int x : itdw) {
        getCell(wolfs[x].getCoords()).removeWolfIndex(x);
        wolfs.erase(x);
        creaturesCounter--;
        deadWolfs++;
    }
    for (int x : itdr) {
        getCell(rabbits[x].getCoords()).removeRabbitIndex(x);
        rabbits.erase(x);
        creaturesCounter--;
        deadRabbits++;
    }         
}

void Field::bornNew(const Indexes &neww, const Indexes &newr) {
    for (auto x : neww) {
        for(int i = 0; i < WOLF_CHILDREN_NUM; ++i ) {
            Wolf w;
            w.setParentId(x);
            w.setField(this);
            w.setCoords(wolfs[x].getCoords());
            wolfs[w.getId()] = w;
            getCell(w.getCoords()).addPredator(w.getId());
            creaturesCounter++;
            allCreatureCounter++;
        }
    }
    for (auto x : newr) {
        for(int i = 0; i < RABBIT_CHILDREN_NUM; ++i) {
            Rabbit r;
            r.setParentId(x);
            r.setField(this);
            r.setCoords(rabbits[x].getCoords());
            rabbits[r.getId()] = r;
            getCell(r.getCoords()).addVictim(r.getId());
            creaturesCounter++;
            allCreatureCounter++;
        }
    }
}

void Field::step() {
    for(int i = 0; i < FIELD_WIDTH; ++i) {
        for (int j = 0; j < FIELD_HEIGHT; ++j) {
            Cell &c =  cells[j * FIELD_WIDTH + i];
            c.growGrass();
            c.decreaseRabbitSmell();
            c.decreaseWolfSmell();
        }
    }
    Indexes itdw;
    Indexes neww;
    for(auto it = wolfs.begin(); it != wolfs.end(); ++it) {
        if(!it->second.isAlive()) {
            itdw.insert(it->first);
            continue;
        }
        Cell &c = getCell(it->second.getCoords());
        if(!c.getRabbitIndexes().empty() && it->second.isHungry()) {
            if(RandomGenerator::dice2() < 0.5) {
                it->second.eat();
                rabbits.erase(c.getFirstRabbitIndex());
                c.removeFirstRabbitIndex();
                creaturesCounter--;
                eatenRabbits++;
            }
        }
        if(c.getWolfIndexes().size() > 1) {
            it->second.makePregnant(); 
        }
        if(it->second.timeToGiveBirth()) {
            neww.insert(it->first);
        }
        it->second.step();
    }        
    Indexes itdr;
    Indexes newr;
    for(auto it = rabbits.begin(); it != rabbits.end(); ++it) {
        if(!(it->second.isAlive())) {
            itdr.insert(it->first);
            continue;
        }
        Cell &c = getCell(it->second.getCoords());
        if(c.isThereGrass()) {
            it->second.eat();
            c.eatGrass();
        }
        if(c.getRabbitIndexes().size() > 1) {
            it->second.makePregnant();
        }
        if(it->second.timeToGiveBirth()) {
            newr.insert(it->first);
        }
        it->second.step();
    }  
    bornNew(neww, newr);
    cleanDead(itdw, itdr);
    stepCounter++;
    rabbitNumbers.push_back(rabbits.size());
    wolfsNumbers.push_back(wolfs.size()); 
}

void Field::check() {
    if(rabbits.empty()) {
        for (int i = 0; i < viCount; ++i) {
            Rabbit r;
            int x = rand() % FIELD_WIDTH;
            int y = rand() % FIELD_HEIGHT;
            r.setField(this);
            r.setCoords(Coords(std::make_pair(x,y)));
            rabbits[r.getId()] = r;
            cells[y * FIELD_WIDTH + x].addVictim(r.getId());
            creaturesCounter++;
            allCreatureCounter++;            
        }
    }
    if(wolfs.empty()) {
        for (int i = 0; i < prCount; ++i) {
            Wolf w;
            int x = rand() % FIELD_WIDTH;
            int y = rand() % FIELD_HEIGHT;
            w.setField(this);
            w.setCoords(Coords(std::make_pair(x,y)));
            wolfs[w.getId()] = w;
            cells[y * FIELD_WIDTH + x].addPredator(w.getId());
            creaturesCounter++;
            allCreatureCounter++;
        }
    }
}

void Field::write() {
    std::ofstream out("WR" + std::to_string(rand()) + ".dat");
    for(auto it = rabbitNumbers.begin(), it1 = wolfsNumbers.begin(); it != rabbitNumbers.end(); ++it, ++it1) {
        out << (*it) << " " << (*it1) << std::endl;
    }
    rabbitNumbers.clear();
    wolfsNumbers.clear();
}

bool Field::wasWolfHere(Coords p, int index) {
    return getCell(p).getWolfWasHere(index);
}

bool Field::wasRabbitHere(Coords p, int index) {
    return getCell(p).getRabbitWasHere(index);
}

void Field::wolfWasHere(Coords p, int index) {
    getCell(p).setRabbitWasHere(false, index);
    getCell(p).setWolfWasHere(true, index);
}

void Field::rabbitWasHere(Coords p, int index) {
    getCell(p).setWolfWasHere(false, index);
    getCell(p).setRabbitWasHere(true, index);
}

Cell &Field::getCreatureCell(Coords coords) {
    return cells[coords.y() * FIELD_WIDTH + coords.x()];
}

void Field::run() {
    while(running.load(std::memory_order_relaxed)) {
        step();
        print();
        emit nextStep();
        if(isEmpty()) {
            std::cerr << "All dead!\n";            
            write();
            generatePopulations();
        }else {
            if(noWolfs()) {
                std::cerr << "Wolfs dead!\n";
                write();
                populateWolfs();
            }
            if(noRabbits()) {
                std::cerr << "Rabbits dead!\n";
                write();
                populateRabbits();
            }
        }
        if(creaturesCounter < 10000) {
            QThread::currentThread()->msleep(10);
        }
    }
    stopped.store(true, std::memory_order_relaxed);
}
