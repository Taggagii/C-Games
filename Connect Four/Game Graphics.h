#ifndef GAME_GRAPHICS
#define GAME_GRAPHICS

#include "Game Values.h"


void Create_Circle(SDL_Renderer *renderer, int originX, int originY)
{
    for (int i = 0; i < CircleRadius * 8; i++)
        SDL_RenderDrawPoint(renderer, originX + baseCircleValues[i][0], originY + baseCircleValues[i][1]);
}

void Fill_Circle(SDL_Renderer *renderer, int originX, int originY)
{
    for (int i = 0; i < CircleRadius * 8; i += 2)
        SDL_RenderDrawLine(renderer,  originX + baseCircleValues[i][0], originY + baseCircleValues[i][1],  originX + baseCircleValues[i + 1][0], originY + baseCircleValues[i+1][1]);
}



void Create_Grid(SDL_Renderer * renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int x = 0; x < ScreenWidth; x += TileWidth)
        SDL_RenderDrawLine(renderer, x, 0, x, ScreenHeight);    
    SDL_RenderDrawLine(renderer, ScreenWidth - 1, 0, ScreenWidth - 1, ScreenHeight);  
    for (int y = 0; y < ScreenHeight; y += TileHeight)
        SDL_RenderDrawLine(renderer, 0, y, ScreenWidth, y);    
    SDL_RenderDrawLine(renderer, 0, ScreenHeight - 1, ScreenWidth, ScreenHeight - 1); 

    for (int x = CircleRadius; x < ScreenWidth; x += TileWidth)
        for (int y = CircleRadius; y < ScreenHeight; y += TileHeight)
            Create_Circle(renderer, x, y);
}

void Update_Tiles(SDL_Renderer * renderer)
{
    for (int x = 0; x < TilesInX; x++)
        for (int y = 0; y < TilesInY; y++)
        {
            int value;
            if ((value = TileMatrix[x][y]))
            {
                if (value == 1)
                    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
                else if (value == 2)
                    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
                int valuex = x * TileWidth + TileBaseValueX, valuey = y * TileHeight + TileBaseValueY;
                Fill_Circle(renderer, valuex, valuey);
                SDL_SetRenderDrawColor(renderer, 0, 255, 255, 255);
                Create_Circle(renderer, valuex, valuey);
            }
        }
}

#endif