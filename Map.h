#ifndef Map_h
#define Map_h
#include "Map_Generating.h"
#include "Maps.h"

class Map: public Maps
{
    //int map[N][N];
public:
    Map();
    void draw(sf::RenderWindow* window);
};

Map::Map()
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            map[i][j] = MAP[i][j];
        }
    }
    
}

void Map::draw(sf::RenderWindow* window)
{
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if(map[i][j] == 1)
            {
                sf::RectangleShape shape;
                shape.setSize(sf::Vector2f(X - 1, X - 1));
                shape.setFillColor(sf::Color::Blue);
                shape.setPosition(X*i, X*j);
                window -> draw(shape);
            }
        }
    }
}

#endif /* Map_h */
