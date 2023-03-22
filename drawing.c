#include <math.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <string.h>
#include "colors.h"
#include "definitions.h"
#include "dimensions.h"
#include "sorting.h"

// Definitions
#define DELAY 5

// Import variables

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

int maximum(int array[], int length) {
	int maximum = array[0];
	for (int i = 1; i < length; ++i) 
		if (array[i] > maximum)
			maximum = array[i];
	
	return maximum;
}

void hsl2rgb(double hue, double saturation, double lightness, int *red, int *green, int *blue) {
    double chroma = (1 - fabs(2 * lightness - 1)) * saturation;
    double hue_region = hue * 6;
    double second_largest_component = chroma * (1 - fabs(fmod(hue_region, 2) - 1));
    double r, g, b;
    
    if (hue_region < 1) {
        r = chroma;
        g = second_largest_component;
        b = 0;
    } else if (hue_region < 2) {
        r = second_largest_component;
        g = chroma;
        b = 0;
    } else if (hue_region < 3) {
        r = 0;
        g = chroma;
        b = second_largest_component;
    } else if (hue_region < 4) {
        r = 0;
        g = second_largest_component;
        b = chroma;
    } else if (hue_region < 5) {
        r = second_largest_component;
        g = 0;
        b = chroma;
    } else {
        r = chroma;
        g = 0;
        b = second_largest_component;
    }
    
    double lightness_offset = lightness - chroma / 2;
    *red = (int) round((r + lightness_offset) * 255);
    *green = (int) round((g + lightness_offset) * 255);
    *blue = (int) round((b + lightness_offset) * 255);
}


void drawCircle(SDL_Renderer *canvas, int array[], int arrayLength) {
	clearScreen(canvas);

	const int centerX = WIDTH / 2;
	const int centerY = HEIGHT / 2;
	const int radius = (WIDTH > HEIGHT ? HEIGHT : WIDTH) / 2;
	const int max = maximum(array, arrayLength);
	for (int i = 0; i < arrayLength; ++i) {
		const double deltaAngle = 2 * PI / arrayLength;
		const double angle = i * deltaAngle;
		const double ratio = (double) array[i] / max;
		int red = 255, green = 255, blue = 255;
		hsl2rgb(ratio, 0.5, 0.5, &red, &green, &blue);

		SDL_Vertex triangle[3] = {
			{
				{ centerX, centerY },
				{ red, green, blue, 0xFF },
				{ 0.f, 0.f }
			},
			{
				{ centerX + radius * cos(angle), centerY + radius * sin(angle) },
				{ red, green, blue, 0xFF },
				{ 0.f, 0.f }
			},
			{
				{ centerX + radius * cos(angle + deltaAngle), centerY + radius * sin(angle + deltaAngle) },
				{ red, green, blue, 0xFF },
				{ 0.f, 0.f }
			},
		};

		SDL_RenderGeometry(canvas, NULL, triangle, 3, NULL, 0);
	}

	SDL_RenderPresent(canvas);
}

void sortVisualizer(SDL_Renderer *canvas, int array[], int arrayLength, char *Visualizer, char *Algorithm) {
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

	if (!strcmp(Algorithm, "Quick Sort")) 
		quickSort(array, 0, arrayLength - 1, arrayLength);

	if (!strcmp(Algorithm, "Selection Sort")) 
		selectionSort(array, arrayLength);

	if (!strcmp(Algorithm, "Bubble Sort")) 
		bubbleSort(array, arrayLength);

	if (!strcmp(Algorithm, "Insertion Sort")) 
		insertionSort(array, arrayLength);

	if (!strcmp(Algorithm, "Heap Sort")) 
		heapSort(array, arrayLength);

	if (!strcmp(Algorithm, "Radix Sort")) 
		radixSort(array, arrayLength);

	if (!strcmp(Algorithm, "Shell Sort")) 
		shellSort(array, arrayLength);

	if (!strcmp(Algorithm, "Comb Sort")) 
		combSort(array, arrayLength);

	if (!strcmp(Algorithm, "Cocktail Sort")) 
		CocktailSort(array, arrayLength);

	if (!strcmp(Algorithm, "Cycle Sort")) 
		cycleSort(array, arrayLength);

	if (!strcmp(Algorithm, "Odd-Even Sort")) 
		oddEvenSort(array, arrayLength);

	if (!strcmp(Algorithm, "Gnome Sort")) 
		gnomeSort(array, arrayLength);

	if (!strcmp(Algorithm, "Shell Sort")) 
		shellSort(array, arrayLength);
	
	
	// Draw sorted bars
	/* drawSortedBars(canvas, array, arrayLength, 0, 255, 0); */
}
