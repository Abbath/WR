#ifndef RANDOMGENERATOR_HPP
#define RANDOMGENERATOR_HPP

#include <functional>
#include <chrono>

class RandomGenerator
{
public:
    static void init();
    static std::function<int()> dice;
    static std::function<double()> dice2;
    static double bell(double x, double m, double s);
    RandomGenerator();
};

#endif // RANDOMGENERATOR_HPP
