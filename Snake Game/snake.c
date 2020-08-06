#include "Game_Values.h"
// #include "Game_Graphics.h"
// #include "Game_Logic.h"
// #include "Linked_Lists.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        fprintf(stderr, "Init Failure : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("Snake Game", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Window Failure : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC); 
    if (renderer == NULL)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Renderer Failure : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    } 
    
    SDL_Event event;
    Player *player = Create_Player();
    Game_Info *game = Create_Game();
    Fruit *fruit = Create_Fruit(player, game);
    Draw_Screen(renderer, player, fruit);
    while (game->state)
    {
        while (SDL_PollEvent(&event))
        {
            //player.tick_last_updated = clock();
            switch (event.type)
            {
                case SDL_QUIT:
                    game->state = Game_Exit;
                    break;

                case SDL_KEYDOWN:
                    if (player->turn_state)
                    {
                        switch (event.key.keysym.sym)
                        {
                            case SDLK_LEFT:
                                if (player->direction != Direction_Right && player->previous_direction != Direction_Right)
                                {
                                    player->direction = Direction_Left;
                                   // fprintf(stderr, "Left");
                                  //  player->turn_state = Turning;
                                }
                                break;
                            case SDLK_RIGHT:
                                if (player->direction != Direction_Left && player->previous_direction != Direction_Left)
                                {
                                    player->direction = Direction_Right;
                                   // fprintf(stderr, "Right");
                                   // player->turn_state = Turning;
                                }
                                break;
                            case SDLK_UP:
                                if (player->direction != Direction_Down && player->previous_direction != Direction_Down)                        
                                {
                                    player->direction = Direction_Up;
                                   // fprintf(stderr, "Up");
                                   // player->turn_state = Turning;
                                }
                                break;
                            case SDLK_DOWN:
                                if (player->direction != Direction_Up && player->previous_direction != Direction_Up)
                                {
                                    player->direction = Direction_Down;
                                   // fprintf(stderr, "Down");
                                   // player->turn_state = Turning;
                                }
                                break;
                        }
                    }
                default:
                    break;
            }
        }
        if (Time_to_update(game))
        {
/*             if (player->x > 600) player->x %= 600;
            if (player->y > 600) player->y %= 600;
            if (player->x < 0) player->x = ScreenWidth - player->x;
            if (player->y < 0) player->y = ScreenWidth - player->y;
            player->x = snap_to_grid(player->x, BlockSize, BlockSize/2);
            player->y = snap_to_grid(player->y, BlockSize, BlockSize/2); */
            Move_Player(game, &player);
            Check_Fruit(player, fruit, game);
            Check_Player_Collision(player, game);
            //Check_Bounds(game, player);
            Draw_Screen(renderer, player, fruit);
        }
    }
    fprintf(stderr, "\n\n");
    free(game);
    delete_list(player);
    SDL_DestroyWindow(window);
    fprintf(stderr, "Game Closed\n\n");
    return EXIT_SUCCESS;


}