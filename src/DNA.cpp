
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