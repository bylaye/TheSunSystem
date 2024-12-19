#include <iostream>
#include <Objects.hpp>
#include <Naturals.hpp>
#include <Artificials.hpp>
#include <memory>
#include <unistd.h>
#include <vector>

//#include <SFML/Graphics.hpp>

int main ()
{
   
    float centerX = 200; 
    float centerY = 300; 

    std::vector<std::unique_ptr<Objects>> objects;
    objects.push_back(std::make_unique<Naturals> ("sun", sf::Vector2f(0, 1), 10e30, sf::Color::Yellow, 70, sf::Vector2f(centerX, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Mercury", sf::Vector2f(0, 1), 10e30, sf::Color(169,169,169), 30, sf::Vector2f(centerX+200, centerY)));
    objects.push_back(std::make_unique<Naturals> ("Venus", sf::Vector2f(0, 1), 10e30, sf::Color(100,100,100), 40, sf::Vector2f(centerX+300, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Earth", sf::Vector2f(0, 1), 10e30, sf::Color(10,10,200), 50, sf::Vector2f(centerX+400, centerY)) );
    objects.push_back(std::make_unique<Naturals> ("Mars", sf::Vector2f(0, 1), 10e30, sf::Color(200,10,0), 35, sf::Vector2f(centerX+500, centerY)) );
    objects.push_back(std::make_unique<Artificials> ("Sat 1", sf::Vector2f(0, 1), 10e10, sf::Color(200,20,200), sf::Vector2f(30,20), sf::Vector2f(centerX+400, centerY+100)) );
    objects.push_back(std::make_unique<Artificials> ("Sat 2", sf::Vector2f(0, 1), 10e10, sf::Color(20,20,200), sf::Vector2f(50,70), sf::Vector2f(centerX+400, centerY+400)) );

    sf::RenderWindow app(sf::VideoMode(1200, 800), "SFML window");

    sf::Event event;
    std::unique_ptr<Objects> selectedObject = nullptr;
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
                                       
                    for (auto& obj : objects) {
                        sf::Vector2f objPos = obj->getShapePosition();
                        if (obj->getIsNatural())
                        {
                            float radius = obj->getShapeDimension().x;
                            float dx = mousePos.x - objPos.x;
                            float dy = mousePos.y - objPos.y;
                            float distance = std::sqrt(dx * dx + dy * dy);

                            if (distance <= radius) {
                                // TODO: Pouvoir copier l'ojbet selectionner dans selectedObject
                                // selectedObject = obj;
                                std::cout << "Object selected : " << obj->getName() << "\n";
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
                                    // TODO: Pouvoir copier l'ojbet selectionner dans selectedObject
                                    std::cout << "selected " << obj->getName() << "\n";
                                    break; 
                                }
                            } 
                        }
                    }                    

                }
            }
            
        }

        usleep(5000);
        app.clear(sf::Color(10,40,40, 100));

        for(const auto& p : objects) { 
            p->draw(app); 
        }

        app.display();
    }
    
    return EXIT_SUCCESS;
}
