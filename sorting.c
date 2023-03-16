#include "dimensions.h"
#include "definitions.h"
#include <SDL2/SDL_timer.h>
#include <stddef.h>
#include <stdlib.h>
#include <SDL2/SDL_render.h>

void drawBars(SDL_Renderer *renderer, Barra bars[], int barsLength, int swapIndex1, int swapIndex2);

void swap(Barra array[], int index1, int index2) {
	drawBars(array[0].renderer, array, BARS, index1, index2);
	Barra t = array[index1];
	array[index1] = array[index2];
	array[index2] = t;

	SDL_Delay(5);
}

void shuffleArray(Barra array[], int size) {
	if (size > 1) {
		size_t i;
		size_t arrayLength = size;
		for (i = 0; i < arrayLength - 1; i++) {
			size_t j = i + rand() / (RAND_MAX / (size - i) + 1);
			swap(array, i, j);
		}
	}
}; 

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */
int partition(Barra arr[], int low, int high) {
	int pivot = arr[high].value; // pivot
	int i = (low - 1); // Index of smaller element and indicates
				// the right position of pivot found so far

	for (int j = low; j <= high - 1; j++) {
		// If current element is smaller than the pivot
		if (arr[j].value < pivot) {
			i++; // increment index of smaller element
			swap(arr, i, j);
		}
	}
	swap(arr, i + 1, high);
	return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */
void quickSort(Barra arr[], int low, int high) {
	if (low < high) {
		/* pi is partitioning index, arr[p] is now
		at right place */
		int pi = partition(arr, low, high);

		// Separately sort elements before
		// partition and after partition
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

void selectionSort(Barra arr[], int size) {
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < size-1; i++) {
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i + 1; j < size; j++)
			if (arr[j].value < arr[min_idx].value)
				min_idx = j;

		// Swap the found minimum element with the first element
		if (min_idx != i)
			swap(arr, min_idx, i);
	}
}

// A function to implement bubble sort
void bubbleSort(Barra arr[], int size) {
	int i, j;
	for (i = 0; i < size - 1; i++)

		// Last i elements are already in place
		for (j = 0; j < size - i - 1; j++)
			if (arr[j].value > arr[j + 1].value)
				swap(arr, j, j + 1);
}

/* Function to sort an array using insertion sort*/
/* void insertionSort(Barra arr[], int size) { */
/* 	int i, key, j; */
/* 	for (i = 1; i < size; i++) { */
/* 		key = arr[i].value; */
/* 		j = i - 1; */

/* 		/1* Move elements of arr[0..i-1], that are */
/* 		greater than key, to one position ahead */
/* 		of their current position *1/ */
/* 		while (j >= 0 && arr[j].value > key) { */
/* 			arr[j + 1] = arr[j]; */
/* 			j = j - 1; */
/* 		} */
/* 		arr[j + 1] = key; */
/* 	} */
/* } */

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
/* void merge(Barra arr[], int l, int m, int r) { */
/* 	int i, j, k; */
/* 	int n1 = m - l + 1; */
/* 	int n2 = r - m; */

/* 	/1* create temp arrays *1/ */
/* 	int L[n1], R[n2]; */

/* 	/1* Copy data to temp arrays L[] and R[] *1/ */
/* 	for (i = 0; i < n1; i++) */
/* 		L[i] = arr[l + i].value; */
/* 	for (j = 0; j < n2; j++) */
/* 		R[j] = arr[m + 1 + j].value; */

	/* Merge the temp arrays back into arr[l..r]*/
/* 	i = 0; // Initial index of first subarray */
/* 	j = 0; // Initial index of second subarray */
/* 	k = l; // Initial index of merged subarray */
/* 	while (i < n1 && j < n2) { */
/* 		if (L[i] <= R[j]) { */
/* 			arr[k] = L[i]; */
/* 			i++; */
/* 		} */
/* 		else { */
/* 			arr[k] = R[j]; */
/* 			j++; */
/* 		} */
/* 		k++; */
/* 	} */

/* 	/1* Copy the remaining elements of L[], if there */
/* 	are any *1/ */
/* 	while (i < n1) { */
/* 		arr[k] = L[i]; */
/* 		i++; */
/* 		k++; */
/* 	} */

/* 	/1* Copy the remaining elements of R[], if there */
/* 	are any *1/ */
/* 	while (j < n2) { */
/* 		arr[k] = R[j]; */
/* 		j++; */
/* 		k++; */
/* 	} */
/* } */

/* /1* l is for left index and r is right index of the */
/* sub-array of arr to be sorted *1/ */
/* void mergeSort(int arr[], int l, int r) */
/* { */
/* 	if (l < r) { */
/* 		// Same as (l+r)/2, but avoids overflow for */
/* 		// large l and h */
/* 		int m = l + (r - l) / 2; */

/* 		// Sort first and second halves */
/* 		mergeSort(arr, l, m); */
/* 		mergeSort(arr, m + 1, r); */

/* 		merge(arr, l, m, r); */
/* 	} */
/* } */

// To heapify a subtree rooted with node i
// which is an index in arr[].
// n is size of heap
void heapify(Barra arr[], int N, int i) {
	// Find largest among root, left child and right child

	// Initialize largest as root
	int largest = i;

	// left = 2*i + 1
	int left = 2 * i + 1;

	// right = 2*i + 2
	int right = 2 * i + 2;

	// If left child is larger than root
	if (left < N && arr[left].value > arr[largest].value)

		largest = left;

	// If right child is larger than largest
	// so far
	if (right < N && arr[right].value > arr[largest].value)

		largest = right;

	// Swap and continue heapifying if root is not largest
	// If largest is not root
	if (largest != i) {

		swap(arr, i, largest);

		// Recursively heapify the affected
		// sub-tree
		heapify(arr, N, largest);
	}
}

// Main function to do heap sort
void heapSort(Barra arr[], int size) {

	// Build max heap
	for (int i = size / 2 - 1; i >= 0; i--)
		heapify(arr, size, i);

	// Heap sort
	for (int i = size - 1; i >= 0; i--) {

		swap(arr, 0, i);

		// Heapify root element to get highest element at
		// root again
		heapify(arr, i, 0);
	}
}

/*// The main function that sort the given string arr[] in */
/*// alphabetical order */
/*void countSort(char arr[]) */
/*{ */
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

/*	// Copy the output array to arr, so that arr now */
/*	// contains sorted characters */
/*	for (i = 0; arr[i]; ++i) */
/*		arr[i] = output[i]; */
/*} */

// Sorts array a[0..n-1] using Cocktail sort
void CocktailSort(Barra arr[], int size) {
	int swapped = 1;
	int start = 0;
	int end = size - 1;

	while (swapped) {
		// reset the swapped flag on entering
		// the loop, because it might be true from
		// a previous iteration.
		swapped = 0;

		// loop from left to right same as
		// the bubble sort
		for (int i = start; i < end; ++i) {
			if (arr[i].value > arr[i + 1].value) {
				swap(arr, i, i + 1);
				swapped = 1;
			}
		}

		// if nothing moved, then array is sorted.
		if (!swapped)
			break;

		// otherwise, reset the swapped flag so that it
		// can be used in the next stage
		swapped = 0;

		// move the end point back by one, because
		// item at the end is in its rightful spot
		--end;

		// from right to left, doing the
		// same comparison as in the previous stage
		for (int i = end - 1; i >= start; --i) {
			if (arr[i].value > arr[i + 1].value) {
				swap(arr, i, i + 1);
				swapped = 1;
			}
		}

		// increase the starting point, because
		// the last stage would have moved the next
		// smallest number to its rightful spot.
		++start;
	}
}

// A function to sort the algorithm using Odd Even sort
void oddEvenSort(Barra arr[], int size) {
	int isSorted = 0; // Initially array is unsorted

	while (!isSorted)
	{
		isSorted = 1;

		// Perform Bubble sort on odd indexed element
		for (int i=1; i<=size-2; i=i+2)
		{
			if (arr[i].value > arr[i+1].value)
			{
				swap(arr, i, i + 1);
				isSorted = 0;
			}
		}

		// Perform Bubble sort on even indexed element
		for (int i=0; i<=size-2; i=i+2)
		{
			if (arr[i].value > arr[i+1].value)
			{
				swap(arr, i, i + 1);
				isSorted = 0;
			}
		}
	}

	return;
}

/* // Function sort the array using Cycle sort */
/* void cycleSort(Barra arr[], int size) { */
/* 	// count number of memory writes */
/* 	int writes = 0; */

/* 	// traverse array elements and put it to on */
/* 	// the right place */
/* 	for (int cycle_start = 0; cycle_start <= size - 2; cycle_start++) { */
/* 		// initialize item as starting point */
/* 		int item = arr[cycle_start].value; */

/* 		// Find position where we put the item. We basically */
/* 		// count all smaller elements on right side of item. */
/* 		int pos = cycle_start; */
/* 		for (int i = cycle_start + 1; i < size; i++) */
/* 			if (arr[i].value < item) */
/* 				pos++; */

/* 		// If item is already in correct position */
/* 		if (pos == cycle_start) */
/* 			continue; */

/* 		// ignore all duplicate elements */
/* 		while (item == arr[pos].value) */
/* 			pos += 1; */

/* 		// put the item to it's right position */
/* 		if (pos != cycle_start) { */
/* 			swap(item, arr[pos]); */
/* 			swap(arr, item, int index2); */
/* 			writes++; */
/* 		} */

/* 		// Rotate rest of the cycle */
/* 		while (pos != cycle_start) { */
/* 			pos = cycle_start; */

/* 			// Find position where we put the element */
/* 			for (int i = cycle_start + 1; i < n; i++) */
/* 				if (arr[i] < item) */
/* 					pos += 1; */

/* 			// ignore all duplicate elements */
/* 			while (item == arr[pos]) */
/* 				pos += 1; */

/* 			// put the item to it's right position */
/* 			if (item != arr[pos]) { */
/* 				swap(item, arr[pos]); */
/* 				writes++; */
/* 			} */
/* 		} */
/* 	} */

/* 	// Number of memory writes or swaps */
/* 	// cout << writes << endl ; */
/* } */

// To find gap between elements
int getNextGap(int gap) {
	// Shrink gap by Shrink factor
	gap = (gap*10)/13;

	if (gap < 1)
		return 1;
	return gap;
}

// Function to sort a[0..n-1] using Comb Sort
void combSort(Barra arr[], int size) {
	// Initialize gap
	int gap = size;

	// Initialize swapped as true to make sure that
	// loop runs
	int swapped = 1;

	// Keep running while gap is more than 1 and last
	// iteration caused a swap
	while (gap != 1 || swapped == 1)
	{
		// Find next gap
		gap = getNextGap(gap);

		// Initialize swapped as false so that we can
		// check if swap happened or not
		swapped = 0;

		// Compare all elements with current gap
		for (int i=0; i<size-gap; i++)
		{
			if (arr[i].value > arr[i+gap].value)
			{
				swap(arr, i, i + gap);
				swapped = 1;
			}
		}
	}
}
