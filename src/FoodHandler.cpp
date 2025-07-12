
#include "FoodHandler.h"

FoodHandler::FoodHandler(int anAmountOfFood)
{
    spawnFood(anAmountOfFood); 
}

FoodHandler::~FoodHandler()
{

}

void FoodHandler::spawnFood(int anAmountOfFood)
{
    if(!mFood.empty())
        mFood.clear(); 
    
    for(int i = 0; i < anAmountOfFood; i++)
    {
        auto food = std::make_shared<Food>(i* time(0)); 
        mFood.push_back(food); 
    }
}