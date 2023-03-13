#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>
#include "dimensions.h"

typedef unsigned int u32 ;

u32 bars[BARS];

// Drawing
void sortBarsVisualizer(SDL_Renderer *renderer, u32 bars[], int barsLength);

// Sorting
void shuffleArray(u32 array[], int size);

void printBars(u32 bars[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d", bars[i]);
		if (i != size - 1) printf(", ");
	}
	printf("\n");
}

int main(void) {
	srand(time(NULL));
	
	// Initialize Array
	for (int i = 0; i < BARS; ++i) {
		u32 height = (i + 1) * HEIGHT / BARS;
		bars[i] = height;
	}
	shuffleArray(bars, BARS);


	SDL_Window *window = SDL_CreateWindow("Sorting Algorithm", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) return 1;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_TEXTUREACCESS_TARGET);
	if (renderer == NULL) return 1;

	sortBarsVisualizer(renderer, bars, BARS);

	printBars(bars, BARS);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
