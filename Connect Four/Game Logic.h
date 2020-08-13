#ifndef _GAME_LOGIC_
#define _GAME_LOGIC_ 

#include "Game Values.h"

void GameOver(SDL_Renderer *renderer)
{
    //SDL_RenderSetScale(renderer, 100.0f, 100.0f);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderDrawLine(renderer, GameOverX, GameOverY, GameOverX2, GameOverY2);
    SDL_RenderPresent(renderer);
    char name[5];
    if (currentTileColor == 1)
        strcpy(name, "Red");
    else
        strcpy(name, "Blue");
    printf("\n\nGameOver\n%s created a line from point (%d, %d) to point (%d, %d)\nCongratulations!!!\n\n",
                                        name, GameOverBoxX, GameOverBoxY, GameOverBoxX2, GameOverBoxY2);
    sleep(5);
}


int ValueInMatrixWithDirection(int x, int y, int direction, int shiftValue)
{
    switch(direction)
    {
        case 0:
            x += shiftValue;
            break;
        case 1:
            y += shiftValue;
            break;
        case 2:
            x -= shiftValue;
            break;
        case 3: //diagonals start
            x += shiftValue;
            y -= shiftValue;
            break;
        case 4:
            x += shiftValue;
            y += shiftValue;
            break;
        case 5: 
            x -= shiftValue;
            y += shiftValue;
            break;
        case 6: 
            x -= shiftValue;
            y -= shiftValue;
            break;
        default: 
            break;
    }
    if (x > -1 && y > -1 && x < TilesInX && y < TilesInY)
        return TileMatrix[x][y];
    return 0;
}

void Detect_Line(SDL_Renderer *renderer, int x, int y, int *running)
{
    x = (snap_to_grid(x, TileWidth, TileBaseValueX) - TileBaseValueX) / TileWidth;
    int color = TileMatrix[x][y];
    int directions[7] = {1, 1, 1, 1, 1, 1, 1};
    for (int shiftvalue = 0; shiftvalue < 4; shiftvalue++)
    {
        for (int direction = 0; direction < 7; direction++)
        {
            if (directions[direction] != 0)
            {
                if (ValueInMatrixWithDirection(x, y, direction, shiftvalue) != color)
                    directions[direction] = 0;
            }
        }
    }
    for (int i = 0; i < (sizeof(directions)/sizeof(directions[0])); i++)
    {
        if (directions[i])
        {
            GameOverX = TileBaseValueX + x * TileWidth, GameOverY = TileBaseValueY + y * TileHeight;
            GameOverBoxX = x, GameOverBoxY = y;

            switch(i)
            {
                case 0:
                    x += 3;
                    break;
                case 1:
                    y += 3;
                    break;
                case 2:
                    x -= 3;
                    break;
                case 3:
                    x += 3;
                    y -= 3;
                    break;
                case 4:
                    x += 3;
                    y += 3;
                    break;
                case 5: 
                    x -= 3;
                    y += 3;
                    break;
                case 6: 
                    x -= 3;
                    y -= 3;
                    break;
                default: 
                    break;
            }
            GameOverBoxX2 = x; GameOverBoxY2 = y;
            x = TileBaseValueX + x * TileWidth, y = TileBaseValueY + y * TileHeight;
            GameOverX2 = x, GameOverY2 = y;
            *running = 0;
            break;
        }
    }
}

int Color_Tiles(int x, int y)
{
    x = (snap_to_grid(x, TileWidth, TileBaseValueX) - TileBaseValueX) / TileWidth;
    y = (snap_to_grid(y, TileHeight, TileBaseValueY) - TileBaseValueY) / TileHeight;
    if (TileMatrix[x][y] == 0)
    { 
        while (y < TilesInY - 1 && TileMatrix[x][y + 1] == 0) y++;
        TileMatrix[x][y] = currentTileColor;
        currentTileColor %= 2;
        currentTileColor++;
    }
    else
        return 0;
    return y;
}

#endif