#include <iostream>
#include <string>
#include <vector>

#include "InsertionSort.cpp"

void RunTest(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        // return 1; // Or handle the error appropriately
    }
    std::streambuf* original_cin_buf = std::cin.rdbuf(); // Save original buffer
    std::cin.rdbuf(file.rdbuf()); // Redirect cin to the file's buffer

    InsertionSort iS(filename);
    // Step 1: Read numbers into an array
    int size;
    std::cin >> size;                            // Read array size
    int* numbers = iS.ReadNums(size);           // Read numbers

    // Step 2: Output the numbers array
    iS.PrintNums(numbers, size);
    std::cout << std::endl;

    // Step 3: Sort the numbers array
    iS.DoInsertionSort(numbers, size);
    std::cout << std::endl;

    // Step 4: Output the number of comparisons and swaps
    /* TODO: Output the number of comparisons and swaps performed */
    
    std::cout << "comparisons: " << iS.comparisons << std::endl;
    std::cout << "swaps: " << iS.swaps << std::endl;

    file.close();
}

std::string case_files[] = {
    "test_case1.txt",
    "test_case2.txt",
    "test_case3.txt",
    "test_case4.txt",
    "test_case5.txt",
}

int main() {
   RunTest("test_case");
   
   return 0;
}
