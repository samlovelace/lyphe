
#include "OrganismHandler.h"
#include <iostream>

OrganismHandler::OrganismHandler(const YAML::Node& aPopulationConfig) : mRate(RateController(5))
{
    mInitialPopulationSize = aPopulationConfig["initial"].as<int>(); 
    mGenerationTime = aPopulationConfig["generation_time"].as<int>(); 
    mNumberGenerations = aPopulationConfig["num_generations"].as<int>(); 

    for(int i = 0; i < mInitialPopulationSize; i++)
    {
        // construct organism and push back into population
        auto organsim = std::make_shared<Organism>(aPopulationConfig["Organism"], i); 
        mPopulation.push_back(organsim); 
    }

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
    
    std::cout << "Simulatiing " << mNumberGenerations << " Generation(s)" << " for " << mGenerationTime << " steps per generation" << std::endl; 
    std::cout << "#########################################################" << std::endl;
    std::cout << "################### Simulation Begin ####################" << std::endl; 

    for(int j = 0; j <= mNumberGenerations; j++)
    {
        for(int i = 0; i < mGenerationTime; i++)
        {            
            mRate.start(); 

            for(auto& organism : mPopulation)
            {
                organism->move(); 
            }

            std::cout << mPopulation[0]->toString() << std::endl;  

            //checkInteractions();


            mRate.block(); 
        }     
    }

    std::cout << "################### Simulation End ######################" << std::endl;
    std::cout << "#########################################################" << std::endl;
}

