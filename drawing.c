#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <string.h>
#include "dimensions.h"
#include "colors.h"
#include "sorting.h"

// Definitions
#define DELAY 5

// Import variables
/* extern SDL_Window *window; */
/* extern SDL_Renderer *renderer; */

void clearScreen(SDL_Renderer *canvas) {
	// Clear screen
	SDL_SetRenderDrawColor(canvas, BACKGROUND_R, BACKGROUND_G, BACKGROUND_B, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(canvas);
}

void drawBars(SDL_Renderer *canvas, int array[], int arrayLength, Uint8 defaultColorR, Uint8 defaultColorG, Uint8 defaultColorB, int highlightedPositions[], int numberOfHighlighted, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB) {
	clearScreen(canvas);

	const int deltaWidth = WIDTH / arrayLength;
	const int deltaHeight = HEIGHT / arrayLength;
	SDL_Rect rectangle;
	rectangle.w = deltaWidth;

	for (int i = 0; i < arrayLength; ++i) {
		int highlited = 0;

		if (numberOfHighlighted > 0)
			for (int j = 0; j < numberOfHighlighted; ++j) 
				if (i == highlightedPositions[j]) {
					highlited = 1;
					break;
				}
			
		if (highlited)
			SDL_SetRenderDrawColor(canvas, highlightColorR, highlightColorG, highlightColorB, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(canvas, defaultColorR, defaultColorG, defaultColorB, SDL_ALPHA_OPAQUE);

		rectangle.h = array[i] * deltaHeight;
		rectangle.x = i * deltaWidth;
		rectangle.y = HEIGHT - rectangle.h;

		SDL_RenderFillRect(canvas, &rectangle);
	}

	// Update
	SDL_RenderPresent(canvas);
}

void sortVisualizer(SDL_Renderer *canvas, int array[], int arrayLength, char *Visualizer, char *Algorithm) {
	clearScreen(canvas);

	int h[1];
	drawBars(canvas, array, arrayLength,
			BAR_R, BAR_G, BAR_B,
			h, 0,
			HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);


	// Sort
	if (!strcmp(Algorithm, "None") && !strcmp(Visualizer, "Bars")) {
		int swaps;
		do {
			swaps = 0;
			for (int i = 0; i < arrayLength - 1; ++i) {
				if (array[i + 1] >= array[i]) continue;
				SDL_Delay(DELAY);

				// Swap
				++swaps;
				int temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				int highlighting[] = { i , i + 1 };
				drawBars(canvas, array, arrayLength,
						BAR_R, BAR_G, BAR_B,
						highlighting, 2,
						HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			}
		} while (swaps != 0);
	}

	if (!strcmp(Algorithm, "Quick Sort") && !strcmp(Visualizer, "Bars")) 
		quickSort(array, 0, arrayLength - 1, arrayLength);

	if (!strcmp(Algorithm, "Selection Sort") && !strcmp(Visualizer, "Bars")) 
		selectionSort(array, arrayLength);

	if (!strcmp(Algorithm, "Bubble Sort") && !strcmp(Visualizer, "Bars")) 
		bubbleSort(array, arrayLength);

	if (!strcmp(Algorithm, "Insertion Sort") && !strcmp(Visualizer, "Bars")) 
		insertionSort(array, arrayLength);

	if (!strcmp(Algorithm, "Heap Sort") && !strcmp(Visualizer, "Bars")) 
		heapSort(array, arrayLength);

	if (!strcmp(Algorithm, "Radix Sort") && !strcmp(Visualizer, "Bars")) 
		radixSort(array, arrayLength);

	if (!strcmp(Algorithm, "Shell Sort") && !strcmp(Visualizer, "Bars")) 
		shellSort(array, arrayLength);

	if (!strcmp(Algorithm, "Comb Sort") && !strcmp(Visualizer, "Bars")) 
		combSort(array, arrayLength);

	if (!strcmp(Algorithm, "Cocktail Sort") && !strcmp(Visualizer, "Bars")) 
		CocktailSort(array, arrayLength);

	if (!strcmp(Algorithm, "Cycle Sort") && !strcmp(Visualizer, "Bars")) 
		cycleSort(array, arrayLength);

	if (!strcmp(Algorithm, "Odd-Even Sort") && !strcmp(Visualizer, "Bars")) 
		oddEvenSort(array, arrayLength);

	if (!strcmp(Algorithm, "Gnome Sort") && !strcmp(Visualizer, "Bars")) 
		gnomeSort(array, arrayLength);

	if (!strcmp(Algorithm, "Shell Sort") && !strcmp(Visualizer, "Bars")) 
		shellSort(array, arrayLength);
	
	
	// Draw sorted bars
	drawBars(canvas, array, arrayLength,
			BAR_R, BAR_G, BAR_B,
			h, 0,
			HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
}
