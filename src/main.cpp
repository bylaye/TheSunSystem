#include <iostream>
#include <Objects.hpp>
#include <Naturals.hpp>
//#include <Artificials.hpp>
#include <memory>
#include <unistd.h>
#include <vector>
#include <sstream>

//#include <SFML/Graphics.hpp>

struct TrailedObject {
    std::unique_ptr<Objects> object;
    std::vector<sf::Vertex> trail; // Trajectoire
};

int main ()
{
   	float mapWidth = 1200;
   	float mapHeight = 800;

    float centerX = 200; 
    float centerY = mapHeight/2; 

	float timestep = 3600;

    std::vector<std::unique_ptr<Objects>> objects;
/*
    objects.push_back(std::make_unique<Naturals> ("sun", sf::Vector2f(0, 0), 1.989e30, sf::Color::Yellow, 70, sf::Vector2f(centerX, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Mercury", sf::Vector2f(5.791e10, 1), 3.3011e23, sf::Color(169,169,169), 30, sf::Vector2f(centerX+200, centerY)));
    objects.push_back(std::make_unique<Naturals> ("Venus", sf::Vector2f(1.082e11, 0), 4.8675e24, sf::Color(100,100,100), 40, sf::Vector2f(centerX+300, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Earth", sf::Vector2f(1.496e11, 0), 5.9724e24, sf::Color(10,10,200), 50, sf::Vector2f(centerX+400, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Mars", sf::Vector2f(2.279e11, 0), 6.4171e23, sf::Color(200,10,0), 35, sf::Vector2f(centerX+500, centerY)) );
    objects.push_back(std::make_unique<Artificials> ("Sat 1", sf::Vector2f(0, 1), 10e10, sf::Color(200,20,200), sf::Vector2f(30,20), sf::Vector2f(centerX+400, centerY+100)) );
    objects.push_back(std::make_unique<Artificials> ("Sat 2", sf::Vector2f(0, 1), 10e10, sf::Color(20,20,200), sf::Vector2f(50,70), sf::Vector2f(centerX+400, centerY+200)) );
*/
	objects.push_back(std::make_unique<Naturals>("Sun", 1.989e30, 0.0, 300.0, 20.0f, 0, sf::Color::Yellow));
    objects.push_back(std::make_unique<Naturals>("Mercury", 3.3011e23, 5.791e10, 300.0, 8, 1e-9,  sf::Color::Green));
    objects.push_back(std::make_unique<Naturals>("Venus", 4.8675e24, 1.082e11, 300.0, 10, 1e-9,  sf::Color::Red));
    objects.push_back(std::make_unique<Naturals>("Earth", 5.972e24, 1.496e11, 300.0, 12, 1.e-9,  sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("Mars", 6.4171e23, 2.279e11, 300.0, 9, 1.e-9,  sf::Color(200,100,50)));
    objects.push_back(std::make_unique<Naturals>("Moon", 7.348e22, 1.496e11 + 3.844e8, 300.0, 5, 1.3e-9, sf::Color::White));


	for(const auto& p : objects) { 
		p->initialiseVelocity(objects);
	}

	for(const auto& p : objects) { 
		std::cout << p->getName() << " vy: " << p-> getVy() << "\n";
	}
	/*
    objects.push_back(std::make_unique<Naturals>("Jupyter", 5.972e24, 400.0 + 1.496e11, 300.0, 29.78e3, 2, 6.4e-9,  sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("Saturn", 5.972e24, 400.0 + 1.496e11, 300.0, 29.78e3, 2, 6.4e-9,  sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("uranus", 5.972e24, 400.0 + 1.496e11, 300.0, 29.78e3, 2, 6.4e-9,  sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("Neptune", 5.972e24, 400.0 + 1.496e11, 300.0, 29.78e3, 2, 6.4e-9,  sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("Moon", 7.348e22, 400.0 + 1.496e11 + 3.844e8, 300.0, 29.78e3 + 1.022e3, 1, 6.4e-9, sf::Color::White));
	*/

	sf::Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        return -1;
    }

    sf::Text infoText;
    infoText.setFont(font);
    infoText.setCharacterSize(16);
    infoText.setFillColor(sf::Color::Blue);
    infoText.setPosition(mapWidth * 0.7f + 10, 10);
	
	sf::RenderWindow app(sf::VideoMode(mapWidth, mapHeight), "SFML window");

    sf::Event event;
    Objects* selectedObject = nullptr;
    while (app.isOpen())
    {
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

			if (event.type == sf::Event::KeyPressed) {
		        if (event.key.code == sf::Keyboard::Up) {
		            timestep = std::min(timestep + 3600.0f, 3600.0f * 24 * 365);
		        } else if (event.key.code == sf::Keyboard::Down) {
		            timestep = std::max(3600.0f, timestep - 3600);
		        }
		    }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left){
                    sf::Vector2i mousePos = sf::Mouse::getPosition(app);
                    std::cout << "Mouse Left pressed x= " << mousePos.x << "\n";
                    selectedObject = nullptr;
                          
                    for (auto& obj : objects) {
                        sf::Vector2f objPos = obj->getShapePosition();
                        if (obj->getIsNatural())
                        {
                            float radius = obj->getShapeDimension().x;
                            float dx = mousePos.x - objPos.x;
                            float dy = mousePos.y - objPos.y;
                            float distance = std::sqrt(dx * dx + dy * dy);

                            if (distance <= radius) {
                                selectedObject = obj.get();
                                std::cout << "Planet selected : " << obj->getName() << "acc: " << obj->getAx() <<"\n";
                                break;
                            }
                        }
                        else
                        {
                            float w = obj->getShapeDimension().x;
                            float h = obj->getShapeDimension().y;
                            if ( (mousePos.x >= (objPos.x - w/2)) && mousePos.x <=(objPos.x + w/2) )
                            {
                                if ( (mousePos.y >= (objPos.y - h/2)) && mousePos.y <=(objPos.y + h/2) )
                                {
                                    selectedObject = obj.get();
                                    std::cout << "Artificial selected " << obj->getName() << "\n";
                                    break; 
                                }
                            } 
                        }
                    }                    

                }
            }
            // Delete selected object with Delete button pressed
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Delete && selectedObject) {
			
					for (auto it = objects.begin(); it != objects.end(); ++it) {
						if (it->get() == selectedObject) {
							objects.erase(it);
                    		std::cout << "Deleting object: " << selectedObject->getName() << "\n";
							break;
						}
					}
                    selectedObject = nullptr;
                }
            }
            
        }

        usleep(5000);
		std::ostringstream output;
		
		output << "Time Step: " << timestep << "\n";

        app.clear(sf::Color(10,40,40, 100));
		
        for(const auto& p : objects) { 
        	p->updateAcceleration(objects);
        }

        for(const auto& p : objects) { 
        	p->update(timestep);
        }

        for(const auto& p : objects) {
			if (!selectedObject){
				output << p->getName() << " : vx = " << p->getVx() << " vy= "<< p->getVy()  <<"\n";
			}
            p->draw(app); 
        }

		// print object selected description
		if (selectedObject)
		{
			output << selectedObject->getName() << "\n";
			output << "Mass : " << selectedObject->getMass() << "\n";
			output << "Real Pos x: "<< selectedObject->getPosX();
			output << " y: "<< selectedObject->getPosY() << "\n";
		}
		
		infoText.setString(output.str());
		app.draw(infoText);
		
        app.display();
    }
    
    return EXIT_SUCCESS;
}
