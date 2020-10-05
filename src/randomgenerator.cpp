#include <random>
#include "randomgenerator.hpp"

std::function<int()> RandomGenerator::dice;
std::function<double()> RandomGenerator::dice2;

void RandomGenerator::init() {
    std::default_random_engine engine(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, std::numeric_limits<int>::max());
    dice = std::bind(distribution, engine);
    std::uniform_real_distribution<double> distribution2(0, 1);
    dice2 = std::bind(distribution2, engine);
}

double RandomGenerator::bell(double x, double m, double s) {
    return 1.0/(s*sqrt(2 * M_PI)) * exp(-0.5 * ((x-m)/s) * ((x-m)/s));
}

RandomGenerator::RandomGenerator() {
}
