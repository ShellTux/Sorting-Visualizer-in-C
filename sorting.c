#include "dimensions.h"
#include "definitions.h"
#include <stddef.h>
#include <stdlib.h>

void shuffleArray(Barra array[], int size) {
	if (size > 1) {
		size_t i;
		size_t arrayLength = size;
		for (i = 0; i < arrayLength - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			Barra t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}; 
