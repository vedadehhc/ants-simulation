#ifndef SCREEN_H
#define SCREEN_H

#include <SDL.h>
// #include <SDL_image.h>
// #include <SDL_ttf.h>
// #include <SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <functional>

// TODO:
// - add wrapper classes for text, image, etc.
// - add vectors of these wrappers to screen
// - add interfaces to these wrappers in screen

class Screen
{
private:
	// screen dimensions
	int width, height;
	std::string title;

	// Function which returns false if a quit event was detected
	std::function<bool(SDL_Event &)> eventProcessor;
	SDL_Event event;

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture *m_texture;
	Uint32 *m_buffer;

public:
	Screen(int width, int height) : width(width), height(height), title("App") {}

	Screen(int width, int height, std::string title) : width(width), height(height), title(title) {}

	bool init()
	{

		// Initialize SDL
		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		{
			printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
			return false;
		}

		// Create window
		m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
		if (m_window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Quit();
			return false;
		}

		// Create renderer
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
		if (m_renderer == NULL)
		{
			printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());

			freeWindow();
			SDL_Quit();

			return false;
		}

		// Create texture
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, width, height);
		if (m_texture == NULL)
		{
			printf("Texture could not be created! SDL Error: %s\n", SDL_GetError());

			freeRenderer();
			freeWindow();
			SDL_Quit();

			return false;
		}

		// Initialize renderer color
		SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);
		SDL_RenderClear(m_renderer);

		// draw loading symbols
		SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_Rect one = {width / 2 - 20, height / 2, 10, 10};
		SDL_Rect two = {width / 2, height / 2, 10, 10};
		SDL_Rect three = {width / 2 + 20, height / 2, 10, 10};
		SDL_RenderFillRect(m_renderer, &one);
		SDL_RenderFillRect(m_renderer, &two);
		SDL_RenderFillRect(m_renderer, &three);

		// Update the renderer
		SDL_RenderPresent(m_renderer);

		// Initialize image loading
		// int imgFlags = IMG_INIT_PNG;
		// if (!(IMG_Init(imgFlags) & imgFlags))
		// {
		// 	printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		// 	success = false;
		// }

		// // initialize font
		// if (TTF_Init() == -1)
		// {
		// 	printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		// 	success = false;
		// }

		// // initialize sound
		// if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		// {
		// 	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		// 	success = false;
		// }

		m_buffer = new Uint32[width * height];
		memset(m_buffer, 0, width * height * sizeof(Uint32));

		return true;
	}

	bool setPixel(int x, int y, Uint32 color)
	{
		if (x < 0 || x >= width || y < 0 || y >= height)
			return false;

		m_buffer[y * width + x] = color;

		return true;
	}

	void update()
	{
		SDL_UpdateTexture(m_texture, NULL, m_buffer, width * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);
	}

	// void freeSfx()
	// {
	// 	// Mix_FreeChunk(gCollect);
	// 	// Mix_FreeChunk(gDeath);
	// 	// gCollect = NULL;
	// 	// gDeath = NULL;
	// }

	// void freeText()
	// {
	// 	// if ( gTextTexture != NULL ) {
	// 	// SDL_DestroyTexture(gTextTexture);
	// 	// gTextTexture = NULL;
	// 	// textWidth = 0;
	// 	// textHeight = 0;
	// 	// }
	// }

	// void freeFont()
	// {
	// 	// TTF_CloseFont(gFont);
	// 	// gFont = NULL;
	// }

	void freeTexture()
	{
		SDL_DestroyTexture(m_texture);
		m_texture = NULL;
	}

	void freeRenderer()
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = NULL;
	}

	void freeWindow()
	{
		SDL_DestroyWindow(m_window);
		m_window = NULL;
	}

	// Frees media and closes SDL
	void close()
	{
		delete[] m_buffer;

		// freeSfx();
		// freeText();
		// freeFont();
		freeTexture();
		freeRenderer();
		freeWindow();

		// Quit SDL subsystems
		// Mix_Quit();
		// IMG_Quit();
		SDL_Quit();
	}

	bool processEvents()
	{
		while (SDL_PollEvent(&event))
		{
			if (!eventProcessor(event))
				return false;
		}
		return true;
	}

	// getters
	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	void setEventProcessor(std::function<bool(SDL_Event &)> eventProcessor)
	{
		this->eventProcessor = eventProcessor;
	}
};

#endif