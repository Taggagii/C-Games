#include "Game_Graphics.h"
#include "Game_Logic.h"

#ifndef GAME_VALUES_H_
#define GAME_VALUES_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL2/SDL.h>


//WINDOW DATA//
#define WindowX 200 
#define WindowY 100
#define WindowHeight 700
#define OtherWindowHeight WindowHeight/4
#define WindowWidth WindowHeight/2
#define OtherWindowWidth WindowWidth/2

//SCREEN DATA//
#define BlocksInY 20
#define BlocksInX 10
#define BlockHeight (int)(WindowHeight / BlocksInY)
#define BlockWidth (int)(WindowWidth / BlocksInX)


//GAME DATA//
#define DropSpeed 1
clock_t LastUpdate;
int speedUpInterval = 90000;

//ENUMS//
enum Blocks {Line = 0, RightL, LeftL, ThreeProng, Cube, CurveL, CurveR};
enum Rotation {Rotation_Up = 0, Rotation_Right, Rotation_Down, Rotation_Left};
enum Color_Grabber {LightBlue, Red, Blue, Magenta, Yellow, Green, Orange, White, Black, DarkGrey}; //CONTINUE THIS    
enum Directions {DirectionStill = 0, DirectionUp, DirectionRight, DirectionDown, DirectionLeft};
enum Rotate {RotateStill = 0, RotateRight, RotateLeft};
enum Status {Inactive = 0, Active};


//BOXES//
int ScreenBoxes[BlocksInX][BlocksInY];


//BLOCKS//
float Block_Data[7][4][2] = {
    {{0, 1}, {0, 0}, {0, -1}, {0, -2}}, //line
    {{0, 1}, {0, 0}, {0, -1}, {1, -1}}, //rightL
    {{0, 1}, {0, 0}, {0, -1}, {-1, -1}}, //leftl
    {{0, 1}, {0, 0}, {0, -1}, {1, 0}}, //threeprong
    {{0, 0}, {0, 1}, {1, 1}, {1, 0}}, //box
    {{0, 1}, {0, 0}, {1, 0}, {1, -1}}, //curveL
    {{1, 1}, {1, 0}, {0, 0}, {0, -1}} //cruveR
};

int Colors[][3] = { //FIX THE COLORS
    {0, 255, 255}, //light blue
    {255, 0, 0}, // red
    {0, 0, 255}, //blue
    {160, 0, 240}, //magenta?
    {255, 255, 0}, //yellow
    {0, 255, 0}, //green 
    {255, 165, 0}, //orange 
    {255, 255, 255}, //white
    {0, 0, 0}, //black
    {100, 100, 100} //dark gray
};

//FUNCTIONS//
void SetColor(SDL_Renderer *renderer, int color)
{
    SDL_SetRenderDrawColor(renderer, Colors[color][0], Colors[color][1], Colors[color][2], 255);
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
    srand(rand() + clock() + time(0));
    return rand() % (upper - lower + 1) + lower;
}




//OBJECTS//
typedef struct
{
    int nextblock;
    int type;
    int x, y;
    int rotation;
    int direction;
    int rotate;
    int movingStatus;
    int rotationalStatus;
    int boxes[4][2];
    int life;
} Block;



//CREATION//


void INIT_SCREEN_BOXES()
{
    for (int x = 0; x < BlocksInX; x++)
    {
        for (int y = 0; y < BlocksInY; y++)
        {
            ScreenBoxes[x][y] = -1;
        }
    }
}


int get_random_block(Block *block)
{
    int type = get_random_int_in_range(0, 6);
/*     if (type == 0)
    {
        int value = get_random_int_in_range(0, 6); //this is just mean man
        if (value > 2) 
            return type;
        return get_random_int_in_range(0, 6);
    } */
    return type;
}

int check_intersection(Block *block)
{
    for (int box = 0; box < 4; box++)
    {
        int x = block->boxes[box][0] / BlockWidth, y = block->boxes[box][1] / BlockHeight;
        for (int x2 = 0; x2 < BlocksInX; x2++)
        {
            for (int y2 = 0; y2 < BlocksInY; y2++)
            {
                if (ScreenBoxes[x2][y2] != -1 && x == x2 && y == y2)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}

void Set_Block_Boxes(Block *block)
{
    for (int box = 0; box < 4; box++)
    { 
        float x, y;
        switch (block->rotation)
        {
            case Rotation_Up:
                x = Block_Data[block->type][box][0];
                y = -Block_Data[block->type][box][1];
                break;
            case Rotation_Right:
                x = -Block_Data[block->type][box][1];
                y = -Block_Data[block->type][box][0];
                break;
            case Rotation_Down:
                x = -Block_Data[block->type][box][0];
                y = Block_Data[block->type][box][1];
                break;
            case Rotation_Left:
                x = Block_Data[block->type][box][1];
                y = Block_Data[block->type][box][0];
                break;
            default:
                break;
        }
        block->boxes[box][0] = block->x + x * BlockWidth;
        block->boxes[box][1] = block->y + y * BlockHeight;
    }
} 


void Refresh_Block(Block *block)
{
    block->type = block->nextblock;
    block->nextblock = get_random_block(block);
    block->x = BlockWidth * (int)((BlocksInX - 1) / 2);
    block->y = BlockHeight;
    block->rotation = Rotation_Up;
    block->direction = DirectionStill;
    block->movingStatus = Active;
    block->rotationalStatus = Active;
    Set_Block_Boxes(block);
    if (check_intersection(block) && block->life == Active)
        block->life = Inactive;
    else
        block->life = Active;
}

Block *Create_Block()
{
    Block *block = (Block*) malloc(sizeof(Block));
    block->nextblock = get_random_block(block);
    Refresh_Block(block);
    return block;
}

#endif