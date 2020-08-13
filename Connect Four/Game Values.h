#include "Game Graphics.h"
#include "Game Logic.h"

#ifndef _GAME_VALUES_
#define _GAME_VALUES_

#include <stdio.h>
#include <math.h> //sqrt
#include <unistd.h> //for the sleep function
#include <string.h> //death message
#include <stdlib.h> //for rand
#include <time.h> //for rand
#include <SDL2/SDL.h>



const int ScreenWidth = 700;
const int ScreenHeight = 600;
const int TilesInY = 6;
const int TilesInX = 7;
const int TileHeight = ScreenHeight / TilesInY;
const int TileWidth = ScreenWidth / TilesInX;
const int TileBaseValueX = TileWidth / 2;
const int TileBaseValueY = TileHeight / 2;
const int CircleRadius = TileBaseValueX;


//GAMEOVER VALUES//
int GameOverX, GameOverY, GameOverX2, GameOverY2;
int GameOverBoxX, GameOverBoxY, GameOverBoxX2, GameOverBoxY2;

//TILES//
int currentTileColor = 0;

int TileMatrix[TilesInX][TilesInY];
void INIT_TILE_MATRIX()
{
    for (int x = 0; x < TilesInX; x++)
        for (int y = 0; y < TilesInY; y++)
            TileMatrix[x][y] = 0;
}

int baseCircleValues[CircleRadius * 8][2];
void INIT_BASECIRCLEVALUES()
{
    int index = 0;
    for (int x = 0; x < CircleRadius; x++)
    {
        int y = (int)(sqrt(CircleRadius * CircleRadius -  x * x));
        baseCircleValues[index][0] = x, baseCircleValues[index][1] = y;
        index++;
        baseCircleValues[index][0] = -x, baseCircleValues[index][1] = y;
        index++;

        baseCircleValues[index][0] = y, baseCircleValues[index][1] = x;
        index++;
        baseCircleValues[index][0] = -y, baseCircleValues[index][1] = x;
        index++;
        
        baseCircleValues[index][0] = x, baseCircleValues[index][1] = -y;
        index++;
        baseCircleValues[index][0] = -x, baseCircleValues[index][1] = -y;
        index++;

        baseCircleValues[index][0] = y, baseCircleValues[index][1] = -x;
        index++;
        baseCircleValues[index][0] = -y, baseCircleValues[index][1] = -x;
        index++;
        
    }
}
//FUNCTIONS//
int snap_to_grid(int input, int multiple, int base)
{
    float value = ((float)(input - base) / multiple);
    int index = (int)value;
    value -= index;
    if (value > 0.5) return (index + 1) * multiple + base;
    return index * multiple + base;
}

#endif