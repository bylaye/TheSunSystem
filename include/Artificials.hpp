#ifndef ARTIFICIALS_HPP
#define ARTIFICIALS_HPP

#include <Objects.hpp>

class Artificials : public Objects
{
    private:
        sf::Vector2f dimension;

    public:
        Artificials(std::string name, sf::Vector2f position, double mass, sf::Color color, sf::Vector2f d, sf::Vector2f shapePos)
        : Objects(name, position, mass, color, new sf::RectangleShape(d), shapePos ), dimension(d)
        {
            shape->setFillColor(color);
            shape->setOrigin(d.x/2, d.y/2);
            //shape->setPosition(400, 200);
        };

    sf::Vector2f getDimension() const { return dimension; };
    
    //void draw(sf::RenderWindow& window) const {
    //    window.draw(shape);
    //}
};


#endif
