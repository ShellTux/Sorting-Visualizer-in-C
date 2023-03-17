#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include "definitions.h"
#include "dimensions.h"
#include "sorting.h"
#include "drawing.h"

// Definitions
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
extern int array[NUMBER_OF_ELEMENTS];
void drawBars(SDL_Renderer *canvas, int array[], int arrayLength, Uint8 defaultColorR, Uint8 defaultColorG, Uint8 defaultColorB, int highlightedPositions[], int numberOfHighlighted, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB);

void printArray(int array[], int arrayLength) {
	printf("[ ");
	for (int i = 0; i < arrayLength; ++i) {
		printf("%d", array[i]);
		if (i != arrayLength - 1) printf(", ");
	}
	printf("]\n");
}

int main(void) {
	srand(time(NULL));


	window = SDL_CreateWindow("Sorting Algorithm", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL) return 1;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_TEXTUREACCESS_TARGET);
	if (renderer == NULL) return 1;
	
	// Initialize Array it should be normalized if
	// in the future we intend to use other sorting visualizers
	initializeArray(array, NUMBER_OF_ELEMENTS, 0, NUMBER_OF_ELEMENTS);
	
	char visualizerTypes[][5] = {
		"Bars"
	};

	char algorithms[][15] = { 
		"None",
		"Quick Sort", 
		"Selection Sort",
		"Bubble Sort",
		"Heap Sort",
		"Cocktail Sort",
		"Odd Even Sort",
		"Comb Sort"
	};

	for (long unsigned int visualizerTypeIndex = 0; visualizerTypeIndex < sizeof(visualizerTypes) / sizeof(visualizerTypes[0]) ; ++visualizerTypeIndex) 
		for (long unsigned int algorithmIndex = 0; algorithmIndex < sizeof(algorithms) / sizeof(algorithms[0]); ++algorithmIndex) {
			printf("Algorithm: %s\n", algorithms[algorithmIndex]);

			
			// Shuffle
			shuffleArray(array, NUMBER_OF_ELEMENTS);
			printf("Shuffled Array: ");
			printArray(array, NUMBER_OF_ELEMENTS);


			// Sort
			sortVisualizer(renderer, array, NUMBER_OF_ELEMENTS, visualizerTypes[visualizerTypeIndex], algorithms[algorithmIndex]);
			printf("Sorted Array: ");
			printArray(array, NUMBER_OF_ELEMENTS);

			printf("\n");
		}


	/* SDL_Delay(1000); */

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
