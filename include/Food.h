#ifndef FOOD
#define FOOD
 
#include "Renderable.hpp"
#include "RandomEngine.h"
 
class Food : public Renderable
{ 
public:
    Food(int anIdx);
    ~Food();

    bool isEaten() {return mIsEaten; }
    void setEaten(bool aFlag) {mIsEaten = aFlag; }

private:

    bool mIsEaten; 
    RandomEngine mRandom; 

   
};
#endif //FOOD