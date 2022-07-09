
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
        printf("Key press!\n");
    }
    return true;
}

int main(int argc, char *args[])
{
    Screen screen(800, 600);

    if (!screen.init())
        return 1;

    screen.setEventProcessor(processEvent);

    SDL_Event e;
    bool quit = false;

    while (!quit)
    {
        quit = !screen.processEvents();
    }

    screen.close();

    return 0;
}