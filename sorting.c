#include <SDL2/SDL_timer.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>
#include "definitions.h"
#include "colors.h"

// Definitions
int array[NUMBER_OF_ELEMENTS];
extern SDL_Renderer *renderer;
void drawBars(SDL_Renderer *canvas, int array[], int arrayLength, Uint8 defaultColorR, Uint8 defaultColorG, Uint8 defaultColorB, int highlightedPositions[], int numberOfHighlighted, Uint8 highlightColorR, Uint8 highlightColorG, Uint8 highlightColorB);

/* void swap(int array[], int index1, int index2) { */
/* 	int t = array[index1]; */
/* 	array[index1] = array[index2]; */
/* 	array[index2] = t; */
/* } */

void swap(int *value1, int *value2) {
	int t = *value1;
	*value1 = *value2;
	*value2 = t;
}

void shuffleArray(int array[], int arrayLength) {
	if (arrayLength > 1) {
		for (int i = 0; i < arrayLength - 1; i++) {
			int j = i + rand() / (RAND_MAX / (arrayLength - i) + 1);
			swap(&array[i], &array[j]);

			int highlighting[] = { i , j };
			drawBars(renderer, array, arrayLength, BAR_R, BAR_G, BAR_B, highlighting, 2, SHUFFLE_R, SHUFFLE_G, SHUFFLE_B);
			SDL_Delay(SHUFFLE_DELAY);
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

int partition(int arr[], int low, int high, int length) {
	int pivot = arr[high]; // pivot
	int i = (low - 1); // Index of smaller element and indicates
				// the right position of pivot found so far

	int highlighting[2];
	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j] < pivot) {
			i++; // increment index of smaller element
			swap(&arr[i], &arr[j]);
			highlighting[0] = i;
			highlighting[1] = j;
			drawBars(renderer, arr, length, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			SDL_Delay(SHUFFLE_DELAY);
		}
	}
	highlighting[0] = i + 1;
	highlighting[1] = high;
	swap(&arr[i + 1], &arr[high]);
	drawBars(renderer, arr, length, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
	SDL_Delay(SHUFFLE_DELAY);
	return (i + 1);
}

void quickSort(int arr[], int low, int high, int length) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high, length);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1, length);
		quickSort(arr, pi + 1, high, length);
	}
}

/* ################# */
/* Quick Sorting END */
/* ################# */


/* ####################### */
/* Selection Sorting START */
/* ####################### */

void selectionSort(int arr[], int n) {
	int i, j, min_idx, highlighting[2];

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		if (min_idx != i) {
			swap(&arr[min_idx], &arr[i]);
			highlighting[0] = min_idx;
			highlighting[1] = i;
			drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			SDL_Delay(SHUFFLE_DELAY);
		}
	}
}

/* ##################### */
/* Selection Sorting END */
/* ##################### */


/* #################### */
/* Bubble Sorting START */
/* #################### */

// A function to implement bubble sort
void bubbleSort(int arr[], int n) {
	int i, j, highlighting[2];
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1]) {
				swap(&arr[j], &arr[j + 1]);
				highlighting[0] = j;
				highlighting[1] = j + 1;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
}

/* ################## */
/* Bubble Sorting END */
/* ################## */


/* #################### */
/* Insertion Sorting START */
/* #################### */

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n) {
	int i, key, j, highlighting[2];
	for (i = 1; i < n; i++) {
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		   greater than key, to one position ahead
		   of their current position */
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];

			highlighting[0] = j;
			highlighting[1] = j + 1;
			drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			SDL_Delay(SHUFFLE_DELAY);

			j = j - 1;
		}
		arr[j + 1] = key;
	}
}

/* ################## */
/* Insertion Sorting END */
/* ################## */


