
#include "Organism.h"
#include <cmath>
#include <cstdlib>  // rand, RAND_MAX

Organism::Organism()
{

}

Organism::Organism(const YAML::Node& anOrgConfig, int anId)
{
    mId = anId; 
    mSpottedFood = false; 
    mPrevHeading = 0; 
    mPosition = vec3<float>(0, 0, 0); 
    mDNA = std::make_unique<DNA>(anOrgConfig["DNA"], mId); 

    float size = mDNA->getTrait("size"); 
    initRenderable(50*size/2, 50*size/2, uniqueColor());
}

Organism::~Organism()
{

}

void Organism::initRenderable(float height, float width, std::array<float, 3> rgb)
{
    init(width, height, rgb); 
}

void Organism::move()
{
    vec3<float> dPos{0, 0, 0};
    double heading = 0;
    bool turnAround = false;

    int mEnvironmentWidth = 5;
    int mEnvironmentHeight = 5;

    if (mSpottedFood)
    {
        // compute heading to food and only move that way
        // heading = atan2(foodLoc.y - mPosition.y, foodLoc.x - mPosition.x);
    }
    else
    {
        heading = random_heading_change(mDNA->getTrait("curiosity"), mPrevHeading);
        float speed = mDNA->getTrait("speed");

        float dx = speed * cos(heading);
        float dy = speed * sin(heading);

        float newX = mPosition.x + dx;
        float newY = mPosition.y + dy;

        // Check boundaries
        if (newX < 0 || newX > mEnvironmentWidth
         || newY < 0 || newY > mEnvironmentHeight)
        {
            // Reverse heading
            heading += M_PI;
            dx = speed * cos(heading);
            dy = speed * sin(heading);
            turnAround = true;
        }

        dPos.x = dx;
        dPos.y = dy;
    }

    mPosition += dPos;
    mPrevHeading = turnAround ? heading : heading;

    // update renderable state 
    setPosition(mPosition.x, mPosition.y); 
}

double Organism::random_heading_change(double curiosity, double current_heading)
{
    constexpr double MAX_ANGLE = M_PI; // radians (180 deg)
    double max_change = curiosity * MAX_ANGLE;

    // Random number in [-max_change, +max_change]
    double rand01 = (double)rand() / RAND_MAX;
    double delta = (rand01 * 2.0 - 1.0) * max_change;

    double new_heading = current_heading + delta;

    // Wrap angle to [0, 2pi)
    if (new_heading < 0)
        new_heading += 2 * M_PI;
    if (new_heading >= 2 * M_PI)
        new_heading -= 2 * M_PI;

    return new_heading;
}

std::array<float, 3> Organism::uniqueColor()
{
    // find top 3 trait values
    float aggression = mDNA->getTrait("aggression");
    float curiosity = mDNA->getTrait("curiosity");
    float speed = mDNA->getTrait("speed");

    std::array<float, 3> rgb = {aggression, curiosity, speed}; 
    return rgb; 
}

std::shared_ptr<Organism> Organism::breed(std::shared_ptr<Organism> anOrganism)
{
    auto child = std::make_shared<Organism>();  
    auto childDNA = mDNA->crossover(anOrganism->getDNA());
    childDNA->mutate(0.1f); 

    child->setDNA(std::move(childDNA)); 
    return child; 
}


std::string Organism::toString()
{
    std::stringstream ss; 
    
    // stuff specific to the organism here 
    ss << "Organism " << mId << ": " << std::endl; 
    ss << "x,y,z: " << mPosition.x << ", " << mPosition.y << ", " << mPosition.z << " "; 
    ss << "Food Consumed: " << mFoodCount << " "; 

    // DNA stuff 
    ss << mDNA->toString(); 

    return ss.str(); 
}

