#ifndef COMPLEX_H
#define COMPLEX_H
#include <iostream>

using namespace std;

/* 
// complex numbers: are represented as X+Yi where x and Y are real numbers.
// X is referred to as the real part and Y as the imaginary part of the 
// complex number. For example complex(5.6,7.2) means 
// 5.6+7.2i. 
//
// Implementation and assumptions:
//   -- complex are stored as real integers X and Y.
//   -- i^2 = -1
//   -- Dividing by zero produces a printed error message and returns 0.
//
// Deeksha Sharma 10/10/2017
*/

class complex
{
	private:
		double real;  //represents the real part of the complex number
		double imaginary; //is the imaginary part of the complex number 
	public:
		//default constructor: parameters are the real number and the imaginary number resp. 
		complex(double = 0.0, double = 0.0);

		double getReal() const; //Accessor method for the real part of the complex number 
		double getImaginary() const; //Accessor method for the imaginary part of the complex number 

		//arthimetic operators 
		complex operator+(const complex&) const; //adds 2 complex numbers
		complex operator-(const complex&) const; //subtracts 2 complex numbers
		complex operator*(const complex&) const; //multiplies 2 complex numbers
		complex operator/(const complex&) const; //divides 2 complex numbers

		//returns the conjugate of the complex number. For example if the input is 
		//5.0+6.0i the output will be 5.0-6.01
		complex conjugate(); //returns the conjugate of the object. If object is z=x+yi this return x-yi

		//comparison operators 
		bool operator==(const complex&) const; //returns true of false depending on if the object == the parameter
		bool operator!=(const complex&) const; //returns true of false depending on if the object == the parameter

		//assignment operators 
		complex& operator+=(const complex&); //output is the current object += the parameter 
		complex& operator-=(const complex&); //output is the current object -= the parameter
		complex& operator*=(const complex&); //output is the current object *= the parameter
		complex& operator/=(const complex&); //output is the current object /= the parameter

		//Stream I/O
		//operator << is overloaded according to how complex numbers should be printed 
		//if Y is one then it print X+i
		//if Y or X is 0 they are omitted from the output 
		//if both Y and X are 0 then the output is 0
		//if Y is negative then the output is X-Yi not X+-Yi
		friend ostream& operator<<(ostream&, const complex&);
		//operator >> is overloaded to take 2 ints as the real and imaginary part
		friend istream& operator>>(istream&, complex&);
};
#endif