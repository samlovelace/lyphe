#ifndef ORGANISM_H
#define ORGANISM_H

#include "DNA.h"
#include <memory>
#include <Vec3.hpp>
#include "Renderable.hpp"
 
class Organism : public Renderable
{ 
public:
    Organism();
    Organism(const YAML::Node& anOrgConfig, int anId); 
    ~Organism();

    void move(); 
    void updateFoodCount() {mFoodCount++;} 
    std::string toString(); 

    std::shared_ptr<Organism> breed(std::shared_ptr<Organism> anOrganism); 

    int getFoodCount() {return mFoodCount; }

    void setFitness(float aFitness) { mFitness = aFitness; }
    float getFitness() {return mFitness; }
    std::unique_ptr<DNA> getDNA() {return std::move(mDNA);}
    void setDNA(std::unique_ptr<DNA> aDNA) {mDNA = std::move(aDNA);}


private:

    int mId; 
    bool mSpottedFood; 
    float mPrevHeading; 
    std::unique_ptr<DNA> mDNA; 
    vec3<float> mPosition; 

    int mFoodCount; 

    float mFitness; 

    void initRenderable(float height, float width, std::array<float, 3> rgb); 
    std::array<float, 3> uniqueColor();
    double random_heading_change(double curiosity, double current_heading);

};
#endif //ORGANISM_H