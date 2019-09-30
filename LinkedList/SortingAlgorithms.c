#include <stdlib.h>
#include <stdio.h>

//swap
//swaps values of the sent memory locations
//left is one memory location, and right is another memory location
inline void swap(int *left, int *right) {
	int temp = *left;
	*left = *right;
	*right = temp;
}

//selection sort
//finds the smallest element in the sent array and puts it at the beggining and repeats until done
//A[] is the sent array to sort, n is the number of values in the array
void selection_sort(int A[], int n) {
	int min;
	for (int i = 0; i < n; i++) {
		min = i;
		for (int j = i + 1; j < n; j++) {
			if (A[j] < A[min]) {
				min = j;
			}
		}
		swap(&A[i], &A[min]);
	}
}

//bubble sort
//sorts elements pair by pair
//A[] is the sent array to sort, n is the number of values in the array
void bubble_sort(int A[], int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (A[j + 1] < A[j])
				swap(&A[j], &A[j + 1]);
		}
	}
}

//buble sort improved
//works the same as bubble sort, but if in the iteration of outer loop change didn't happen, the array is considered sorted
//A[] is the sent array to sort, n is the number of values in the array
void bubble_sort_improved(int A[], int n) {
	int change_happened = 1;
	for (int i = 0, change_happened = 1; change_happened; i++) {
		change_happened = 0;
		for (int j = 0; j < n - 1 - i; j++) {
			if (A[j + 1] < A[j]) {
				swap(&A[j], &A[j + 1]);
				change_happened = 1;
			}
		}
	}
}

//insertion sort
//goes through elements on diagonal and sorts it on the left side of the diagonal
//A[] is the sent array to sort, n is the number of values in the array
void insertion_sort(int A[], int n) {
	int temp, i, j;
	for (i = 1; i < n; i++) {
		temp = A[i];
		for (j = i; j >= 1 && A[j - 1] > temp; j--)
			A[j] = A[j - 1];
		A[j] = temp;
	}
}

//shell sort
//works similar to insertion sort, but it is meant for elements further away
//A[] is the sent array to sort, n is the number of values in the array
void shell_sort(int A[], int n) {
	int i, j, step;
	int pom;
	for (step = n / 2; step > 0; step /= 2) {
		for (i = step; i < n; i++) {
			pom = A[i];
			for (j = i; j >= step && A[j - step] > pom; j -= step) {
				A[j] = A[j - step];
			}
			A[j] = pom;
		}
	}
}

//auxiliary function for heap sort(it represents a heap creation with the highest number on top)
void heapify(int A[], int n, int i) {

	//largest root, left child and right child indexes
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left<n && A[left]>A[largest])
		largest = left;

	if (right<n && A[right]>A[largest])
		largest = right;

	if (largest != i) {
		
		//since largest is the index of the highest number,
		//the swap happens so that the largest element is the root
		//after that we call heapify again
		swap(&A[i], &A[largest]);
		heapify(A, n, largest);
	}
}

//heap sort
//A[] is the array to sort, n is the number of array elements
void heap_sort(int A[], int n) {
	//build max heap
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(A, n, i);
	}

	//heap sort
	for (int i = n - 1; i >= 0; i--) {
		swap(&A[0], &A[i]);

		//heapify root element to get highest element at root again
		heapify(A, i, 0);
	}
}

//auxiliary function for merge sort(it merges 2 arrays in one)
void merge(int A[], int start, int mid, int end) {

	//temperary array should have the size of "end-start+1", 
	//but since the size of the array has to be a constant value,
	//it is set to 100
	int temp[100 + 1];

	//values of indexes for array iteration
	int i = start, j = mid + 1, k = 0;

	//transfering both arrays in each iteration and smaller 
	//of both elements in temperary array
	while (i <= mid && j <= end) {
		if (A[i] <= A[j]) {
			temp[k] = A[i];
			k++;
			i++;
		}
		else {
			temp[k] = A[j];
			k++;
			j++;
		}
	}

	//add elements left in the first interval
	while (i <= mid) {
		temp[k] = A[i];
		k++;
		i++;
	}

	//add elements left in the second interval
	while (j <= end) {
		temp[k] = A[j];
		k++;
		j++;
	}

	//copy temperary array to original
	for (i = start; i <= end; i++) {
		A[i] = temp[i - start];
	}

}

//merge sort
//A[] is the array to sort, start is the first index of the array part to sort 
//and end is the last index of the array part to sort
void _merge_sort(int A[], int start, int end) {
	if (start < end) {
		//breaking an array in 2 pieces
		int mid = (start + end) / 2;
		_merge_sort(A, start, mid);
		_merge_sort(A, mid + 1, end);

		//function to merge back 2 arrays in one
		merge(A, start, mid, end);
	}
}

//merge sort (to sort entire array)
//calls real merge sort
//A[] is the array to sort, n is the number of elements
void merge_sort(int A[], int n) {
	_merge_sort(A, 0, n - 1);
}

//auxiliary function for quick sort(it determines the pivot by "median of three" method)
int median3(int A[], int start, int end) {
	//method sorts first, last and middle element 
	//and then chooses middle one as the pivot 
	int mid = (start + end) / 2;
	if (A[start] > A[mid])
		swap(&A[start], &A[mid]);
	if (A[start] > A[mid])
		swap(&A[start], &A[end]);
	if (A[mid] > A[end])
		swap(&A[mid], &A[end]);

	swap(&A[mid], &A[end - 1]);
	return A[end - 1];
}

//auxiliary function for quick sort(it puts pivot element at correct position, all smaller elements on left, and larger on right)
int partition(int A[], int start, int end)
{
	//method replaces smaller elements from right
	//with larger elements from left
	int pivot = median3(A, start, end);
	int i = (start - 1);
	--end;

	for (int j = start; j <= end - 1; j++)
	{
		if (A[j] < pivot)
		{
			i++;
			swap(&A[i], &A[j]);
		}
	}
	swap(&A[i + 1], &A[end]);
	return (i + 1);
}

//quick sort
//A[] is the array to sort, start is starting index and end is ending index
void _quick_sort(int A[], int start, int end)
{
	if (start < end)
	{
		//pi is index of partition, A[p] is now sorted
		int pi = partition(A, start, end);

		//elements before partition and after are sorted seperately
		_quick_sort(A, start, pi - 1);
		_quick_sort(A, pi + 1, end);
	}
 }

//quick sort (to sort entire array)
//calls real quick sort
//A[] is array to sort, n is the number of elements
void quick_sort(int A[], int n) {
	_quick_sort(A, 0, n - 1);
}

//main function (for testing)
int main() {
	int A[] = { 4, 2, 3, 8, 10, 9 };

	//uncomment the sort you want to test
	//selection_sort(A, 6);
	//bubble_sort(A, 6);
	//bubble_sort_improved(A, 6);
	//insertion_sort(A, 6);
	//shell_sort(A, 6);
	//heap_sort(A, 6);
	//merge_sort(A, 6);
	//quick_sort(A, 6);

	for (int i = 0; i < 6; i++) {
		printf("%d ", A[i]);
	}

	system("pause");
	return 0;
}
