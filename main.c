#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include "dimensions.h"

#define BARS 100
#define DELAY 5

typedef unsigned int u32 ;

u32 bars[BARS];

void printBars(u32 bars[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d", bars[i]);
		if (i != size - 1) printf(", ");
	}
	printf("\n");
}

void randomizeBars(u32 bars[], int size) {
	for (int i = 0; i < size; ++i) {
		u32 height = (i + 1) * HEIGHT / size;
		bars[i] = height;
	}
	if (size > 1) {
		size_t i;
		for (i = 0; i < size - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			u32 t = bars[j];
			bars[j] = bars[i];
			bars[i] = t;
		}
	}
}; 

void clearScreen(SDL_Renderer *renderer) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void drawBar(SDL_Renderer *renderer, int x, int y, int width, int height, Uint8 colorRed, Uint8 colorGreen, Uint8 colorBlue) {
	SDL_Rect rectangle;
	rectangle.w = width;
	rectangle.h = height;
	rectangle.x = x;
	rectangle.y = y;
	SDL_SetRenderDrawColor(renderer, colorRed, colorGreen, colorBlue, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &rectangle);
}

void drawBars(SDL_Renderer *renderer, u32 bars[], int barsLength, int swapIndex1, int swapIndex2) {
	clearScreen(renderer);

	SDL_Rect rectangle;
	rectangle.w = WIDTH / barsLength;

	for (int i = 0; i < barsLength; ++i) {
		rectangle.x = i * rectangle.w;
		rectangle.y = HEIGHT - bars[i];
		rectangle.h = bars[i];

		if (i == swapIndex1 || i == swapIndex2)
			SDL_SetRenderDrawColor(renderer, 28, 219, 61, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		SDL_RenderFillRect(renderer, &rectangle);
	}

	// Update
	SDL_RenderPresent(renderer);
}

void drawSortedBars(SDL_Renderer *renderer, u32 bars[], int barsLength) {
	clearScreen(renderer);

	int dw = WIDTH / barsLength;
	for (int i = 0; i < barsLength; ++i) {
		drawBar(renderer, i * dw, HEIGHT - bars[i], dw, bars[i], 0, 255, 0);
	}
	SDL_RenderPresent(renderer);
}

void sortBarsVisualizer(SDL_Renderer *renderer, u32 bars[], int barsLength) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	drawBars(renderer, bars, barsLength, -1, -1);

	int swaps;
	do {
		swaps = 0;
		for (int i = 0; i < barsLength - 1; ++i) {
			if (bars[i + 1] >= bars[i]) continue;
			SDL_Delay(DELAY);

			// Swap
			++swaps;
			u32 temp = bars[i];
			bars[i] = bars[i + 1];
			bars[i + 1] = temp;
			drawBars(renderer, bars, barsLength, i, i + 1);

		}
	} while (swaps != 0);

	drawSortedBars(renderer, bars, barsLength, 50);
}

int main(void) {
	srand(time(NULL));

	SDL_Window *window = SDL_CreateWindow("Sorting Algorithm", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) return 1;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_TEXTUREACCESS_TARGET);
	if (renderer == NULL) return 1;

	randomizeBars(bars, BARS);

	sortBarsVisualizer(renderer, bars, BARS);

	printBars(bars, BARS);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
