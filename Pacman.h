#ifndef Pacman_h
#define Pacman_h
#include "Strawberry.h"
class Pacman : public Character
{
    Dots* dots;
    Strawberry* strawberry;
    sf::Texture texture[2];
public:
    Pacman();
    Pacman(Dots* _dots, Strawberry* _strawberry);
    //init(Dots* _dots, Strawberry* _strawberry);
    int get_xi();
    int get_yi();
    int get_x();
    int get_y();
    void init(Dots* _dots, Strawberry* _strawberry);
    void draw(sf::RenderWindow* window);
    void move_left(int* move);
    void move_down(int* move);
    void move_right(int* move);
    void move_up(int* move);
    void move(int* move);
};
Pacman::Pacman() {}

Pacman::Pacman(Dots* _dots, Strawberry* _strawberry): dots(_dots), strawberry(_strawberry)
{
    x = N*X/2;
    xi = (N - 1)/2;
    y = N*X/2;
    yi = (N - 1)/2;
    r = X/2;
    count = 100;
    texture[0].loadFromFile(resourcePath()+"pacman.jpg", sf::IntRect(0, 0, 225, 225));
    texture[1].loadFromFile(resourcePath()+"pacman.jpg", sf::IntRect(260, 0, 225, 225));
    mov = 0;
    vel = 0.4;
}

void Pacman::init(Dots* _dots, Strawberry* _strawberry)
{
    dots = _dots;
    strawberry = _strawberry;
    x = N*X/2;
    xi = (N - 1)/2;
    y = N*X/2;
    yi = (N - 1)/2;
    r = X/2;
    count = 100;
    texture[0].loadFromFile(resourcePath()+"pacman.jpg", sf::IntRect(0, 0, 225, 225));
    texture[1].loadFromFile(resourcePath()+"pacman.jpg", sf::IntRect(260, 0, 225, 225));
    mov = 0;
    vel = 0.4;
}
int Pacman::get_xi()
{
    return xi;
}
int Pacman::get_yi()
{
    return yi;
}
int Pacman::get_x()
{
    return x;
}
int Pacman::get_y()
{
    return y;
}
void Pacman::draw(sf::RenderWindow* window)
{
    sf::CircleShape shape;
    shape.setRadius(r);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
    shape.setOrigin(r, r);
    shape.setTexture(&texture[(count/40)%2]);
    shape.rotate(90*mov);
    window -> draw(shape);
}
void Pacman::move_left(int* move)
{
    if(count > 0)
    {
        x -= vel;
        --count;
    }
    else
    {
        --xi;
        count = 100;
        dots -> check(xi, yi);
        strawberry -> check(xi, yi);
        *move = 0;
    }
    
}
void Pacman::move_down(int* move)
{
    if(count > 0)
    {
        y += vel;
        --count;
    }
    else
    {
        ++yi;
        count = 100;
        dots -> check(xi, yi);
        strawberry -> check(xi, yi);
        *move = 0;
    }
    
}
void Pacman::move_right(int* move)
{
    if(count > 0)
    {
        x += vel;
        --count;
    }
    else
    {
        ++xi;
        count = 100;
        dots -> check(xi, yi);
        strawberry -> check(xi, yi);
        *move = 0;
    }
    
}
void Pacman::move_up(int* move)
{
    if(count > 0)
    {
        y -= vel;
        --count;
    }
    else
    {
        --yi;
        count = 100;
        dots -> check(xi, yi);
        strawberry -> check(xi, yi);
        *move = 0;
    }
    
}
void Pacman::move(int* move)
{
    mov = *move;
    switch (*move) {
        case 2:
            if(MAP[xi - 1][yi] != 1)
            {
                move_left(move);
            }
            else
            {
                *move = 0;
            }
            break;
        case 1:
            if(MAP[xi][yi + 1] != 1)
            {
                move_down(move);
            }
            else
            {
                *move = 0;
            }
            break;
        case 4:
            if(MAP[xi + 1][yi] != 1)
            {
                move_right(move);
            }
            else
            {
                *move = 0;
            }
            break;
        case 3:
            if(MAP[xi][yi - 1] != 1)
            {
                move_up(move);
            }
            else
            {
                *move = 0;
            }
            break;
            
        default:
            break;
    }
}

#endif /* Pacman_h */
