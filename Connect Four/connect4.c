#include "Game Values.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Error while Initalizing SDL2: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Window *window = SDL_CreateWindow("Connect Four", 100, 100, ScreenWidth, ScreenHeight, SDL_WINDOW_SHOWN);
    if (!window)
    {
        fprintf(stderr, "Error while Initalizing window: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        SDL_DestroyWindow(window);
        fprintf(stderr, "Error while Initalizing renderer: %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    SDL_Event events;
    int running = 1;
    int noexit = 0;
    srand(clock());
    currentTileColor = (rand() % 2) + 1;
    INIT_TILE_MATRIX();
    INIT_BASECIRCLEVALUES();
    while (running)
    {
        while (SDL_PollEvent(&events))
        {
            switch(events.type)
            {
                case SDL_QUIT:
                    running = 0;
                    noexit = 1;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (events.button.button == SDL_BUTTON_LEFT)
                    {
                        int y = Color_Tiles(events.button.x, events.button.y);
                        if (y != 0)
                            Detect_Line(renderer, events.button.x, y, &running);
                    }
                    
            }
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        Create_Grid(renderer);
        Update_Tiles(renderer);
        SDL_RenderPresent(renderer);
        if (!running && !noexit)
        {
            Update_Tiles(renderer);
            GameOver(renderer);
        }
    }


    SDL_DestroyWindow(window);

    return EXIT_SUCCESS;
}