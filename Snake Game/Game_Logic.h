


#ifndef GAMELOGIC_H_
#define GAMELOGIC_H_
#include "Game_Values.h"


char Time_to_update(Game_Info *game)
{
    if (clock() - game->tick_last_updated > FrameElapsedTime)
    {
        game->tick_last_updated = clock();
        return 1;
    }
    return 0;
}


void Check_Fruit(Player *player, Fruit *fruit, Game_Info *game)
{
    if (fruit->x == player->x && fruit->y == player->y)
    {
        Refresh_Fruit(fruit, player, game);
        Grow_Snake(player);
    }
}

void Move_Player(Game_Info *game, Player **player)
{
    //if (clock() - game->tick_last_updated > FrameElapsedTime)
    {
       // game->tick_last_updated = clock();
        (*player)->previous_direction = (*player)->direction;
        if ((*player)->next != NULL) //if player is larger than size one
        {
            Player *temp = *player;
            while (temp->next->next != NULL)
                temp = temp->next;
            
            (*player)->color = Green;
            temp->next->next = *player;
            temp->next->direction = (*player)->direction;
            temp->next->previous_direction = (*player)->previous_direction;
            temp->next->x = (*player)->x;
            temp->next->y = (*player)->y;
            temp->next->color = DarkGreen;
            *player = temp->next;         
            temp->next = NULL;

        }

        switch((*player)->direction)
        {
            case Direction_Down:
                (*player)->y += PlayerSpeed;
                break;
            case Direction_Up:
                (*player)->y -= PlayerSpeed;
                break;
            case Direction_Right:
                (*player)->x += PlayerSpeed;
                break;
            case Direction_Left:
                (*player)->x -= PlayerSpeed;
                break;       
            default:
                break;
        }
        //(*player)->turn_state = Turnable;
    }
}


#endif