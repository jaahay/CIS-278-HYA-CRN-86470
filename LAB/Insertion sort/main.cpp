#include <iostream>

#include "InsertionSort.cpp"

using namespace std;

int main() {
   // Step 1: Read numbers into an array
   int size;
   cin >> size;                             // Read array size
   int* numbers = ReadNums(size);           // Read numbers

   // Step 2: Output the numbers array
   PrintNums(numbers, size);
   cout << endl;

   // Step 3: Sort the numbers array
   InsertionSort(numbers, size);
   cout << endl;

   // Step 4: Output the number of comparisons and swaps
   /* TODO: Output the number of comparisons and swaps performed */
   cout << "comparisons: " << comparisons << endl;
   cout << "swaps: " << swaps << endl;
   
   return 0;
}
