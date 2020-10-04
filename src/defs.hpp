#ifndef DEFS_HPP
#define DEFS_HPP
#include <cassert>
#include <vector>
#include "randomgenerator.hpp"

constexpr int FIELD_SIZE = 60;
constexpr int FIELD_WIDTH = 240*2;
constexpr int FIELD_HEIGHT = 45*2;
constexpr int WOLF_MAX_AGE = 21840;
constexpr int RABBIT_MAX_AGE = 8736;
constexpr int WOLF_START_HUNGRY = 224;
constexpr int RABBIT_START_HUNGRY = 112;
constexpr int WOLF_PREGNANCY_TIME = 252;
constexpr int RABBIT_PREGNANCY_TIME = 168;
constexpr int WOLF_CHILDREN_NUM = 5;
constexpr int RABBIT_CHILDREN_NUM = 4;
constexpr int WOLF_NUMBER = 40;
constexpr int RABBIT_NUMBER = 500;
constexpr int WOLF_SMELL_TIME = 10;
constexpr int RABBIT_SMELL_TIME = 20;
constexpr int GRASS_PER_CELL = 150;
constexpr int GRASS_PER_RABBIT = 12;
#endif // DEFS_HPP
