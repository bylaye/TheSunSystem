#include <iostream>
#include <Objects.hpp>
#include <Naturals.hpp>
#include <Artificials.hpp>
#include <unistd.h>
#include <vector>

//#include <SFML/Graphics.hpp>

int main ()
{
    Objects o("planet", sf::Vector2f(12, 13), 1000e10, sf::Color::Black, new sf::CircleShape(30),{10,10} );
    std::cout << o.getName() << "\n" << static_cast<int>(o.getColor().r)<< "\n";

    Naturals sun("sun", sf::Vector2f(0, 1), 10e30, sf::Color::Yellow, 70, {200, 300});
    Naturals mercury("Mercury", {0, 1}, 10e23, sf::Color(50,40,20), 30, {400, 300});
    Naturals venus("Venus", {0, 1}, 10e24, sf::Color(120,40,150, 50), 40, {500, 300});
    Naturals earth("Earth", {0, 1}, 10e25, sf::Color::Blue, 45, {600, 300});
    
    
    //const std::vector<Naturals>& objects {sun, mercury, venus, earth};
    /*
    objects.push_back(std::make_unique<Naturals>(sun));
    objects.push_back(std::make_unique<Naturals>(mercury));
    objects.push_back(std::make_unique<Naturals>(venus));
    objects.push_back(std::make_unique<Naturals>(earth));
    //objects.push_back(earth);
    */
    
    Artificials sat("sun", sf::Vector2f(0, 1), 10e23, sf::Color::Blue, sf::Vector2f(60, 50), {300, 500});

    std::cout << sun.getName() << " " << sun.getMass()<< "\n";
    std::cout << "Hello Solar System \n";

    sf::RenderWindow app(sf::VideoMode(1200, 800), "SFML window");

    /*
    sf::Texture texture;
    if (!texture.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);
    */

    while (app.isOpen())
    {
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();
        }
        usleep(5000);
        app.clear(sf::Color(10,40,40, 100));
        sun.draw(app);
        mercury.draw(app);
        venus.draw(app);
        earth.draw(app);
        sat.draw(app);
        o.draw(app);
        app.display();
    }

    for(const auto& p : {sun,earth})
    {
        std::cout << p.getName() << "\n";
    }

    return EXIT_SUCCESS;

}
