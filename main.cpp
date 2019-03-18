#include <iostream>
#include <cmath>
#include <sstream>

#include <SFML/Graphics.hpp>

#define N 19 //numbers os quads
#define X 40 //lenght of side

int score = 0;
int fail = 0;

#include "Character.h"
#include "Map.h"
#include "Dots.h"
#include "Pacman.h"
#include "Enemy.h"

int main()
{
    sf::Clock clock;
    double time = 0;

    Map map;

    Dots dots;

    Pacman packman(&dots);
    int move = 0; // 1 - left, 2 - down, 3 - right, 4 - up

    int t50 = 0;
    int t100 = 0;
    int t150 = 0;

    int k = 2;
    Enemy enemy[5];
    enemy[0].init(1, 1);
    enemy[1].init(17, 17);

    sf::RenderWindow window(sf::VideoMode(X*N, X*N + 100), "Packman");

    sf::Font font;
    if (!font.loadFromFile("res/arial.ttf"))
    {
        return 1;
    }
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(X*N/2 - 100, X*N + 10);
    std::stringstream ss;

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                default:
                    break;
            }
        }

        if(move == 0)
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                move = 2;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                move = 1;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                move = 4;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                move = 3;
            }
        }
        packman.move(&move);

        if(score >= 50 && t50 == 0)
        {
            t50 = 1;
            enemy[2].init((N - 1)/2, (N - 1)/2);
            ++k;
        }
        else if(score >= 100 && t100 == 0)
        {
            t100 = 1;
            enemy[3].init((N - 1)/2, (N - 1)/2);
            ++k;
        }
        else if(score >= 150 && t150 == 0)
        {
            t150 = 1;
            enemy[4].init((N - 1)/2, (N - 1)/2);
            ++k;
        }

        for(int i = 0; i < k; i++)
        {
            enemy[i].move(packman.get_xi(), packman.get_yi());
            enemy[i].check_fail(packman.get_x(), packman.get_y());
        }

        ss.str("");
        ss << "Score - " << score;
        text.setString(ss.str());

        window.clear();
        if(fail == 0)
        {
            dots.draw(&window);
            map.draw(&window);
            packman.draw(&window);
            for(int i = 0; i < k; i++)
            {
                enemy[i].draw(&window);
            }
            window.draw(text);
        }
        else if(fail == 1)
        {
            ss.str("");
            ss << "FAIL";
            text.setString(ss.str());
            window.draw(text);
            window.display();

            clock.restart();
            while(time < 1.0)
            {
                time = clock.getElapsedTime().asSeconds();
            }
            window.close();

        }
        else if(fail == -1)
        {
            ss.str("");
            ss << "WICTORY";
            text.setString(ss.str());
            window.draw(text);
            window.display();

            clock.restart();
            while(time < 3.0)
            {
                time = clock.getElapsedTime().asSeconds();
            }
            window.close();
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
