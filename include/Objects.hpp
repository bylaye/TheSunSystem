
#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>

// Gravitational Constant
const double G = 6.674e-11;

class Objects
{
    protected:
        std::string name;
        double mass;
        sf::Vector2f position;
        double velocity;
        double acceleration;
        sf::Color color;
        bool isNatural = false;

        std::unique_ptr<sf::Shape> shape;

    public:
        Objects(std::string name, sf::Vector2f pos, double m, sf::Color c, std::unique_ptr<sf::Shape> s, sf::Vector2f shapePos)
        : name(name), position(pos), mass(m), color(c), shape(std::move(s)), acceleration(10), velocity(0)
        {
            shape->setPosition(shapePos);
            shape->setFillColor(color);
        };
        
        // getteur
        std::string  getName()          const { return name; };
        sf::Vector2f getPosition()      const { return position; };
        sf::Color    getColor()         const { return color; };
        double       getMass()          const { return mass; };
        double       getVelocity()      const { return velocity; };
        double       getAcceleration()  const { return acceleration; };
        bool         getIsNatural()     const { return isNatural; };

        void setName(std::string n)      { name=n; };
        void setPosition(sf::Vector2f p) { position = p; };
        void setColor(sf::Color c)       { color = c; };
        void setMass(double m)           { mass = m; };
        void setVelocity(double v)       { velocity = v; };
        void setAcceleration(double a)   { acceleration = a; };
        void setIsNatural(bool b)        { isNatural = b; };

        //virtual ~Objects() = default;

        virtual void  draw(sf::RenderWindow& window) const {
            if (shape)
            {
                window.draw(*shape);
            }
        };

        virtual sf::Vector2f getShapePosition() const
        {
            if (shape){
                return shape->getPosition(); 
            }
            else{ 
                return sf::Vector2f(0.0f, 0.0f); 
            }
        };

        virtual sf::Vector2f getShapeDimension() const {
            return sf::Vector2f(0.0f, 0.0f);
        };

        
        void updateAcceleration(const std::vector<std::unique_ptr<Objects>>& objects)
        {
            double ax = 0;
            double ay = 0;
            for (const auto& obj : objects)
            {
                if(obj.get() != this)
                {
                    double dx = this->position.x - obj->getPosition().x;
                    double dy = this->position.y - obj->getPosition().y;
                    double distance = std::sqrt(dx*dx + dy*dy);
                    double  force = G * obj->getMass() / (distance * distance);

                    ax += force * (dx/distance);
                    ay += force * (dy/distance);
                }
            }
            this->acceleration = std::sqrt(ax*ax + ay*ay);
        };
        
		void updateVelocity(float timestamp)
		{
			// TODO: Calculer la vitesse par rapport a acceleration 
		}
};

#endif // OBJECT_HPP_INCLUDED
