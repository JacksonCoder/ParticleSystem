
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resource, use the helper
// method resourcePath() from ResourcePath.hpp
//

#include <Particle.hpp>
// Here is a small helper for you ! Have a look.
#include "ResourcePath.hpp"
#include <iostream>

void modifier(Particle& modp){

    modp.getVelocity() = sf::Vector2f(((rand()%10)-5)/1,((rand()%10)-5)/1);
}
void modifier2(Particle& modp){
    modp.getLocation() = sf::Vector2f(100,100);
}
int main(int, char const**)
{
    
    srand(time(NULL));
    srand(time(NULL)*rand());
    srand(time(NULL)*rand());
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(2400, 1800), "JLib Particle Test");

    // Set the Icon
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text text("Particle Test using JSFML", font, 50);
    text.setColor(sf::Color::Black);
    sf::Texture particleTexture;
    if(!particleTexture.loadFromFile(resourcePath() + "starparticle.svg.thumb.png")){
        return EXIT_FAILURE;
    }
    ParticleController pc;
    pc.setParticleTexture(particleTexture);
    pc.setParticleConstraints(sf::Vector2f(100,100));
    pc.intmods.push_back(modifier);
    //jpc.intmods.push_back(modifier2);
    pc.spawnParticles(1, sf::Vector2i(100,100));
    pc.spawnParticles(1, sf::Vector2i(4,100));
    pc.spawnParticles(1, sf::Vector2i(130,200));
    pc.spawnParticles(1, sf::Vector2i(300,0));
    sf::View view(sf::FloatRect(0, 0, 2400, 1800));
    window.setView(view);
    view.zoom(-100);
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            else if(event.type == event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
                //std::cout<<"c"<<std::endl;
                pc.spawnParticles(8, sf::Mouse::getPosition());
            }
        }

        // Clear screen
        window.clear(sf::Color::Black);

        // Draw the string
        window.draw(text);
        //jpc.spawnParticles(2, sf::Vector2i(1200,900));
        pc.frameRun(window);
        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
