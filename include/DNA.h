#ifndef DNA_H
#define DNA_H
 
#include <vector> 
#include <unordered_map>
#include <yaml-cpp/yaml.h>
#include "RandomEngine.h"

class DNA 
{ 
public:
    DNA();
    DNA(const YAML::Node& aDnaConfig, int anOrgsId);
    ~DNA();

    std::unique_ptr<DNA> crossover(std::unique_ptr<DNA> aDNA); 
    void mutate(float mutationRate);

    float getTrait(const std::string& aTraitName); 
    std::unordered_map<std::string, float> getAllTraits() {return mTraitsMap;}
    void setTraitsMap(std::unordered_map<std::string, float> aTraitsMap) {mTraitsMap = aTraitsMap; }
    std::string toString(); 

private:

    std::vector<std::string> mTraits; 
    std::unordered_map<std::string, float> mTraitsMap; 

    RandomEngine* mRandom; 

   
};
#endif //DNA_H

// 🧠 Cognitive / Behavioral Traits
// These influence decision-making, interaction, or risk behavior:
//     Boldness: how often an agent initiates contact or enters danger zones
//     Curiosity: likelihood of exploring new areas
//     Avoidance: tendency to flee from crowds or threats
//     Cooperation: preference for staying near others
//     MemorySpan: ability to remember zones or past interactions

// 🔧 Physical / Genetic Traits
// These drive form, performance, and survivability:
//     Endurance: movement over time without losing energy
//     SensoryRange: how far the agent “sees” or detects stimuli
//     ColorHue / PatternCode: for camouflage, signaling, or mate selection
//     MutationResistance: how stable their genome stays across generations
//     EnergyEfficiency: cost per unit of movement

// 🧬 Reproductive Traits
// For when evolution starts to get juicy:
//     FertilityRate: number of offspring generated
//     MatePreference: trait biases in partner selection
//     GestationTime: delay between selection and spawning
//     DominanceLevel: ability to override local genotypes

// 🌎 Environmental Traits
// These are defined by interaction with surroundings:
//     ThermalTolerance: survive hot or cold zones
//     GravityAdaptation: how movement changes in dense regions
//     NutrientSensitivity: ability to detect and absorb resources
//     TerritoryBias: preference for certain map zones