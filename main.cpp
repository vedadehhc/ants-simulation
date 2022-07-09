
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "Screen.h"

// int pixelX = 0;
// int pixelY = 0;

bool processEvent(SDL_Event &e)
{
    // user requests quit
    if (e.type == SDL_QUIT)
    {
        return false;
    }

    if (e.type == SDL_KEYDOWN)
    {
        // printf("Pressed key: %d\n", e.key.keysym.sym);
        // switch (e.key.keysym.sym)
        // {
        // case SDLK_RIGHT:
        //     pixelX++;
        //     break;

        // case SDLK_LEFT:
        //     pixelX--;
        //     break;

        // case SDLK_UP:
        //     pixelY--;
        //     break;

        // case SDLK_DOWN:
        //     pixelY++;
        //     break;
        // }
    }
    return true;
}

int main(int argc, char *args[])
{
    Screen screen(800, 600, "Ants");

    if (!screen.init())
        return 1;

    screen.setEventProcessor(processEvent);

    // Main game loop
    bool quit = false;
    while (!quit)
    {
        screen.clear();

        // screen.setPixel(pixelX, pixelY, 0xFF0000FF);

        // Draw screen
        screen.update();

        quit = !screen.processEvents();
    }

    screen.close();

    return 0;
}