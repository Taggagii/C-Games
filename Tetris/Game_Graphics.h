

#ifndef GRAPHICS_H_
#define GRAPHICS_H_
#include "Game_Values.h"

void Draw_NextBlock(SDL_Renderer *renderer2, Block *block)
{
    
    SDL_Rect rect = {.x = 0, .y = 0, .w = BlockWidth, .h = BlockHeight};
    for (int box = 0; box < 4; box++)
    {
        rect.x = (OtherWindowWidth / 3) + Block_Data[block->nextblock][box][0] * BlockWidth;
        rect.y = (OtherWindowHeight / 2.5) +  -Block_Data[block->nextblock][box][1] * BlockHeight;
        SetColor(renderer2, block->nextblock);
        SDL_RenderFillRect(renderer2, &rect);
        SetColor(renderer2, DarkGrey);
        SDL_RenderDrawRect(renderer2, &rect);
    }
}


void Draw_Grid(SDL_Renderer *renderer)
{
    SetColor(renderer, White);
    for (int i = 0; i < WindowWidth; i += BlockWidth)
        SDL_RenderDrawLine(renderer, i, 0, i, WindowHeight);
    for (int i = 0; i < WindowHeight; i += BlockHeight)
        SDL_RenderDrawLine(renderer, 0, i, WindowWidth, i);
    
}


void Draw_Box(SDL_Renderer *renderer, int x, int y, int color)
{   
   
    if (color != -1)//if (x > -1 && x < WindowWidth + BlockWidth && -1 < y && y < WindowHeight + BlockWidth)
    {
        SetColor(renderer, color);
        SDL_Rect block = {.x = x, .y = y, .w = BlockWidth, .h = BlockHeight};
        SDL_RenderFillRect(renderer, &block);
        SetColor(renderer, DarkGrey);
        SDL_RenderDrawRect(renderer, &block);
    }
}

void Draw_Boxes(SDL_Renderer *renderer)
{
    for (int x = 0; x < BlocksInX; x++)
    {
        for (int y = 0; y < BlocksInY; y++)
        {
            Draw_Box(renderer, x * BlockWidth, y * BlockHeight, ScreenBoxes[x][y]);
        }
    }
}


void Draw_Block(SDL_Renderer *renderer, Block *block)
{
    Set_Block_Boxes(block);
    for (int box = 0; box < 4; box++)
        Draw_Box(renderer, block->boxes[box][0], block->boxes[box][1], block->type);
}


#endif