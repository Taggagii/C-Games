

#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_
#include "Game_Values.h"

void Draw_Grid(SDL_Renderer *renderer, const SDL_Color *color)
{
    Set_Color(renderer, color);
    for (int i = 0; i < ScreenWidth; i += BlockSize)
    {
        SDL_RenderDrawLine(renderer, i, 0, i, ScreenHeight);
        SDL_RenderDrawLine(renderer, 0, i, ScreenWidth, i);
        
    }
    SDL_RenderDrawLine(renderer, ScreenHeight - 1, 0, ScreenHeight - 1, ScreenWidth);
    SDL_RenderDrawLine(renderer, 0, ScreenWidth - 1, ScreenHeight, ScreenWidth - 1);
}

void Draw_Fruit(SDL_Renderer *renderer, Fruit *fruit, const SDL_Color *color)
{
    SDL_Rect fruit_rect = {.x = fruit->x - FruitWidth/2, .y = fruit->y - FruitHeight/2, .w = FruitWidth, .h = FruitHeight};
    Set_Color(renderer, color);
    SDL_RenderFillRect(renderer, &fruit_rect);
}

void Draw_Player(SDL_Renderer *renderer, Player *player)
{
    Player *temp = player;
    while (temp != NULL)
    {   
        if (temp->x > 0 && temp->x < ScreenWidth && temp->y > 0 && temp->y < ScreenHeight)
        {
            SDL_Rect player_rect = {.x = temp->x - PlayerWidth/2, .y = temp->y - PlayerHeight/2, .w = PlayerWidth, .h = PlayerHeight};
            Set_Color(renderer, &temp->color);
            SDL_RenderFillRect(renderer, &player_rect);
            temp = temp->next;
        }
        else
        {
            temp = temp->next;
            continue;
        }
    }
    SDL_Rect player_rect = {.x = player->x - PlayerWidth/2, .y = player->y - PlayerHeight/2, .w = PlayerWidth, .h = PlayerHeight};
    Set_Color(renderer, &player->color);
    SDL_RenderFillRect(renderer, &player_rect);
}


void Draw_Screen(SDL_Renderer *renderer, Player *player, Fruit *fruit)
{
    Set_Color(renderer, &Black);
    SDL_RenderClear(renderer);
    Draw_Grid(renderer, &Gray);
    Draw_Player(renderer, player);
    Draw_Fruit(renderer, fruit, &Red);
    SDL_RenderPresent(renderer);
}


#endif