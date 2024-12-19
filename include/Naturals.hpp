#ifndef NATURALS_HPP
#define NATURALS_HPP

#include <Objects.hpp>

class Naturals : public Objects
{
    private:
        float radius;
//        sf::CircleShape shape;

    public:
        Naturals(std::string name, sf::Vector2f position, double mass, sf::Color color, float radius, sf::Vector2f shapePos)
        : Objects(name, position, mass, color, new sf::CircleShape(radius), shapePos ), radius(radius) 
        {
            //shape.setRadius(radius);
            //shape->setFillColor(color);
            shape->setOrigin(radius, radius);
            //shape->setPosition(200, 100);
        };

    float getRadius() const { return radius; };
    
    //void draw(sf::RenderWindow& window) const {
    //    window.draw(shape);
    //}
};


#endif
