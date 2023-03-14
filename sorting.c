#include "dimensions.h"
#include <stddef.h>
#include <stdlib.h>

typedef unsigned int u32 ;

void shuffleArray(u32 array[], int size) {
	if (size > 1) {
		size_t i;
		size_t arrayLength = size;
		for (i = 0; i < arrayLength - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			u32 t = array[j];
			array[j] = array[i];
			array[i] = t;
		}
	}
}; 
