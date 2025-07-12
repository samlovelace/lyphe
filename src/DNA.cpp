
#include "DNA.h"
#include <ctime> 

DNA::DNA()
{

}

DNA::DNA(const YAML::Node& aDnaConfig, int anOrgsId)
{ 
    unsigned int seed = static_cast<unsigned int>(std::time(nullptr)) + anOrgsId; 
    mRandom = new RandomEngine(seed); 

    if(aDnaConfig["traits"])
    {
        for(const auto& trait : aDnaConfig["traits"])
        {
            // do i need a separate traits vector? 
            mTraits.push_back(trait.as<std::string>());
            
            mTraitsMap.insert({trait.as<std::string>(), mRandom->getFloat(0, 1)}); 
            
        }
    }

}

DNA::~DNA()
{

}

std::unique_ptr<DNA> DNA::crossover(std::unique_ptr<DNA> aDNA)
{
    std::unique_ptr<DNA> child = std::make_unique<DNA>(); 

    auto childTraitsMap = std::unordered_map<std::string, float>(); 

    auto otherTraitsMap = aDNA->getAllTraits(); 

    for(const auto& [trait, value] : mTraitsMap)
    {
        float inheritedValue = (value + otherTraitsMap.at(trait)) / 2.0;
        childTraitsMap.insert({trait, inheritedValue});  
    }

    child->setTraitsMap(childTraitsMap);
    return std::move(child); 
}

void DNA::mutate(float mutationRate)
{
    for (auto& [trait, value] : mTraitsMap)
    {
        float mutation = mRandom->getFloat(-mutationRate, mutationRate);
        value = std::clamp(value + mutation, 0.f, 1.f);
    }
}


float DNA::getTrait(const std::string& aTraitName)
{
    if(mTraitsMap.find(aTraitName) == mTraitsMap.end())
    {
        return -1; 
    }

    return mTraitsMap.at(aTraitName); 
}

std::string DNA::toString()
{
    std::stringstream ss; 

    for(const auto& [trait, value] : mTraitsMap)
    {
        ss << trait << ": " << value << "\n"; 
    }

    return ss.str(); 
}