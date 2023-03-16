#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include "definitions.h"
#include "colors.h"

// Definitions
int array[NUMBER_OF_ELEMENTS];
extern SDL_Renderer *renderer;
void drawBars(SDL_Renderer *canvas, int array[], int arrayLength, Uint8 defaultColorR, Uint8 defaultColorG, Uint8 defaultColorB, int highlightedPositions[], int numberOfHighlighted, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB);

void swap(int array[], int index1, int index2) {
	int t = array[index1];
	array[index1] = array[index2];
	array[index2] = t;
}

void shuffleArray(int array[], int arrayLength) {
	if (arrayLength > 1) {
		for (int i = 0; i < arrayLength - 1; i++) {
			int j = i + rand() / (RAND_MAX / (arrayLength - i) + 1);
			swap(array, i, j);

			/* int highlighting[] = { i , j }; */
			/* drawBars(renderer, array, arrayLength, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B); */
			/* SDL_Delay(50); */
		}
	}
}; 

void initializeArray(int array[], int arrayLength, int minimum, int maximum) {
	for (int i = 0; i < arrayLength ; ++i) 
		array[i] = minimum + i * (maximum - minimum) / arrayLength;
}


/* ################### */
/* Quick Sorting START */
/* ################### */

int partition(int arr[], int low, int high) {
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates
				// the right position of pivot found so far

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			i++; // increment index of smaller element
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, high);
	return (i + 1);
}
