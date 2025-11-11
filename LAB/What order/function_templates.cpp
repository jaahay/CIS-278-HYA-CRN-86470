// TODO: Define a generic method called CheckOrder() that
//       takes in four variables of generic type as arguments.
//       The return type of the method is integer

   // Check the order of the input: return -1 for ascending,
   // 0 for neither, 1 for descending
template<typename T>
int CheckOrder(T a, T b, T c, T d) {
   auto comparison = [](T x, T y) -> std::array<bool, 2> {
      std::array<bool, 2> ret = { x < y, x > y };
      return ret;
   };
   auto comp1 = comparison(a, b);
   auto comp2 = comparison(b, c);
   auto comp3 = comparison(c, d);
   // cout << comp1[0] << endl;
   // cout << comp2[0] << endl;
   // cout << comp3[0] << endl;
   if(comp1[0] && comp2[0] && comp3[0]) return -1;
   if(comp1[1] && comp2[1] && comp3[1]) return 1;
   return 0;
}
