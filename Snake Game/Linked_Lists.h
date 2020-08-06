

#ifndef LINKEDLIST_H_   
#define LINKEDLIST_H_
#include "Game_Values.h"

void print_list(Player *head)
{
    Player *temp = head;
    while (temp != NULL)
    {
        fprintf(stderr, "Direction : %d\nx : %d\ny : %d\n", temp->direction, temp->x, temp->y);
        temp = temp->next;
    }
}


void delete_list(Player *player)
{
    Player *previous, *current = player;
    while (current != NULL)
    {
        previous = current;
        current = current->next;
        free(previous);
    }
    fprintf(stderr, "Snake Murdered\n");
}


#endif 