#ifndef NATURALS_HPP
#define NATURALS_HPP

#include <Objects.hpp>

class Naturals : public Objects
{
    private:
        float radius;

    public:
        Naturals(std::string name, double mass, double x, double y, float radius, sf::Color color)
        : Objects(name, mass, x, y, color, std::make_unique<sf::CircleShape>(radius) ), radius(radius)
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
