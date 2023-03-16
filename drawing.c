#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include <string.h>
#include "dimensions.h"
#include "definitions.h"

#define DELAY 5
const int dw = WIDTH / BARS;
const int dh = HEIGHT / BARS;
void quickSort(Barra arr[], int low, int high);
void selectionSort(Barra arr[], int size);
void bubbleSort(Barra arr[], int size);
void heapSort(Barra arr[], int size);
void CocktailSort(Barra arr[], int size);
void oddEvenSort(Barra arr[], int size);
void combSort(Barra arr[], int size);

void clearScreen(SDL_Renderer *renderer) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void drawBar(SDL_Renderer *renderer, Barra bar, int position, Uint8 colorRed, Uint8 colorGreen, Uint8 colorBlue) {
	SDL_SetRenderDrawColor(renderer, colorRed, colorGreen, colorBlue, SDL_ALPHA_OPAQUE);

	bar.rectangle.x = position * dw;
	bar.rectangle.y = HEIGHT - position * dh;

	SDL_RenderFillRect(renderer, &bar.rectangle);
}

void drawBars(SDL_Renderer *renderer, Barra bars[], int barsLength, int swapIndex1, int swapIndex2) {
	clearScreen(renderer);

	for (int i = 0; i < barsLength; ++i) {
		if (i == swapIndex1 || i == swapIndex2)
			SDL_SetRenderDrawColor(renderer, 28, 219, 61, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		bars[i].rectangle.x = i * bars[i].rectangle.w;
		bars[i].rectangle.y = HEIGHT - bars[i].rectangle.h;

		SDL_RenderFillRect(renderer, &bars[i].rectangle);
	}

	// Update
	SDL_RenderPresent(renderer);
}

void drawSortedBars(SDL_Renderer *renderer, Barra bars[], int barsLength) {
	clearScreen(renderer);

	for (int i = 0; i < barsLength; ++i) drawBar(
			renderer, 
			bars[i],
			i,
			0,
			255,
			0
			);
	
	SDL_RenderPresent(renderer);
}

void sortBarsVisualizer(SDL_Renderer *renderer, Barra bars[], int barsLength, char *Algorithm) {
	// Clear screen
	clearScreen(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	drawBars(renderer, bars, barsLength, -1, -1);

	int swaps;
	if (!strcmp(Algorithm, "None")) {
		do {
			swaps = 0;
			for (int i = 0; i < barsLength - 1; ++i) {
				if (bars[i + 1].value >= bars[i].value) continue;
				SDL_Delay(DELAY);

				// Swap
				++swaps;
				Barra temp = bars[i];
				bars[i] = bars[i + 1];
				bars[i + 1] = temp;
				drawBars(renderer, bars, barsLength, i, i + 1);
			}
		} while (swaps != 0);
	}

	if (!strcmp(Algorithm, "Quick Sort")) 
		quickSort(bars, 0, BARS - 1);

	if (!strcmp(Algorithm, "Selection Sort")) 
		selectionSort(bars, BARS);

	if (!strcmp(Algorithm, "Bubble Sort")) 
		bubbleSort(bars, BARS);

	if (!strcmp(Algorithm, "Heap Sort")) 
		heapSort(bars, BARS);

	if (!strcmp(Algorithm, "Cocktail Sort")) 
		CocktailSort(bars, BARS);

	if (!strcmp(Algorithm, "Odd Even Sort")) 
		oddEvenSort(bars, BARS);

	if (!strcmp(Algorithm, "Comb Sort")) 
		combSort(bars, BARS);
	

	drawSortedBars(renderer, bars, barsLength);
}
