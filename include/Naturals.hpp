#ifndef NATURALS_HPP
#define NATURALS_HPP

#include <Objects.hpp>

class Naturals : public Objects
{
    private:
        float radius;

    public:
        Naturals(std::string name, sf::Vector2f position, double mass, sf::Color color, float radius, sf::Vector2f shapePos)
        : Objects(name, position, mass, color, std::make_unique<sf::CircleShape>(radius), shapePos ), radius(radius) 
        {
            shape->setOrigin(radius, radius);
            setIsNatural(true);
        };

    float getRadius() const { return radius; };   
    virtual sf::Vector2f getShapeDimension() const {
            return sf::Vector2f(radius, radius);
    };
    //sf::Vector2f getShapePosition() const { return shape->getPosition();};

};


#endif
