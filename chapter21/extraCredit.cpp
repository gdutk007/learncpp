/*
4. Extra credit: This one is a little more tricky. A floating point number is a number with a decimal where the number of digits after the decimal can be variable.
A fixed point number is a number with a fractional component where the number of digits in the fractional portion is fixed. In this quiz, we’re going to write
a class to implement a fixed point number with two fractional digits (e.g. 12.34, 3.00, or 1278.99). Assume that the range of the class should be -32768.99 to 32767.99,
that the fractional component should hold any two digits, that we don’t want precision errors, and that we want to conserve space.

4a) What type of member variable(s) do you think we should use to implement our fixed point number with 2 digits after the decimal?
(Make sure you read the answer before proceeding with the next questions)

4a). Answer: because -32768 and +32768 is the desired range, we want a 16 bit signed number. The fractional part can use 8 bits
*/

/**
 * 4b) Write a class named FixedPoint2 that implements the recommended solution from the previous question. 
 * If either (or both) of the non-fractional and fractional part of the number are negative, the number should 
 * be treated as negative. Provide the overloaded operators and constructors required for the following program to run:
 */
 
#include <iostream>
//#include<int_t>

using namespace std;

 class FixedPoint2 {

   private:

   bool pos{true};
   int16_t m_num{0};
   int8_t m_fraction{0};

   public:

   FixedPoint2() = default;

   FixedPoint2(int16_t num, int8_t fraction): 
               m_num{num}, m_fraction{fraction}
               {
                  if(num < 0 || fraction < 0){
                     pos = false;
                     if(num < 0){
                        m_num *= -1;
                     }
                     if( fraction < 0){
                        m_fraction *= -1;
                     }
                  }
               }
   
   friend ostream& operator<<(ostream& out, FixedPoint2& obj){
      double num = static_cast<double>(obj.m_num) + static_cast<double>(obj.m_fraction)/100.0;
      if(!obj.pos){
         num *= -1;
      }
      out << num <<  
      "\n";
      return out;
   }
 };

 int main()
{
	FixedPoint2 a{ 34, 56 };
	std::cout << a << '\n';

	FixedPoint2 b{ -2, 8 };
	std::cout << b << '\n';

	FixedPoint2 c{ 2, -8 };
	std::cout << c << '\n';

	FixedPoint2 d{ -2, -8 };
	std::cout << d << '\n';

	FixedPoint2 e{ 0, -5 };
	std::cout << e << '\n';

	//std::cout << static_cast<double>(e) << '\n';

	return 0;
}
