
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "Screen.h"
#include "Ant.h"

using namespace ants;

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


    const int NUM_ANTS = 100;
    Ant* ants = new Ant[NUM_ANTS];

    for(int i = 0; i < NUM_ANTS; i++)
    {
        ants[i] = Ant(rand() % screen.getWidth(), rand() % screen.getHeight());
    }

    // Main game loop
    bool quit = false;
    while (!quit)
    {
        screen.clear();

        for (int i = 0; i < NUM_ANTS; i++)
        {
            ants[i].render(screen);
        }

        // Draw screen
        screen.update();

        quit = !screen.processEvents();
    }

    delete[] ants;
    screen.close();

    return 0;
}