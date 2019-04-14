//
//  Maps.h
//  Ermitage
//
//  Created by Mikhail Labendik on 09/04/2019.
//  Copyright © 2019 Mikhail Labendik. All rights reserved.
//

#ifndef Maps_h
#define Maps_h
#include "Map_Generating.h"
class Maps
{
protected:
    int map[N][N];
public:
    void draw(sf::RenderWindow* window);
    void restart()
    {
        for(int i = 0; i < N; i++)
        {
            for(int j = 0; j < N; j++)
            {
                map[i][j] = MAP[i][j];
            }
        }
    }
    Maps& operator= (const Maps &maps)
    {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                map[i][j] = maps.map[i][j];
        return *this;
    }
};

#endif /* Maps_h */
