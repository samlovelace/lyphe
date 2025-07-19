
#include "OrganismHandler.h"
#include <iostream>

OrganismHandler::OrganismHandler(const YAML::Node& aPopulationConfig) : mRate(RateController(10))
{
    mInitialPopulationSize = aPopulationConfig["initial"].as<int>(); 
    mGenerationTime = aPopulationConfig["generation_time"].as<int>(); 
    mNumberGenerations = aPopulationConfig["num_generations"].as<int>(); 

    for(int i = 0; i < mInitialPopulationSize; i++)
    {
        // construct organism and push back into population

        // construct traits map 
        std::vector<std::string> traits; 
        if(aPopulationConfig["Organism"]["DNA"]["traits"])
        {
            for(const auto& trait : aPopulationConfig["Organism"]["DNA"]["traits"])
            {
                traits.push_back(trait.as<std::string>());
            }
        }

        auto organsim = std::make_shared<Organism>(traits, i); 
        mPopulation.push_back(organsim); 
    }

    mNumInitialFood = aPopulationConfig["num_food"].as<int>(); 
    mFoodHandler = std::make_shared<FoodHandler>(mNumInitialFood); 

}

OrganismHandler::~OrganismHandler()
{

}

void OrganismHandler::run()
{
    std::cout << "Constructed population of size: " << mInitialPopulationSize << std::endl; 
    std::cout << "Population: " << std::endl; 
    
    for(const auto& org : mPopulation)
    {
        std::cout << org->toString() << std::endl;  
    }
    
    std::cout << "Simulating " << mNumberGenerations << " Generation(s)" << " with " << mGenerationTime << " steps per generation" << std::endl; 
    std::cout << "#########################################################" << std::endl;
    std::cout << "################### Simulation Begin ####################" << std::endl; 

    for(int j = 0; j <= mNumberGenerations; j++)
    {
        std::cout << "************* GENERATION " << j << " ****************" << std::endl; 
        std::cout << "Population Size: " << mPopulation.size() << std::endl; 
        // other stats here 
        
        mFoodHandler->spawnFood(mNumInitialFood); 

        for(int i = 0; i < mGenerationTime; i++)
        {      
            mRate.start(); 

            for(auto& organism : mPopulation)
            {
                organism->move(); 
            }

            checkInteractions(); 

            mRate.block(); 
        }     

        generateNewPopulation(); 
    }

    std::cout << "################### Simulation End ######################" << std::endl;
    std::cout << "#########################################################" << std::endl;
}

void OrganismHandler::checkInteractions()
{
    for(auto& organism : mPopulation)
    {
        for(auto& food : mFoodHandler->getFood())
        {
            if(food->isEaten())
                continue; 

            auto organismShape = organism->getDrawable().getGlobalBounds(); 
            auto foodShape = food->getDrawable().getGlobalBounds(); 

            if(organismShape.intersects(foodShape))
            {
                food->setEaten(true); 
                organism->updateFoodCount(); 
            }
        }
    }
}

void OrganismHandler::generateNewPopulation()
{
    computePopulationFitness(); 

    // TODO: make percentage of survivors configurable/smarter 
    int survivors = static_cast<int>(mPopulation.size() * 0.5f);
    survivors = std::max(survivors, 2); // ensure at least 2

    std::vector<std::shared_ptr<Organism>> newPopulation; 

    for (int i = 0; i < survivors; ++i)
    {
        // Pick two parents randomly
        int p1 = rand() % survivors;
        int p2 = rand() % survivors;

        auto child = mPopulation[p1]->breed(mPopulation[p2]); 

        newPopulation.push_back(child); 
    }

    // TODO: make percentage of survivors configurable/smarter 
    int elites = static_cast<int>(mPopulation.size() * 0.8f);
    elites = std::max(survivors, 2); // ensure at least 2
    
    // allow elites to breed again 
    for(int i = 0; i < elites; i++)
    {
        int p1 = rand() % elites; 
        int p2 = rand() % elites; 

        auto child = mPopulation[p1]->breed(mPopulation[p2]); 
        newPopulation.push_back(child); 
    }

    // reset the population for the next generation 
    mPopulation = newPopulation; 
}

void OrganismHandler::computePopulationFitness()
{
    for(const auto& organism : mPopulation)
    {
        // for now, set mFitness = mFoodCount 
        organism->setFitness(organism->getFoodCount());
    }

    std::sort(mPopulation.begin(), mPopulation.end(),
          [](std::shared_ptr<Organism> a, std::shared_ptr<Organism> b) {
              return a->getFitness() > b->getFitness();
          });

}


