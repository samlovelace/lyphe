
#include "RandomEngine.h"

RandomEngine::RandomEngine(unsigned int seed) : mGen(seed) 
{

}

RandomEngine::~RandomEngine()
{

}

int RandomEngine::getInt(int min, int max) 
{
    std::uniform_int_distribution<> dist(min, max);
    return dist(mGen);
}

double RandomEngine::getFloat(double min, double max) 
{
    std::uniform_real_distribution<> dist(min, max);
    return dist(mGen);
}

bool RandomEngine::chance(double probability) 
{
    return getFloat(0.0, 1.0) < probability;
}