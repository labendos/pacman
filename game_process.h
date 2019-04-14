//
//  game_process.h
//  Ermitage
//
//  Created by Mikhail Labendik on 13/04/2019.
//  Copyright © 2019 Mikhail Labendik. All rights reserved.
//

#ifndef game_process_h
#define game_process_h
#include "ResourcePath.hpp" // Решить проблему с отображением текста
template < typename T, typename U >
void parity(T & e, U & e1) // держит enemy и enemy1 в одом месте
{
    e.x = e1.x;
    e.y = e1.y;
    e.xi = e1.xi;
    e.yi = e1.yi;
}

class Game
{
protected:
    sf::Clock clock;
    sf::Clock clock_special; //часы черно-белого режима
    double time = 0;
    double time_special = 0; //время для черно-белого режима
    Map1 map1;
    Map map;
    int level = 0;
    Dots dots;
    Strawberry strawberry;
    Pacman packman;
    Enemy enemy[5];
    Enemy1 enemy1[5];
    
    int move = 0; // 1 - left, 2 - down, 3 - right, 4 - up
    
    int t50;
    int t100;
    int t150;
    
    
public:
    int k = 2;
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    std::stringstream ss;
    
    Game(Pacman _packman);
    void play();
    void play1();
    void newlevel();
    
    
};
void Game::newlevel()
{
    int t50 = 0;
    int t100 = 0;
    int t150 = 0;
    
    packman.init(&dots, &strawberry);
    window.create(sf::VideoMode(X*N, X*N + 100), "Packman");
    
    enemy[0].init(1, 1);
    enemy[1].init(17, 17);
    
    enemy1[0].init(1, 1);
    enemy1[1].init(17, 17);
    
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "arial.ttf"))
    {
        return EXIT_FAILURE;
    }
    
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(X*N/2 - 100, X*N + 10);
}

Game::Game(Pacman _packman): packman(_packman)
{
    int t50 = 0;
    int t100 = 0;
    int t150 = 0;
    
    packman.init(&dots, &strawberry);
    window.create(sf::VideoMode(X*N, X*N + 100), "Packman");
    
    enemy[0].init(1, 1);
    enemy[1].init(17, 17);
    
    enemy1[0].init(1, 1);
    enemy1[1].init(17, 17);

    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "arial.ttf"))
    {
        return EXIT_FAILURE;
    }
    
    text.setFont(font);
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(X*N/2 - 100, X*N + 10);
}

void Game::play()
{
    int old_score;
    while (window.isOpen())
    {
        old_score = score; //для проверки, насколько увеличился счет
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
        if ((score > 20) && (level == 0))
        {
            level = 1;
            dots.restart();
            strawberry.restart();
            //map1.restart();
            //map.restart();
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
        if ((fail == 0) && (score <= 20))
        {
            dots.draw(&window);
            
            map.draw(&window);
            packman.draw(&window);
            strawberry.draw(&window);
            for(int i = 0; i < k; i++)
            {
                enemy[i].draw(&window);
            }
            //window.draw(text);
        }
        
        if ((fail == 0) && (score > 20))
        {
            dots.draw(&window);
            map1.draw(&window);
            packman.draw(&window);
            strawberry.draw(&window);
            for(int i = 0; i < k; i++)
            {
                enemy[i].draw(&window);
            }
            //window.draw(text);
        }
        
        else if (fail == 1)
        {
            ss.str("");
            ss << "FAIL";
            text.setString(ss.str());
            //window.draw(text);
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
            ss << "VICTORY";
            text.setString(ss.str());
            //window.draw(text);
            window.display();
            
            clock.restart();
            while(time < 3.0)
            {
                time = clock.getElapsedTime().asSeconds();
            }
            
            window.close();
        }
        if (score - old_score > 1)
        {
            break;
        }
        
        window.display();
    }
    for (int i = 0; i < 5; ++i)
        parity(enemy1[i], enemy[i]);
    window.display();
    return EXIT_SUCCESS;
}

void Game::play1()
{
    clock_special.restart();
    time_special = clock_special.getElapsedTime().asSeconds();
    while ((window.isOpen()) && (time_special < 5.0))
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
        if ((score > 20) && (level == 0))
        {
            level = 1;
            dots.restart();
            strawberry.restart();
            //map1.restart();
            //map.restart();
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
            enemy1[2].init((N - 1)/2, (N - 1)/2);
            ++k;
        }
        else if(score >= 100 && t100 == 0)
        {
            t100 = 1;
            enemy1[3].init((N - 1)/2, (N - 1)/2);
            ++k;
        }
        else if(score >= 150 && t150 == 0)
        {
            t150 = 1;
            enemy1[4].init((N - 1)/2, (N - 1)/2);
            ++k;
        }
        
        for(int i = 0; i < k; i++)
        {
            enemy1[i].move(packman.get_xi(), packman.get_yi());
            enemy1[i].check_fail(packman.get_x(), packman.get_y());
        }
        
        
        ss.str("");
        ss << "Score - " << score;
        text.setString(ss.str());
        
        window.clear();
        if((fail == 0) && (level == 0))
        {
            dots.draw(&window);
            
            map.draw(&window);
            packman.draw(&window);
            strawberry.draw(&window);
            for(int i = 0; i < k; i++)
            {
                enemy1[i].draw(&window);
            }
            //window.draw(text);
        }
        
        if((fail == 0) && (level == 1))
        {
            dots.draw(&window);
            
            map1.draw(&window);
            packman.draw(&window);
            strawberry.draw(&window);
            for(int i = 0; i < k; i++)
            {
                enemy1[i].draw(&window);
            }
            //window.draw(text);
        }
        
        /*if ((fail == 0) && (score > 30))
        {
            break;
        }*/
        
        else if(fail == 1)
        {
            ss.str("");
            ss << "FAIL";
            text.setString(ss.str());
            //window.draw(text);
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
            ss << "VICTORY";
            text.setString(ss.str());
            //window.draw(text);
            window.display();
            
            clock.restart();
            while(time < 3.0)
            {
                time = clock.getElapsedTime().asSeconds();
            }
            window.close();
        }
        for (int i = 0; i < 5; ++i)
            parity(enemy[i], enemy1[i]);
        window.display();
        time_special = clock_special.getElapsedTime().asSeconds();
    }
}



#endif /* game_process_h */
