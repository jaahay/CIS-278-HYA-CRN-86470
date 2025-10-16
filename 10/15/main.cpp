#include "Plant.h"
#include "Flower.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstring>

using namespace std;

void PrintVector(vector<Plant*> garden) {
   int i = int(0);
   for(Plant* plant : garden) {
      ++i;
      cout << "Plant " << i << " Information:" << endl;
      plant->PrintInfo();
      cout << endl;
   }
}

// int main() {
//    string input;
//    cin >> input;
//    while(input != "-1") {
//       cout << input << endl;
//       cin >> input;
//    }
// }

int main() {
   vector<Plant*> myGarden;

   const char* PLANT = "plant";
   const char* FLOWER = "flower";
   // string plantType;
   bool isAnnual;
   string input;

   cin >> input;
   int attempts = 0;
   while(input != "-1") {
      string plantName, flowerName, colorOfFlowers;
      int plantCost;
      ++attempts;
      // cout << endl << "input" << input << endl;
      cin >> plantName;
      cin >> plantCost;
      // cout << "blah" << endl << input << plantName << plantCost << "blahblah" << endl;
      if(strcmp(PLANT, input.c_str()) == 0) {
         // cout << "Plant type" << endl;
         Plant* plant = new Plant();
         plant->SetPlantName(plantName);
         plant->SetPlantCost(plantCost);
         myGarden.push_back(plant);
      }
      if(strcmp(FLOWER, input.c_str()) == 0) {
         // cout << "Flower type" << endl;
         Flower* flower = new Flower();
         flower->SetPlantName(plantName);
         flower->SetPlantCost(plantCost);

         cin >> std::boolalpha >> isAnnual;
         cin >> colorOfFlowers;

         // cout << endl << "is Annual: " << isAnnual << endl;
         // cout << endl << "colorOfFlowers: " << colorOfFlowers << endl;
         flower->SetPlantType(isAnnual);
         flower->SetColorOfFlowers(colorOfFlowers);
         myGarden.push_back(flower);
      }
      cin >> input;
   }
   // cout << endl;
   PrintVector(myGarden);
   // TODO: Call the method PrintVector to print myGarden
   
   return 0;
}
