#ifndef ORGANISMHANDLER_H
#define ORGANISMHANDLER_H
 
#include "Organism.h" 
#include "RateController.hpp"
#include "FoodHandler.h"

class OrganismHandler 
{ 
public:
    OrganismHandler(const YAML::Node& aPopulationConfig);
    ~OrganismHandler();

    void run(); 

    std::vector<std::shared_ptr<Organism>> getPopulation() {return mPopulation; }
    std::vector<std::shared_ptr<Food>> getFood() {return mFoodHandler->getFood(); }

private:

    int mInitialPopulationSize; 
    int mGenerationTime;
    int mNumberGenerations;
    int mNumInitialFood;

    RateController mRate; 
    std::shared_ptr<FoodHandler> mFoodHandler; 
    std::vector<std::shared_ptr<Organism>> mPopulation; 

    void checkInteractions();
    void generateNewPopulation();
    void computePopulationFitness(); 
   
};
#endif //ORGANISMHANDLER_H