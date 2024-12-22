#include <iostream>
#include <Objects.hpp>
#include <Naturals.hpp>
//#include <Artificials.hpp>
#include <memory>
#include <unistd.h>
#include <vector>

//#include <SFML/Graphics.hpp>

int main ()
{
   	float mapWidth = 1200;
   	float mapHeight = 800;

    float centerX = 200; 
    float centerY = mapHeight/2; 

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
	objects.push_back(std::make_unique<Naturals>("Sun", 1.989e30, 400.0, 300.0, 20.0f, sf::Color::Yellow));
    objects.push_back(std::make_unique<Naturals>("Earth", 5.972e24, 400.0 + 1.496e11, 300.0, 10.0f, sf::Color::Blue));
    objects.push_back(std::make_unique<Naturals>("Moon", 7.348e22, 400.0 + 1.496e11 + 3.844e8, 300.0, 5.0f, sf::Color::White));

    sf::RenderWindow app(sf::VideoMode(mapWidth, mapHeight), "SFML window");

    sf::Event event;
    Objects* selectedObject = nullptr;
    while (app.isOpen())
    {
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

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
                    std::cout << "Deleting object: " << selectedObject->getName() << "\n";
					
					for (auto it = objects.begin(); it != objects.end(); ++it) {
						if (it->get() == selectedObject) {
							objects.erase(it);
							break;
						}
					}
                    selectedObject = nullptr;
                }
            }
            
        }

        usleep(5000);
        app.clear(sf::Color(10,40,40, 100));

        for(const auto& p : objects) { 
        	p->updateAcceleration(objects);
			//p->draw(app); 
        }

        for(const auto& p : objects) { 
        	p->updatePosition(3600/2);
        }

        for(const auto& p : objects) { 
            p->draw(app); 
        }
        app.display();
    }
    
    return EXIT_SUCCESS;
}
