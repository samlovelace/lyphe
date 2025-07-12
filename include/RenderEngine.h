#ifndef RENDERENGINE_H
#define RENDERENGINE_H
 
#include "OrganismHandler.h"
#include <memory>

#include <SFML/Graphics.hpp>

 
class RenderEngine 
{ 
public:
    RenderEngine(std::shared_ptr<OrganismHandler> oh);
    ~RenderEngine();

    void run(); 

private:

    sf::RenderWindow mWindow; 

    std::shared_ptr<OrganismHandler> mOrganismHandler; 
   
};
#endif //RENDERENGINE_H