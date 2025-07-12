#ifndef FOODHANDLER_H
#define FOODHANDLER_H
 
#include <vector> 
#include <memory>
#include "Food.h"
 
class FoodHandler 
{ 
public:
    FoodHandler(int anAmountOfFood);
    ~FoodHandler();

    void spawnFood(int anAmountOfFood); 
    std::vector<std::shared_ptr<Food>> getFood() {return mFood; }

private:
   
    std::vector<std::shared_ptr<Food>> mFood; 

};
#endif //FOODHANDLER_H