#include "Game_Values.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Error while Initalizing SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window = SDL_CreateWindow("Tetris", WindowX, WindowY, WindowWidth, WindowHeight, SDL_WINDOW_SHOWN);
    SDL_Window *window2 = SDL_CreateWindow("other thing", WindowX + WindowWidth, WindowY, OtherWindowWidth, OtherWindowHeight, SDL_WINDOW_SHOWN);
    if (!window || !window2)
    {
        fprintf(stderr, "Error while Initalizing window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Renderer *renderer2 = SDL_CreateRenderer(window2, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer || !renderer2)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyWindow(window2);
        fprintf(stderr, "Error while Initalizing renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    int rotation_testing = 0;
    int counter = 0;
    SDL_Event events;
    int leave = 1;
    Block *block = Create_Block();
    LastUpdate = clock();
    INIT_SCREEN_BOXES();
    //ScreenBoxes[2][3] = 1;
    while (leave)
    {
        if (block->life == Inactive)
        {
            break;
        }
        block->direction = DirectionStill;
        while (SDL_PollEvent(&events))
        {
            if (events.type == SDL_WINDOWEVENT && events.window.event == SDL_WINDOWEVENT_CLOSE)
            {
                fprintf(stderr, "Game Over\n");
                leave = 0;
                break;
            }
            if (events.type == SDL_KEYDOWN)
            {
                switch (events.key.keysym.sym)
                {
                    case SDLK_DOWN:
                        block->direction = DirectionDown;
                        break;
                    case SDLK_RIGHT:                    
                        block->direction = DirectionRight;
                        block->movingStatus = Inactive;
                        break;
                    case SDLK_LEFT:
                        block->direction = DirectionLeft;
                        block->movingStatus = Inactive;
                        break;
                    case SDLK_a:
                        if (block->rotationalStatus)
                        {
                            block->rotate = RotateLeft;
                            block->rotationalStatus = Inactive;
                        }
                        break;
                    case SDLK_s:
                        if (block->rotationalStatus)
                        {
                            block->rotate = RotateRight;
                            block->rotationalStatus = Inactive;
                        }
                        break;
                    default:
                        break;
                }
            }
            if (events.type == SDL_KEYUP)
            {
                switch (events.key.keysym.sym)
                {
                    case SDLK_a:
                        block->rotationalStatus = Active;
                        break;
                    case SDLK_s:
                        block->rotationalStatus = Active;
                        break;
                    default:
                        break;
                        
                }
            }
        }
        
        SetColor(renderer, Black);
        SetColor(renderer2, Black);
        SDL_RenderClear(renderer);
        SDL_RenderClear(renderer2);
        if (LastUpdate < clock())
        {
            LastUpdate += speedUpInterval;
            block->direction += DirectionDown;
        }
        Rotate_Block(block);
        Move_Block(block);
        Draw_Grid(renderer);
        Draw_Boxes(renderer);
        Draw_NextBlock(renderer2, block);
        Draw_Block(renderer, block);
        SDL_RenderPresent(renderer);
        SDL_RenderPresent(renderer2);

    }
    free(block);
    SDL_DestroyWindow(window);
    SDL_DestroyWindow(window2);
    return EXIT_SUCCESS;
}