/* #################### */
/* Merge Sorting START */
/* #################### */

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(int arr[], int l, int m, int r) {
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	int L[n1], R[n2];

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray
	j = 0; // Initial index of second subarray
	k = l; // Initial index of merged subarray
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	are any */
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	are any */
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r) {
	if (l < r) {
		// Same as (l+r)/2, but avoids overflow for
		// large l and h
		int m = l + (r - l) / 2;

		// Sort first and second halves
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}

/* ################## */
/* Merge Sorting END */
/* ################## */


/* #################### */
/* Heap Sorting START */
/* #################### */

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(int arr[], int N, int i) {
	// Find largest among root, left child and right child

	// Initialize largest as root
	int largest = i;

	// left = 2*i + 1
	int left = 2 * i + 1;

	// right = 2*i + 2
	int right = 2 * i + 2;

	int highlighting[2];

	// If left child is larger than root
	if (left < N && arr[left] > arr[largest])

		largest = left;

	// If right child is larger than largest
	// so far
	if (right < N && arr[right] > arr[largest])

		largest = right;

	// Swap and continue heapifying if root is not largest
	// If largest is not root
	if (largest != i) {

		swap(&arr[i], &arr[largest]);
		highlighting[0] = i;
		highlighting[1] = largest;
		drawBars(renderer, arr, N, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
		SDL_Delay(SHUFFLE_DELAY);

		// Recursively heapify the affected
		// sub-tree
		heapify(arr, N, largest);
	}
}

// Main function to do heap sort
void heapSort(int arr[], int N) {
	int highlighting[2];

	// Build max heap
	for (int i = N / 2 - 1; i >= 0; i--)

		heapify(arr, N, i);

	// Heap sort
	for (int i = N - 1; i >= 0; i--) {

		swap(&arr[0], &arr[i]);
		highlighting[0] = 0;
		highlighting[1] = i;
		drawBars(renderer, arr, N, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
		SDL_Delay(SHUFFLE_DELAY);

		// Heapify root element to get highest element at
		// root again
		heapify(arr, i, 0);
	}
}

/* ################## */
/* Heap Sorting END */
/* ################## */


/* ################## */
/* Counting Sorting START */
/* ################## */

/*#define RANGE 255 */

/*// The main function that sort the given string arr[] in */
/*// alphabetical order */
/*void countSort(char arr[]) { */
/*	// The output character array that will have sorted arr */
/*	char output[strlen(arr)]; */

/*	// Create a count array to store count of individual */
/*	// characters and initialize count array as 0 */
/*	int count[RANGE + 1], i; */
/*	memset(count, 0, sizeof(count)); */

/*	// Store count of each character */
/*	for (i = 0; arr[i]; ++i) */
/*		++count[arr[i]]; */

/*	// Change count[i] so that count[i] now contains actual */
/*	// position of this character in output array */
/*	for (i = 1; i <= RANGE; ++i) */
/*		count[i] += count[i - 1]; */

/*	// Build the output character array */
/*	for (i = 0; arr[i]; ++i) { */
/*		output[count[arr[i]] - 1] = arr[i]; */
/*		--count[arr[i]]; */
/*	} */

/*	/1* */
/*	For Stable algorithm */
/*	for (i = sizeof(arr)-1; i>=0; --i) */
/*	{ */
/*		output[count[arr[i]]-1] = arr[i]; */
/*		--count[arr[i]]; */
/*	} */

/*	For Logic : See implementation */

/*	int highlighting[1]; */
/*	// Copy the output array to arr, so that arr now */
/*	// contains sorted characters */
/*	for (i = 0; arr[i]; ++i) { */
/*		arr[i] = output[i]; */
/*		highlighting[0] = i; */
/*		drawBars(renderer, arr, int arrayLength, BAR_R, BAR_G, BAR_B, highlighting, 1, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B); */
/*	} */
/*} */

/* ################## */
/* Counting Sorting END */
/* ################## */


/* ################## */
/* Radix Sorting START */
/* ################## */

// A utility function to get maximum value in arr[]
int getMax(int arr[], int n) {
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}

// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSort(int arr[], int n, int exp) {
	int output[n]; // output array
	int i, count[10] = { 0 };

	// Store count of occurrences in count[]
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Change count[i] so that count[i] now contains actual
	// position of this digit in output[]
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	int highlighting[1];
	// Copy the output array to arr[], so that arr[] now
	// contains sorted numbers according to current digit
	for (i = 0; i < n; i++) {
		arr[i] = output[i];
		highlighting[0] = i;
		drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 1, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
		SDL_Delay(SHUFFLE_DELAY);
	}
}

// The main function to that sorts arr[] of size n using
// Radix Sort
void radixSort(int arr[], int n) {
	// Find the maximum number to know number of digits
	int m = getMax(arr, n);

	// Do counting sort for every digit. Note that instead
	// of passing digit number, exp is passed. exp is 10^i
	// where i is current digit number
	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}


/* ################## */
/* Radix Sorting END */
/* ################## */


/* ################## */
/* Bucket Sorting START */
/* ################## */


/* ################## */
/* Bucket Sorting END */
/* ################## */


/* ################## */
/* Shell Sorting START */
/* ################## */

/* function to sort arr using shellSort */
void shellSort(int arr[], int n) {
	// Start with a big gap, then reduce the gap
	int highlighting[2];
	for (int gap = n/2; gap > 0; gap /= 2) {
		// Do a gapped insertion sort for this gap size.
		// The first gap elements a[0..gap-1] are already in gapped order
		// keep adding one more element until the entire array is
		// gap sorted
		for (int i = gap; i < n; i += 1) {
			// add a[i] to the elements that have been gap sorted
			// save a[i] in temp and make a hole at position i
			int temp = arr[i];
			highlighting[0] = i;

			// shift earlier gap-sorted elements up until the correct
			// location for a[i] is found
			int j;			
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			
			// put temp (the original a[i]) in its correct location
			arr[j] = temp;

			highlighting[1] = j;
			drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
		}
	}
}

/* ################## */
/* Shell Sorting END */
/* ################## */


/* ################## */
/* Comb Sorting START */
/* ################## */

// To find gap between elements
int getNextGap(int gap) {
	// Shrink gap by Shrink factor
	gap = (gap*10)/13;

	if (gap < 1)
		return 1;
	return gap;
}

// Function to sort a[0..n-1] using Comb Sort
void combSort(int arr[], int n) {
	int highlighting[2];

	// Initialize gap
	int gap = n;

	// Initialize swapped as true to make sure that
	// loop runs
	int swapped = 1;

	// Keep running while gap is more than 1 and last
	// iteration caused a swap
	while (gap != 1 || swapped == 1) {
		// Find next gap
		gap = getNextGap(gap);

		// Initialize swapped as false so that we can
		// check if swap happened or not
		swapped = 0;

		// Compare all elements with current gap
		for (int i = 0; i < n - gap; i++) {
			if (arr[i] > arr[i + gap]) {
				swap(&arr[i], &arr[i+gap]);
				swapped = 1;

				highlighting[0] = i;
				highlighting[1] = i + gap;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}
	}
}

/* ################## */
/* Comb Sorting END */
/* ################## */


/* ################## */
/* Cocktail Sorting START */
/* ################## */

// Sorts array a[0..n-1] using Cocktail sort
void CocktailSort(int arr[], int n) {
	int highlighting[2];
	int swapped = 1;
	int start = 0;
	int end = n - 1;

	while (swapped) {
		// reset the swapped flag on entering
		// the loop, because it might be 1 from
		// a previous iteration.
		swapped = 0;

		// loop from left to right same as
		// the bubble sort
		for (int i = start; i < end; ++i) {
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swapped = 1;

				highlighting[0] = i;
				highlighting[1] = i + 1;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}

		// if nothing moved, then array is sorted.
		if (!swapped) break;

		// otherwise, reset the swapped flag so that it
		// can be used in the next stage
		swapped = 0;

		// move the end point back by one, because
		// item at the end is in its rightful spot
		--end;

		// from right to left, doing the
		// same comparison as in the previous stage
		for (int i = end - 1; i >= start; --i) {
			if (arr[i] > arr[i + 1]) {
				swap(&arr[i], &arr[i + 1]);
				swapped = 1;

				highlighting[0] = i;
				highlighting[1] = i + 1;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}

		// increase the starting point, because
		// the last stage would have moved the next
		// smallest number to its rightful spot.
		++start;
	}
}

/* ################## */
/* Cocktail Sorting END */
/* ################## */


/* ################## */
/* Cycle Sorting END */
/* ################## */

// Function sort the array using Cycle sort
void cycleSort(int arr[], int n) {
	int highlighting[1];

	// count number of memory writes
	int writes = 0;

	// traverse array elements and put it to on
	// the right place
	for (int cycle_start = 0; cycle_start <= n - 2; cycle_start++) {
		// initialize item as starting point
		int item = arr[cycle_start];

		// Find position where we put the item. We basically
		// count all smaller elements on right side of item.
		int pos = cycle_start;
		for (int i = cycle_start + 1; i < n; i++)
			if (arr[i] < item)
				pos++;

		// If item is already in correct position
		if (pos == cycle_start)
			continue;

		// ignore all duplicate elements
		while (item == arr[pos])
			pos += 1;

		// put the item to it's right position
		if (pos != cycle_start) {
			swap(&item, &arr[pos]);
			writes++;

			highlighting[0] = pos;
			drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 1, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			SDL_Delay(SHUFFLE_DELAY);
		}

		// Rotate rest of the cycle
		while (pos != cycle_start) {
			pos = cycle_start;

			// Find position where we put the element
			for (int i = cycle_start + 1; i < n; i++)
				if (arr[i] < item)
					pos += 1;

			// ignore all duplicate elements
			while (item == arr[pos])
				pos += 1;

			// put the item to it's right position
			if (item != arr[pos]) {
				swap(&item, &arr[pos]);
				writes++;

				highlighting[0] = pos;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 1, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}
	}

	// Number of memory writes or swaps
	// cout << writes << endl ;
}

/* ################## */
/* Cycle Sorting END */
/* ################## */


/* ################## */
/* Odd-Even Sorting END */
/* ################## */

// A function to sort the algorithm using Odd Even sort
void oddEvenSort(int arr[], int n) {
	int highlighting[2];

	int isSorted = 0; // Initially array is unsorted

	while (!isSorted) {
		isSorted = 1;

		// Perform Bubble sort on odd indexed element
		for (int i=1; i<=n-2; i=i+2) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				isSorted = 0;

				highlighting[0] = i;
				highlighting[1] = i + 1;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}

		// Perform Bubble sort on even indexed element
		for (int i=0; i<=n-2; i=i+2) {
			if (arr[i] > arr[i+1]) {
				swap(&arr[i], &arr[i+1]);
				isSorted = 0;

				highlighting[0] = i;
				highlighting[1] = i + 1;
				drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
				SDL_Delay(SHUFFLE_DELAY);
			}
		}
	}

	return;
}

/* ################## */
/* Odd-Even Sorting END */
/* ################## */


/* ################## */
/* Gnome Sorting START */
/* ################## */

// A function to sort the algorithm using gnome sort
void gnomeSort(int arr[], int n) {
	int highlighting[2];

	int index = 0;

	while (index < n) {
		if (index == 0)
			index++;
		if (arr[index] >= arr[index - 1])
			index++;
		else {
			swap(&arr[index], &arr[index - 1]);
			index--;

			highlighting[0] = index;
			highlighting[1] = index - 1;
			drawBars(renderer, arr, n, BAR_R, BAR_G, BAR_B, highlighting, 2, HIGHLIGHT_R, HIGHLIGHT_G, HIGHLIGHT_B);
			SDL_Delay(SHUFFLE_DELAY);
		}
	}
	return;
}

/* ################## */
/* Gnome Sorting END */
/* ################## */

