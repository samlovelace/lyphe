#ifndef RENDERABLE_H
#define RENDERABLE_H

#include "SFML/Graphics.hpp"

/** 
 * @brief Renderable - base class for all entities being rendered 
 */
class Renderable
{

public:
    Renderable(int width, int height) : mDrawable(sf::RectangleShape(sf::Vector2f(width, height))) {}
    Renderable() {}; 
    virtual ~Renderable() {}

    void init(float width, float height, std::array<float, 3> rgb) 
    {
        mDrawable = sf::RectangleShape(sf::Vector2f(width, height));
        
        sf::Uint8 r = static_cast<sf::Uint8>(rgb[0] * 255);
        sf::Uint8 g = static_cast<sf::Uint8>(rgb[1] * 255);
        sf::Uint8 b = static_cast<sf::Uint8>(rgb[2] * 255);

        sf::Color color(r, g, b);
        mDrawable.setFillColor(color);
    }
 
    void setPosition(int x, int y) {mDrawable.setPosition(x,y); }
    void setPosition(float x, float y) {mDrawable.setPosition(x*100, y*100);}
    void setColor(sf::Color aColor) {mDrawable.setFillColor(aColor); }
    int height() {return mDrawable.getSize().y; }
    int width() {return mDrawable.getSize().x; }
    float x() {return mDrawable.getPosition().x; }
    float y() {return mDrawable.getPosition().y; }
    sf::RectangleShape getDrawable() {return mDrawable;}
    //Entity Renderable() {return static_cast<Entity>(*this);}

private:
    sf::RectangleShape mDrawable; 
};

#endif //RENDERABLE_H