#ifndef FIELD_HPP
#define FIELD_HPP

#include "wolf.hpp"
#include "rabbit.hpp"
#include "cell.hpp"
#include <functional>
#include <iostream>
#include <deque>
#include <unordered_map>
#include <list>
#include <fstream>
#include <string>
#include <atomic>
#include <QRunnable>
#include <QObject>

using Cells = std::vector<Cell>;

class Field : public QObject, public QRunnable{
    CS_OBJECT(Field)
    Cells cells;
    std::unordered_map<int, Wolf> wolfs;
    std::unordered_map<int, Rabbit> rabbits;
    std::list<int> wolfsNumbers;
    std::list<int> rabbitNumbers;
    int creaturesCounter; 
    int allCreatureCounter = 0;
    int deadRabbits = 0;
    int deadWolfs = 0;
    int eatenRabbits = 0;
    int stepCounter;
    std::atomic_bool running;
    static constexpr int prCount = WOLF_NUMBER;
    static constexpr int viCount = RABBIT_NUMBER;
    bool noWolfs();
    bool noRabbits();
public:
    void populateWolfs();
    void populateRabbits();
    void stop();
    explicit Field(QObject* parent);
    Cell& getCell(Coords c);
    Cells &getCells();
    bool isEmpty(); 
    void generatePopulations();
    void print();
    void fixCoords();
    void cleanDead(Indexes itdw, Indexes itdr);
    void bornNew(const Indexes& neww, const Indexes& newr);
    void step();
    void check();
    void write();
    bool wasWolfHere(Coords p, int index = -1);
    bool wasRabbitHere(Coords p, int index = -1);
    void wolfWasHere(Coords p, int index);
    void rabbitWasHere(Coords p, int index);
    Cell& getCreatureCell(Coords coords);
    void run();
public:
    CS_SIGNAL_1(Public, void nextStep())
    CS_SIGNAL_2(nextStep) 
};
#endif // FIELD_HPP
