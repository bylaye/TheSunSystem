#ifndef ARTIFICIALS_HPP
#define ARTIFICIALS_HPP

#include <Objects.hpp>

class Artificials : public Objects
{
    private:
        sf::Vector2f dimension;

    public:
        Artificials(std::string name, sf::Vector2f position, double mass, sf::Color color, sf::Vector2f d, sf::Vector2f shapePos)
        : Objects(name, position, mass, color, std::make_unique<sf::RectangleShape>(d), shapePos ), dimension(d)
        {
            shape->setOrigin(d.x/2, d.y/2);
        };

    sf::Vector2f getDimension() const { return dimension; };
    virtual sf::Vector2f getShapeDimension() const {
            return dimension;
    };
};

#endif
