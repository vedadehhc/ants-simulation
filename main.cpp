
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "Screen.h"

bool processEvent(SDL_Event &e)
{   
    // user requests quit
    if (e.type == SDL_QUIT)
    {
        return false;
    }

    if (e.type == SDL_KEYUP)
    {
        printf("Pressed key: %d\n", e.key.keysym.sym);
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
        quit = !screen.processEvents();
    }

    screen.close();

    return 0;
}