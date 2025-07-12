
#include "ConfigManager.hpp"
#include "OrganismHandler.h"
#include <thread> 
#include "RenderEngine.h"

int main()
{
    ConfigManager::get().load("../config.yaml"); 

    YAML::Node populationConfig; 
    if(!ConfigManager::get().getConfig<YAML::Node>("Population", populationConfig))
    {
        std::cout << "Failed to get population config" << std::endl; 
        return 0; 
    } 

    auto oh = std::make_shared<OrganismHandler>(populationConfig); 
    std::thread(&OrganismHandler::run, oh.get()).detach(); 

    RenderEngine render(oh);  
    render.run(); 
}
