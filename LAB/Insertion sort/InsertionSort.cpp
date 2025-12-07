#include <iostream>
using namespace std;

// Read size numbers from cin into a new array and return the array.
int* ReadNums(int size) {
   int *nums = new int[size];                // Create array
   for (int i = 0; i < size; ++i) {          // Read the numbers
      cin >> nums[i];
      }
   return nums;
}

// Print the numbers in the array, separated by spaces
// (No space or newline before the first number or after the last.)
void PrintNums(int nums[], int size) {
   for (int i = 0; i < size; ++i) {
      cout << nums[i];
      if (i < size - 1) {
         cout << " ";
      }
   }
   cout << endl;
}

// Exchange nums[j] and nums[k].
void Swap(int nums[], int j, int k) {
   int temp;
   temp = nums[j];
   nums[j] = nums[k];
   nums[k] = temp;
}

// Sort numbers
/* TODO: Count comparisons and swaps.
         Output the array at the end of each iteration. */
void InsertionSort(int numbers[], int size) {
   int i;
   int j;

   for (i = 1; i < size; ++i) {
      j = i;
      comparisons += 1;
      while (j > 0 && numbers[j] < numbers[j - 1]) {
            Swap(numbers, j, j  - 1);
            swaps += 1;
            if(j != i) { comparisons += 1; }
            --j;
      }
      if(j == 0) { comparisons += 1; }
      // if(i == j) { comparisons += 1; }
      // else { comparisons += i - j; }
      PrintNums(numbers, size);
   }
}