#ifndef RANDOMENGINE_H
#define RANDOMENGINE_H
 
#include <random>
 
class RandomEngine 
{ 
public:
    RandomEngine(unsigned int seed);
    ~RandomEngine();

    int getInt(int min, int max); 
    double getFloat(double min, double max); 
    bool chance(double probability); 

private:
    std::mt19937 mGen;
   
};
#endif //RANDOMENGINE_H
