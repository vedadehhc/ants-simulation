
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>

#include "Screen.h"
#include "Ant.h"
#include "Food.h"
#include "Trail.h"

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
    Screen screen(720, 720, "Ants");

    if (!screen.init())
        return 1;

    screen.setEventProcessor(processEvent);

    // initialize trails
    Trail exploreTrail(0x0000FFFF);
    Trail returnTrail(0xFFCC00FF);

    // initialize ants
    const int NUM_ANTS = 100;
    const int ANT_HOME_X = screen.getWidth() / 2;
    const int ANT_HOME_Y = 3 * screen.getHeight() / 4;

    Ant *ants = new Ant[NUM_ANTS];

    for (int i = 0; i < NUM_ANTS; i++)
    {
        ants[i] = Ant(ANT_HOME_X, ANT_HOME_Y, &exploreTrail, &returnTrail);
    }

    // initialize food
    const int NUM_FOOD = 5000;
    for (int i = 0; i < NUM_FOOD; i++)
    {
        float r = randFloat() * 50;
        float t = randFloat() * M_PI * 2;
        Food::addFood(screen.getWidth() / 2 + r * cos(t), screen.getHeight() / 4 + r * sin(t));
    }

    // Main game loop
    Uint32 prevTime = SDL_GetTicks();
    bool quit = false;
    while (!quit)
    {
        Uint32 curTime = SDL_GetTicks();
        Uint32 elapsed = curTime - prevTime;
        prevTime = curTime;

        screen.clear();

        // render ant home
        screen.drawFillCircle(ANT_HOME_X, ANT_HOME_Y, Ant::HOME_RADIUS, 0x0000FF80);

        // update + render trails
        exploreTrail.update(elapsed);        
        returnTrail.update(elapsed);
        
        exploreTrail.render(screen);
        returnTrail.render(screen);

        // render food
        for (std::list<Food *>::iterator it = Food::foods.begin(); it != Food::foods.end(); it++)
        {
            (*it)->render(screen);
        }

        // render ants
        for (int i = 0; i < NUM_ANTS; i++)
        {
            ants[i].move(elapsed, screen.getWidth(), screen.getHeight());
            ants[i].render(screen);
        }

        // Draw screen
        screen.update();

        quit = !screen.processEvents();
    }

    delete[] ants;
    Food::deleteAll();
    screen.close();

    return 0;
}