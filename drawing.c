#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
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

void drawBars(SDL_Renderer *canvas, int array[], int previousArray[], int arrayLength, Uint8 barColorR, Uint8 barColorG, Uint8 barColorB, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB) {
	clearScreen(canvas);

	const int deltaWidth = WIDTH / arrayLength;
	const int deltaHeight = HEIGHT / arrayLength;
	SDL_Rect rectangle;
	rectangle.w = deltaWidth;

	for (int i = 0; i < arrayLength; ++i) {
			
		if (array[i] != previousArray[i]) {
			previousArray[i] = array[i];
			SDL_SetRenderDrawColor(canvas, highlightColorR, highlightColorG, highlightColorB, SDL_ALPHA_OPAQUE);
		} else 
			SDL_SetRenderDrawColor(canvas, barColorR, barColorG, barColorB, SDL_ALPHA_OPAQUE);


		rectangle.h = array[i] * deltaHeight;
		rectangle.x = i * deltaWidth;
		rectangle.y = HEIGHT - rectangle.h;

		SDL_RenderFillRect(canvas, &rectangle);
	}

	// Update
	SDL_RenderPresent(canvas);
};

void drawSortedBars(SDL_Renderer *canvas, int array[], int arrayLength, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB) {
	clearScreen(canvas);
	SDL_RenderFlush(canvas);
	SDL_RenderClear(canvas);

	const int deltaWidth = WIDTH / arrayLength;
	const int deltaHeight = HEIGHT / arrayLength;
	SDL_Rect rectangle;
	rectangle.w = deltaWidth;

	for (int i = 0; i < arrayLength; ++i) {
			
		SDL_SetRenderDrawColor(canvas, highlightColorR, highlightColorG, highlightColorB, SDL_ALPHA_OPAQUE);

		rectangle.h = array[i] * deltaHeight;
		rectangle.x = i * deltaWidth;
		rectangle.y = HEIGHT - rectangle.h;

		SDL_RenderFillRect(canvas, &rectangle);

		// Update
		SDL_RenderPresent(canvas);

		SDL_Delay(10);
	}
};

void sortVisualizer(SDL_Window *window, SDL_Renderer *canvas, int array[], int arrayLength, char *Visualizer, char *Algorithm) {
	SDL_SetWindowTitle(window, Algorithm);

	clearScreen(canvas);

	drawBars(canvas, array, array, arrayLength,
			BAR_R, BAR_G, BAR_B,
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
				drawBars(canvas, array, array, arrayLength,
						BAR_R, BAR_G, BAR_B,
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
	/* drawSortedBars(canvas, array, arrayLength, 0, 255, 0); */
}
