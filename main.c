#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <time.h>
#include "dimensions.h"
#include "definitions.h"

Barra bars[BARS];

// Drawing
void sortBarsVisualizer(SDL_Renderer *renderer, Barra array[], int arrayLength);

// Sorting
void shuffleArray(Barra array[], int size);

void printBars(Barra bars[], int size) {
	for (int i = 0; i < size; ++i)
		printf("value: %d\n", bars[i].value);
	
	printf("\n");
}

int main(void) {
	srand(time(NULL));
	
	// Initialize Array
	const int dw = WIDTH / BARS;
	const int dh = HEIGHT / BARS;
	for (int i = 0; i < BARS; ++i) {
		bars[i].value = i;
		bars[i].width = dw;
		bars[i].height = (i + 1) * dh;
	}
	
	shuffleArray(bars, BARS);
	printBars(bars, BARS);


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
