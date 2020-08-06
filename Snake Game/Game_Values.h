#include "Game_Logic.h"
#include "Game_Graphics.h"
#include "Linked_Lists.h"

#ifndef _GAMEVALUES_H_
#define _GAMEVALUES_H_
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>

//screen//
#define ScreenWidth 600
#define ScreenHeight ScreenWidth
#define BlockAmount 13
#define BlockSize (int)ScreenWidth / BlockAmount



//values// 
#define FramesPerSecond 6//3.5
#define FrameElapsedTime CLOCKS_PER_SEC/(double)FramesPerSecond
#define RefreshFruitMax 10

//colors//
const SDL_Color Gray = {.r = 221, .g = 221, .b = 221};
const SDL_Color Green = {.r = 0, .g = 255, .b = 0};
const SDL_Color DarkGreen = {.r = 0, .g = 200, .b = 0};
const SDL_Color Black = {.r = 0, .g = 0, .b = 0};
const SDL_Color Red = {.r = 255, .g = 0, .b = 0};

//states//
enum GameState {Game_Exit = 0, Game_Running};
enum Direction {Direction_Still = 0, Direction_Up, Direction_Right, Direction_Down, Direction_Left};
enum FruitState {Fruit_Alive = 0, Fruit_Eaten};
enum TurnState {Turning = 0, Turnable};

//static player data//
#define PlayerHeight BlockSize
#define PlayerWidth BlockSize
#define PlayerSpeed BlockSize
#define FruitHeight BlockSize / 4
#define FruitWidth BlockSize / 4

//mutable player data//
int SnakeLength = 1;

//General Functions//
void Set_Color(SDL_Renderer *renderer, const SDL_Color *color)
{
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
}

int snap_to_grid(int input, int multiple, int base)
{
    float value = ((float)(input - base) / multiple);
    int index = (int)value;
    value -= index;
    if (value > 0.5) return (index + 1) * multiple + base;
    return index * multiple + base;
}

int get_random_int_in_range(int lower, int upper)
{
    srand(rand() + clock());
    return rand() % (upper - lower + 1) + lower;
}

int Check_GameOver()
{
    if (SnakeLength >= BlockAmount*BlockAmount)
        return 1;
    return 0;
}




//objects//
typedef struct {
    int state;
    clock_t tick_last_updated;
} Game_Info;

struct Player_t {
    int x, y;
    int direction;
    int previous_direction;
    int turn_state;
    SDL_Color color;
    struct Player_t *next;
};
typedef struct Player_t Player;

void Grow_Snake(Player *player)
{
    Player *temp = player;
    while (temp->next != NULL)
        temp = temp->next;
    
    temp->next = (Player*) malloc(sizeof(Player));
    temp->next->direction = temp->direction;
    temp->next->x = temp->x;
    temp->next->y = temp->y;
    temp->next->color = Green;
    temp->next->next = NULL;
    
    //fprintf(stderr, "one %d\ntwo %d\nThree %d\n", temp->next->direction, temp->next->x, temp->next->y);
    switch(temp->next->direction)
    {
        case Direction_Down:
            temp->next->y -= PlayerSpeed;
            break;
        case Direction_Up:
            temp->next->y += PlayerSpeed;
            break;
        case Direction_Right:
            temp->next->x -= PlayerSpeed;
            break;
        case Direction_Left:
            temp->next->x += PlayerSpeed;
            break;
        default:
            break;
    }
    SnakeLength++;
}

void Check_Bounds(Game_Info *game, Player *player)
{
    if (player->x > ScreenWidth || player->x < 0 || player->y > ScreenHeight || player->y < 0)
    {
        game->state = Game_Exit;
    }
}

void Check_Player_Collision(Player *player, Game_Info *game)
{
    Check_Bounds(game, player);
    Player *temp = player->next;
    if (player->previous_direction != Direction_Still)
    {
        while (temp != NULL)
        {
            if (temp->x == player->x && temp->y == player->y)
                game->state = Game_Exit;
            temp = temp->next;
        }
    }
}

typedef struct
{
    int x, y;
} Fruit;

char Fruit_In_Snake(Fruit *fruit, Player *player)
{
    Player *temp = player;
    while (temp != NULL)
    {
        if (temp->x == fruit->x && temp->y == fruit->y)
        {
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}


void Refresh_Fruit(Fruit *fruit, Player *player, Game_Info *game)
{
    int counter = 0;
    do
    {
        if (counter > RefreshFruitMax)
        {
            if (Check_GameOver())
                game->state = Game_Exit;
            else
                counter = 0;
        }
        counter++;
        fruit->x = snap_to_grid(get_random_int_in_range(0, 600), BlockSize, BlockSize/2);
        fruit->y = snap_to_grid(get_random_int_in_range(0, 600), BlockSize, BlockSize/2);
    } while (Fruit_In_Snake(fruit, player) || fruit->x > 600 || fruit->y > 600);
}

Fruit* Create_Fruit(Player *player, Game_Info *game)
{
    Fruit *fruit = (Fruit*) malloc(sizeof(Fruit));
    Refresh_Fruit(fruit, player, game);
    return fruit;
}


Game_Info* Create_Game()
{
    Game_Info *game = (Game_Info*) malloc(sizeof(Game_Info));
    game->state = Game_Running;
    game->tick_last_updated = clock();
    return game;
}

Player* Create_Player()
{
    Player *player = (Player*)malloc(sizeof(Player));
    player->x = snap_to_grid(ScreenWidth/2, BlockSize, BlockSize/2);
    player->y = snap_to_grid(ScreenHeight/2, BlockSize, BlockSize/2);
    player->direction = Direction_Still; 
    player->previous_direction = Direction_Still;
    player->turn_state = Turnable;
    player->color = DarkGreen;
    player->next = NULL;
    Grow_Snake(player);
    return player;
}




#endif