#ifndef ORGANISMHANDLER_H
#define ORGANISMHANDLER_H
 
#include "Organism.h" 
#include "RateController.hpp"

class OrganismHandler 
{ 
public:
    OrganismHandler(const YAML::Node& aPopulationConfig);
    ~OrganismHandler();

    void run(); 

    std::vector<std::shared_ptr<Organism>> getPopulation() {return mPopulation; }

private:

    int mInitialPopulationSize; 
    int mGenerationTime;
    int mNumberGenerations;
    RateController mRate; 
    std::vector<std::shared_ptr<Organism>> mPopulation; 
   
};
#endif //ORGANISMHANDLER_H