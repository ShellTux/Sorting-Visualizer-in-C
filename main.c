#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include <string.h>
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
extern char *visualizer;
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
	
	char visualizerTypes[][15] = {
		"Bars",
		"Colored Circle"
	};

	char algorithms[][20] = { 
		"Quick Sort", 
		"Selection Sort",
		"Bubble Sort",
		"Heap Sort",
		"Radix Sort",
		"Shell Sort",
		"Comb Sort",
		"Cocktail Sort",
		"Cycle Sort",
		"Odd-Even Sort",
		"Gnome Sort"
	};

	for (long unsigned int visualizerTypeIndex = 0; visualizerTypeIndex < sizeof(visualizerTypes) / sizeof(visualizerTypes[0]) ; ++visualizerTypeIndex) 
		for (long unsigned int algorithmIndex = 0; algorithmIndex < sizeof(algorithms) / sizeof(algorithms[0]); ++algorithmIndex) {
			char title[100] = "";
			strcat(title, algorithms[algorithmIndex]);
			strcat(title, " | ");
			strcat(title, visualizerTypes[visualizerTypeIndex]);

			printf("Algorithm: %s\n", algorithms[algorithmIndex]);
			visualizer = visualizerTypes[visualizerTypeIndex];

			
			// Shuffle
			SDL_SetWindowTitle(window, "Shuffling Array...");
			shuffleArray(array, NUMBER_OF_ELEMENTS);
			printf("Shuffled Array: ");
			printArray(array, NUMBER_OF_ELEMENTS);


			// Sort
			SDL_SetWindowTitle(window, title);
			sortVisualizer(renderer, array, NUMBER_OF_ELEMENTS, visualizerTypes[visualizerTypeIndex], algorithms[algorithmIndex]);
			printf("Sorted Array: ");
			printArray(array, NUMBER_OF_ELEMENTS);

			printf("\n");
		}


	// Clean up
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
