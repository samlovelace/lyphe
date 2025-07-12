
#include "RenderEngine.h"

RenderEngine::RenderEngine(std::shared_ptr<OrganismHandler> oh) : mOrganismHandler(oh)
{
    mWindow.create(sf::VideoMode(500, 500), "Lyphe");
}

RenderEngine::~RenderEngine()
{

}

void RenderEngine::run()
{
    while(mWindow.isOpen())
    {
        sf::Event e; 
        while(mWindow.pollEvent(e))
        {
            if(sf::Event::Closed == e.type)
            {
                mWindow.close(); 
            }
        }

        mWindow.clear(sf::Color::Black);
        
        for(const auto& organism : mOrganismHandler->getPopulation())
        {
            mWindow.draw(organism->getDrawable());
        }

        for(const auto& food : mOrganismHandler->getFood())
        {
            if(food->isEaten())
                continue;
            
            mWindow.draw(food->getDrawable()); 
        }

        mWindow.display(); 
    }

}