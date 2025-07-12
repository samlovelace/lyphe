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
    std::string toString(); 

private:

    int mId; 
    bool mSpottedFood; 
    float mPrevHeading; 
    std::unique_ptr<DNA> mDNA; 
    vec3<float> mPosition; 

    void initRenderable(float height, float width, std::array<float, 3> rgb); 
    std::array<float, 3> uniqueColor();
    double random_heading_change(double curiosity, double current_heading);

};
#endif //ORGANISM_H