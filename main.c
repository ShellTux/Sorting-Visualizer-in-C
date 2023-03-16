#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include "dimensions.h"
#include "definitions.h"

Barra bars[BARS];

// Drawing
void sortBarsVisualizer(SDL_Renderer *renderer, Barra array[], int arrayLength, char *Algorithm);

// Sorting
void shuffleArray(Barra array[], int size);

void printBars(Barra bars[], int size) {
	printf("[ ");
	for (int i = 0; i < size; ++i) {
		printf("%d", bars[i].value);
		if (i != size - 1)
			printf(", ");
	}
	printf("]\n");
}

int main(void) {
	srand(time(NULL));


	SDL_Window *window = SDL_CreateWindow("Sorting Algorithm", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) return 1;
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_TEXTUREACCESS_TARGET);
	if (renderer == NULL) return 1;
	
	// Initialize Array
	const int dw = WIDTH / BARS;
	const int dh = HEIGHT / BARS;
	for (int i = 0; i < BARS; ++i) {
		bars[i].value = i;
		bars[i].rectangle.w = dw;
		bars[i].rectangle.h = (i + 1) * dh;
		bars[i].renderer = renderer;
	}
	
	char algorithms[][15] = { 
		"Quick Sort", 
		"Selection Sort",
		"Bubble Sort",
		"Heap Sort",
		"Cocktail Sort",
		"Odd Even Sort",
		"Comb Sort"
	};

	for (long unsigned int i = 0; i < sizeof(algorithms) / sizeof(algorithms[0]); ++i) {
		shuffleArray(bars, BARS);
		/* printBars(bars, BARS); */

		printf("Algorithm: %s\n", algorithms[i]);
		sortBarsVisualizer(renderer, bars, BARS, algorithms[i]);
		/* printBars(bars, BARS); */
	}

	SDL_Delay(1000);

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
