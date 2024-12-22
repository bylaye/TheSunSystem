
#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include <string>
#include <vector>
#include <memory>
#include <cmath>
#include <SFML/Graphics.hpp>

// Gravitational Constant
const double G = 6.674e-11;
const double scale2 = 1e-9;
class Objects
{
	protected:
		std::string name;
		double mass;
		double posX, posY;
		double ax, ay;
		double vx, vy;
		sf::Color color;
		bool isNatural = false;
		double scale;

		std::unique_ptr<sf::Shape> shape;

	public:
		Objects(std::string name, double m, double x, double y, double scale, sf::Color c, std::unique_ptr<sf::Shape> s): 
			name(name), mass(m), posX(x), posY(y), 
			vx(0),  vy(0), scale(scale),  
			color(c), shape(std::move(s)), ax(0), ay(0)
		{
			shape->setPosition(static_cast<float>(x), static_cast<float>(y));
			shape->setFillColor(color);
		};
		
		// getteur
		std::string getName()			const { return name; };
		double		getMass()			const { return mass; };
		double		getPosX()			const { return posX; };
		double		getPosY()			const { return posY; };
		double		getAx()				const { return ax; };
		double		getAy()				const { return ay; };
		double		getVx()				const { return vx; };
		double		getVy()				const { return vy; };
		sf::Color	getColor()			const { return color; };
		bool		getIsNatural()		const { return isNatural; };

		void setName(std::string n)		 { name=n; };
		void setColor(sf::Color c)		 { color = c; };
		void setMass(double m)			 { mass = m; };
		void setIsNatural(bool b)		 { isNatural = b; };

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


		void initialiseVelocity(const std::vector<std::unique_ptr<Objects>>& objects)
		{
			for (auto& obj : objects)
			{
				if (obj.get() != this)
				{
					double dx = obj->getPosX() - posX;
					double dy = obj->getPosY() - posY;
					double distance = std::sqrt(dx * dx + dy * dy);
					vy += std::sqrt(G * obj->getMass() / distance);
				}
			}
		}
		

		void updateAcceleration(const std::vector<std::unique_ptr<Objects>>& objects)
		{
			ax = 0;
			ay = 0;
			for (const auto& obj : objects)
			{
				if(obj.get() != this)
				{
					double dx = obj->getPosX() - posX;
					double dy = obj->getPosY() - posY;
					double distance = std::sqrt(dx * dx + dy * dy);

					if (distance < 1e3) continue;

					double force = G * obj->getMass() / (distance * distance);

					ax += force * (dx/distance);
					ay += force * (dy/distance);
				}
			}
		};
		

		void update(double timestep) {
			vx += ax * timestep;
			vy += ay * timestep;

			posX += vx * timestep;
			posY += vy * timestep;

			shape->setPosition(static_cast<float>(posX * scale + 400), static_cast<float>(posY * scale +400));
		}
};

#endif // OBJECT_HPP_INCLUDED
