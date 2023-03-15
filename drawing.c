#include <SDL2/SDL.h>
#include <SDL2/SDL_rect.h>
#include "dimensions.h"
#include "definitions.h"

#define DELAY 5

void clearScreen(SDL_Renderer *renderer) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
}

void drawBar(SDL_Renderer *renderer, Barra bar, int x, int y, Uint8 colorRed, Uint8 colorGreen, Uint8 colorBlue) {
	SDL_SetRenderDrawColor(renderer, colorRed, colorGreen, colorBlue, SDL_ALPHA_OPAQUE);

	SDL_Rect rectangle;
	rectangle.w = bar.width;
	rectangle.h = bar.height;
	rectangle.x = x;
	rectangle.y = y;

	SDL_RenderFillRect(renderer, &rectangle);
}

void drawBars(SDL_Renderer *renderer, Barra bars[], int barsLength, int swapIndex1, int swapIndex2) {
	clearScreen(renderer);

	SDL_Rect rectangle;
	for (int i = 0; i < barsLength; ++i) {
		if (i == swapIndex1 || i == swapIndex2)
			SDL_SetRenderDrawColor(renderer, 28, 219, 61, SDL_ALPHA_OPAQUE);
		else
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

		rectangle.w = bars[i].width;
		rectangle.h = bars[i].height;
		rectangle.x = i * bars[i].width;
		rectangle.y = HEIGHT - rectangle.h;

		SDL_RenderFillRect(renderer, &rectangle);
	}

	// Update
	SDL_RenderPresent(renderer);
}

void drawSortedBars(SDL_Renderer *renderer, Barra bars[], int barsLength) {
	clearScreen(renderer);

	for (int i = 0; i < barsLength; ++i) drawBar(
			renderer, 
			bars[i],
			i * bars[i].width,
			HEIGHT - bars[i].height,
			0,
			255,
			0
			);
	
	SDL_RenderPresent(renderer);
}

void sortBarsVisualizer(SDL_Renderer *renderer, Barra bars[], int barsLength) {
	// Clear screen
	clearScreen(renderer);

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	drawBars(renderer, bars, barsLength, -1, -1);

	int swaps;
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

	drawSortedBars(renderer, bars, barsLength);
}
