#ifndef STATEPAIR
#define STATEPAIR

template<typename T1, typename T2>
class StatePair {
// TODO: Define constructors
   T1 t1;
   T2 t2;

   public:
      StatePair() {};
      StatePair(T1 userKey, T2 userValue) {
         this->t1 = userKey;
         this->t2 = userValue;
      }
      void SetKey(T1 t1) { this->t1 = t1;}
      T1 GetKey() { return t1; }

      void SetValue(T2 t2) { this->t2 = t2; }
      T2 GetValue() { return t2; }

      void PrintInfo() {
         std::cout << t1 << ": " << t2 << std::endl;
      }
// TODO: Define mutators, and accessors for StatePair
	
// TODO: Define PrintInfo() method
};

#endif
