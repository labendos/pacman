//
//  menu.h
//  Ermitage
//
//  Created by Mikhail Labendik on 15/04/2019.
//  Copyright © 2019 Mikhail Labendik. All rights reserved.
//

#ifndef menu_h
#define menu_h
#include <SFML/Audio.hpp> // добвлена музыка, но не играет

void menu()
{
    // Create the main window
    sf::Clock clock;
    double time = 0;
    sf::RenderWindow window(sf::VideoMode(645, 849), "Pacman");
    sf::Texture newgameTexture, menuBackground;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    buffer.loadFromFile(resourcePath() + "click.wav");
    sound.setBuffer(buffer);
    newgameTexture.loadFromFile(resourcePath()+"play.png");
    menuBackground.loadFromFile(resourcePath()+"menu.png");
    sf::Sprite newgame(newgameTexture), menuBg(menuBackground);
    bool isMenu = 1;
    int menuNum = 0;
    newgame.setPosition(340, 100);
    menuBg.setPosition(0, 0);
    sf::Music music;
    music.openFromFile(resourcePath()+"opening.wav");
    music.play();
    
    while (window.isOpen())
    {
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
        }
        newgame.setColor(sf::Color::White);
        menuNum = 0;
        window.clear(sf::Color(129, 181, 221));
        
        if (sf::IntRect(340, 100, 200, 200).contains(sf::Mouse::getPosition(window))) {newgame.setColor(sf::Color::Green); menuNum = 1;}
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (menuNum == 1)
            {
                clock.restart();
                time = clock.getElapsedTime().asSeconds();
                sound.play();
                while(time < 0.1)
                {
                    time = clock.getElapsedTime().asSeconds();
                }

                window.close();
                break;
            }//если нажали первую кнопку, то выходим из меню и идем в игру
        }
       // window.clear();
        
        window.draw(menuBg);
        window.draw(newgame);
        window.display();
    }
}

#endif /* menu_h */
