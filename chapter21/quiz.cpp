
#include <iostream>

using namespace std;


/*
   1. Assuming Point is a class and point is an instance of that class, should you use a normal/friend or member function overload for the following operators?

   1a) point + point 
   1b) -point 
   1c) std::cout << point
   1d) point = 5;

ans:
   1a. normal/friend functions because '+' has binary operands and left is not modified(new value is returned)
   1b. member function function because it's a unary operator
   1c. friend/normal function because ostream has to be a const reference on the left operand and has to be returned by reference
   1d. member function because copy assignment should be member function because left operand is medified and returned
*/


/*
2
    Write a class named Average that will keep track of the average of all integers passed to it. Use two members: The first one should be type std::int32_t, 
    and used to keep track of the sum of all the numbers you’ve seen so far. The second should be of type std::int8_t, and used to keep track of how many
    numbers you’ve seen so far. You can divide them to find your average.

2a) Write all of the functions necessary for the following program to run:
*/
class Average{
   private:
   int32_t sum{0};
   int8_t nums{0};
   public:

   Average(){}

   Average(int32_t s, int8_t n):
                  sum{s}, nums{n} 
                  {}
   Average& operator+=(int val){
      sum += val;
      nums += 1;
      return *this;
   }

   friend std::ostream& operator<<(std::ostream& out, Average & obj){
      
      if(obj.nums)
         out << (static_cast<float>(obj.sum)/obj.nums);
      else
         out << "no numbers have been added.";
      
      return out;
   }

};

//The following is a working solution
/*int main()
{
	Average avg{};
	avg += 4;
	std::cout << avg << '\n'; // 4 / 1 = 4

	avg += 8;
	std::cout << avg << '\n'; // (4 + 8) / 2 = 6

	avg += 24;
	std::cout << avg << '\n'; // (4 + 8 + 24) / 3 = 12

	avg += -10;
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10) / 4 = 6.5

	(avg += 6) += 10; // 2 calls chained together
	std::cout << avg << '\n'; // (4 + 8 + 24 - 10 + 6 + 10) / 6 = 7

	Average copy{ avg };
	std::cout << copy << '\n';

	return 0;
}*/

/*
2b Should this define a copy assignment operator and a copy constructor? 
No because there is no dynamic memory being used. Memberwise init is okay.
*/


/*
3. Write your own integer array class named IntArray from scratch (do not use std::array or std::vector). 
Users should pass in the size of the array when it is created, and the array should be dynamically allocated.
Use assert statements to guard against bad data. Create any constructors or overloaded operators needed to make
the following program operate correctly:
*/
class IntArray {
   private:
   int * ptr{nullptr};
   int size{0};
   public:
   IntArray() = delete;
   IntArray(int sz):size{sz}
   {
      cout << "ctor";
      if(ptr){
         delete[] ptr;
         ptr = nullptr;
      }
      ptr = new int[size];
   }
   
   /**
    * Because the class deals with dynamic memory, the default memberwise copy in the ctor and copy-Assignment
    * operators won't work. We will get UB. To get around this we must use the rule of three(implement copy ctor, copy assignment and dtor) 
    */

   void doDeepCopy(int* p, int sz){
      ptr = new int[size];
      size = sz;
      for(int i = 0; i < sz; ++i){
         ptr[i] = p[i];
      }
   }
   
   ~IntArray(){
      if(ptr){
         delete[] ptr;
         ptr = nullptr;
         size = 0;
      }
   }

   IntArray(const IntArray& obj){
      //cout << "copy ctor";
      doDeepCopy(obj.ptr, obj.size);
   }

   IntArray& operator=(const IntArray& obj){
      // avoid self-assignmet
      //cout << "copy assignment";
      if(this == &obj) {
         //cout << "\n bailing\n";
         return *this;
      }
      /**
       *  because we are reassigning the left operand
       *  we need to delete whatever the left operand was pointing too
       *  if not we will leak memory
       * */
      if(ptr){
         delete[] ptr;
         size = 0;
         ptr = nullptr;
      }
      doDeepCopy(obj.ptr,obj.size);
      return *this;
   }

   int& operator[](int index){
      assert(index >= 0 && index < size);
      return ptr[index];
   }

   friend ostream& operator<<(ostream& out, IntArray& obj){
      for(int i = 0; i < obj.size; ++i){
         out << " " << obj.ptr[i] << " ";
      }
      return out;
   }
};

IntArray fillArray()
{
	IntArray a(5);

	a[0] = 5;
	a[1] = 8;
	a[2] = 2;
	a[3] = 3;
	a[4] = 6;

	return a;
}

int main()
{
	IntArray a{ fillArray() };

	std::cout << a << '\n';

	auto& ref{ a }; // we're using this reference to avoid compiler self-assignment errors
	a = ref;

	IntArray b(1);
	b = a;

	a[4] = 7;

	std::cout << b << '\n';
   std::cout << a << '\n';
	return 0;
}
