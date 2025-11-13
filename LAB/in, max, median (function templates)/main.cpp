#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm> // to use sort()
using namespace std;

const int NUM_VALUES = 5;

// Input NUM_VALUES of TheType into the vector parameter
template<typename TheType> void Read(vector<TheType>& list) {
   for (int j = 0; j < NUM_VALUES; ++j) {
      cin >> list.at(j);
   }
}

// Output the elements of the vector parameter
template<typename TheType> void Write(const vector<TheType>& list) {
   long unsigned int j;
   for (j = 0; j < list.size(); ++j) {
      cout << list.at(j) << " ";
   }
}

// Return the min, median, and max of the vector parameter in a new vector
template<typename TheType> vector<TheType> GetStatistics(const vector<TheType>& list) {
   std::unordered_map<TheType, int> freqMap{};
   freqMap[list[0]] = 1;
   TheType min = list[0],
            max = list[0];
   for(size_t i = 1; i < list.size(); i++) {
      min = std::min(min, list.at(i));
      max = std::max(max, list.at(i));
      freqMap[list[i]]++;
   }
   TheType median = list[0];
   int median_count = freqMap[median];
   for(const auto& pair : freqMap) {
      if(pair.second > median_count) {
         median = pair.first;
         median_count = pair.second;
      }
   }

   return {min, median, max};

   /* Type your code here. */
   
}

// Read values into a vector, sort the vector, output the sorted vector,
// then output the min, median, and max of the sorted vector
template<typename TheType> void Run(vector<TheType>& list) {
   Write(list);
   std::sort(list.begin(), list.end());
   Write(list);
   Write(GetStatistics(list));
}

int main() {
   vector<int> integers(NUM_VALUES);
   Run(integers);
   cout << endl;

   vector<double> doubles(NUM_VALUES);
   Run(doubles);
   cout << endl;

   vector<string> strings(NUM_VALUES);
   Run(strings);

   return 0;
}
