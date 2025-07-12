
#include "Food.h"

Food::Food(int anIdx) : mRandom(anIdx), mIsEaten(false)
{
    int x = mRandom.getInt(0, 500);
    int y = mRandom.getInt(0, 500); 
    
    // always green 
    std::array<float, 3> rgb = {1, 1, 1}; 

    init(10, 10, rgb); 
    setPosition(x,y); 
}

Food::~Food()
{

}
