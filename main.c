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

typedef unsigned int u32 ;

u32 bars[BARS];

// Drawing
void sortBarsVisualizer(SDL_Renderer *renderer, u32 bars[], int barsLength);

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
