#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 1634
#define HEIGHT 944
#define BARS 30

typedef unsigned int u32 ;

u32 bars[BARS];

void printBars(u32 bars[], int size) {
	for (int i = 0; i < size; ++i) {
		printf("%d", bars[i]);
		if (i != size - 1) printf(", ");
	}
	printf("\n");
}

void randomizeBars(u32 bars[], int size) {
	for (int i = 0; i < size; ++i) {
		u32 height = (i + 1) * HEIGHT / size;
		bars[i] = height;
	}
	if (size > 1) {
		size_t i;
		for (i = 0; i < size - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			u32 t = bars[j];
			bars[j] = bars[i];
			bars[i] = t;
		}
	}
}; 

void drawBars(SDL_Renderer *renderer, u32 bars[], int barsLength) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	SDL_Rect rectangle;
	rectangle.w = WIDTH / barsLength;

	for (int i = 0; i < barsLength; ++i) {
		rectangle.x = i * rectangle.w;
		rectangle.y = HEIGHT - bars[i];
		rectangle.h = bars[i];
		SDL_RenderFillRect(renderer, &rectangle);
	}

	// Update
	SDL_RenderPresent(renderer);
}

void sortBarsVisualizer(SDL_Renderer *renderer, u32 bars[], int barsLength) {
	// Clear screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

	drawBars(renderer, bars, barsLength);

	int swaps;
	do {
		swaps = 0;
		for (int i = 0; i < barsLength - 1; ++i) {
			SDL_Delay(50);
			if (bars[i + 1] >= bars[i]) continue;

			// Swap
			++swaps;
			u32 temp = bars[i];
			bars[i] = bars[i + 1];
			bars[i + 1] = temp;
			drawBars(renderer, bars, barsLength);

		}
	} while (swaps != 0);
}

int main(void) {
	srand(time(NULL));

	SDL_Window *window = SDL_CreateWindow("Sorting Algorithm", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = NULL;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_CreateWindowAndRenderer(WIDTH, HEIGHT, SDL_WINDOW_SHOWN, &window, &renderer);

	randomizeBars(bars, BARS);

	sortBarsVisualizer(renderer, bars, BARS);

	printBars(bars, BARS);

	SDL_DestroyWindow(window);
	SDL_Quit();


	return 0;
}
