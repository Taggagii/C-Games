#ifndef LOGIC_H_
#define LOGIC_H_

#include "Game_Values.h"

void Lock_Block(Block *block)
{
    for (int box = 0; box < 4; box++)
    {
        int x = block->boxes[box][0] / BlockWidth, y = block->boxes[box][1] / BlockHeight;
        ScreenBoxes[x][y] = block->type;
    }
}

void Complete_Lines()
{
    for (int y = 0; y < BlocksInY; y++)
    {
        int complete = 1;
        for (int x = 0; x < BlocksInX; x++)
        {
            if (ScreenBoxes[x][y] == -1)
            {
                complete = 0;
                break;
            }
        }
        if (complete)
        {
            for (int x = 0; x < BlocksInX; x++) 
                ScreenBoxes[x][y] = -1;
            for (int y2 = y; y2 > 0; y2--)
            {
                for (int x = 0; x < BlocksInX; x++)
                {
                    ScreenBoxes[x][y2] = ScreenBoxes[x][y2-1];
                    ScreenBoxes[x][y2-1] = -1;
                }
            }
            y--;
        }
    }
}





int check_block_against_border(Block *block)
{
    for (int box = 0; box < 4; box++)
    {
        Set_Block_Boxes(block);
        float x = block->boxes[box][0], y = block->boxes[box][1];
        switch (block->direction)
        {
            case DirectionUp:
                y -= BlockHeight;
                break;
            case DirectionDown:
                y += BlockHeight;
                break;
            case DirectionLeft:
                x -= BlockWidth;
                break;
            case DirectionRight:
                x += BlockWidth;
                break;
            default:
                break;
        }
        if (y < 0 || x > WindowWidth - BlockWidth || x < 0)
            return 1;
        else if (y > WindowHeight - BlockHeight)
            return 2;
    }
    return 0;
}


int check_block_against_boxes(Block *block)
{
    Set_Block_Boxes(block);
    for (int box = 0; box < 4; box++)
    {
        int x = block->boxes[box][0], y = block->boxes[box][1];
        switch (block->direction)
        {
            case DirectionUp:
                y -= BlockHeight;
                break;
            case DirectionDown:
                y += BlockHeight;
                break;
            case DirectionLeft:
                x -= BlockWidth;
                break;
            case DirectionRight:
                x += BlockWidth;
                break;
            default:
                break;
        }
        x /= BlockWidth;
        y /= BlockHeight;
        for (int x2 = 0; x2 < BlocksInX; x2++)
        {
            for (int y2 = 0; y2 < BlocksInY; y2++)
            {
                if (ScreenBoxes[x2][y2] != -1 && x == x2 && y == y2)
                {
                    if (block->direction == DirectionDown)
                        return 2;
                    return 1;
                }
            }
        }
    }
    return 0;
}

int push_from_wall(Block *block)
{
    for (int box = 0; box < 4; box++)
    {
        Set_Block_Boxes(block);
        float x = block->boxes[box][0], y = block->boxes[box][1];
        if (x > WindowWidth - BlockWidth)
        {
            block->x -= BlockWidth;
            return 1;
        }
        else if (x < 0)
        {
            block->x += BlockWidth;
            return 1;
        }
        if (y > WindowHeight - BlockHeight)
        {
            block->y -= BlockHeight;
            return 1;
        }
        else if (y < 0)
        {
            block->y += BlockHeight;
            return 1;
        }
    }
    return 0;
}




void Rotate_Block(Block *block)
{
    int base_rotation = block->rotation;
    int x = block->x, y = block->y;
    if (block->rotate == RotateLeft)
    {
        block->rotation++;
        block->rotation %= 4;
    }
    if (block->rotate == RotateRight)
    {
        block->rotation--;
        if (block->rotation < 0) block->rotation = 4 + block->rotation;
    }
    int value;
    do value = push_from_wall(block); while (value);
    if (check_intersection(block)) block->rotation = base_rotation;
    block->rotate = RotateStill; 
}


int Check_Block_Collision(Block *block)
{
    int value = check_block_against_border(block);
    int value2 = check_block_against_boxes(block);
    if (value > value2)
        return value;
    else if (value2 > value)
        return value2;
    return value;
}


void Move_Block(Block *block)
{
    int will_collide = Check_Block_Collision(block);
    if (!will_collide)
    {
        switch (block->direction)
        {
            case DirectionUp:
                block->y -= BlockHeight;
                break;
            case DirectionDown:
                block->y += BlockHeight;
                break;
            case DirectionRight:
                block->x += BlockWidth;
                break;
            case DirectionLeft:
                block->x -= BlockWidth;
                break;
            default:
                break;
        }
    }
    else if (will_collide == 2)
    {
        Set_Block_Boxes(block);
        Lock_Block(block);
        Refresh_Block(block);
        Complete_Lines();
    }
    block->direction = DirectionStill;
}



#endif