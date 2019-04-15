#include <iostream>
#include <cmath>
#include <sstream>
#include <tuple>
#include <functional>

#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include "SFML/Audio.hpp"
#define N 19 //numbers os quads
#define X 40 //lenght of side*/

int score = 0;
int fail = 0;
int enemy_regime = 0;
#include "Character.h"
#include "Maps.h"
#include "Map.h"
#include "Map1.h"
#include <set>
#include "Dots.h"
#include "Pacman.h"
#include "Enemy.h"
#include "Strawberry.h"
#include "Enemy1.h" 
#include "game_process.h"
#include "menu.h"


int main()
{
    generate_map();
    Pacman _packman;
    menu();
    Game game(_packman);
    
    while(game.window.isOpen())
    {
        game.play();
        game.play1(); // в течение 5 секунд enemy замедляются в случае поедания клубники
    }
}
