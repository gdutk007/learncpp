#include <iostream>
#include <cmath>

using namespace std;

// please copile with: g++ chapter14/quiz14.cpp -std=c++17

class Point2d {
   
   float m_x{0.0};
   float m_y{0.0};

   public:

   Point2d(){} // could be Point2d() = default but this won't zero init members of class
   
   Point2d(float x, float y) : m_x{ x }, m_y{ y }
   {
      //cout << "in constructor";
   }

   void print(){
      cout << "Point2d(" << m_x << "," << m_y << ")\n";
   }

   float distanceTo(const Point2d& second){
      return sqrt( (m_x - second.m_x)*(m_x - second.m_x) + (m_y - second.m_y)*(m_y - second.m_y) );
   }

};


struct Fraction {
    int numerator{ 0 };
    int denominator{ 1 };

    public:

   Fraction() = default;

   explicit Fraction(int num, int denom):  // prevents implicit conversions
      numerator{num}, denominator{denom} 
   {}

   Fraction multiply(const Fraction& f1, const Fraction& f2){
      return Fraction{ f1.numerator * f2.numerator, f1.denominator * f2.denominator };
   }

   void printFraction(const Fraction& f){
      std::cout << f.numerator << '/' << f.denominator << '\n';
   }

   void getFraction(){
      
      std::cout << "Enter a value for numerator: ";
      std::cin >> numerator;
      std::cout << "Enter a value for denominator: ";
      std::cin >> denominator;
      std::cout << '\n';
   }
};


int main(){
   Point2d first{};

   Point2d second{3.0, 4.0};

   first.print();
   second.print();
   cout << "Distance between two points: " << first.distanceTo(second) << "\n";
   return 0;
}