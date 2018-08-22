#include <iostream>
#include "complex.h"

/*
// Complex number class implementation of complex.h file
//
// Deeksha Sharma 10/10/2017 
*/

using namespace std;

//The parameters to this constructor are the real and imaginary part of the complex number resp. 
//This constructor takes in zero, one, or two parameters or sets the instance variables to the deafult value of 0.0
//Pre-condition: the arguments passed in for r and i must be doubles
//Post-condition: r = real and i = imaginary part of the complex number created 
complex::complex(double r, double i) {
	real = r < 0 ? -r : r;
	imaginary = i < 0 ? -i : i;
}

//Pre-condition: assumed that a is a valid complex number
//Post-condition: this method returns the sum of 2 complex numbers 
complex complex::operator+(const complex &a) const
{
	complex sum;

	sum.real = real + a.real;
	sum.imaginary = imaginary + a.imaginary;

	return sum;
}

//Pre-condition: assumed that a is a valid complex number
//Post-condition: this method returns the difference of 2 complex numbers 
complex complex::operator-(const complex &a) const
{
	complex difference;

	difference.real = real - a.real;
	difference.imaginary = imaginary - a.imaginary;

	return difference;
}

//Pre-condition: assumed that a is a valid complex number
//Post-condition: this method returns the product of 2 complex numbers 
complex complex::operator*(const complex &a) const
{
	complex product;

	product.real = (real*a.real) + (-1 * imaginary + a.imaginary);
	product.imaginary = (real*a.imaginary) + (imaginary*a.real);
	
	return product;
}

//Pre-condition: the calling object is a valid complex number
//Post-condition: this method returns the conjugate of the calling object complex number 
//for example if calling object = 5.1+7.2i this method returns 5.1-7.2i
complex complex::conjugate()
{
	complex con;

	con.real = real;
	con.imaginary = -1 * imaginary;

	return con;
}

/*
Pre-Condition: a.real and a.imaginary do not equal zero; a is a complex number
Post Condition: this method returns the quotient of two complex numbers or a divide by 0 error
*/
complex complex::operator/(const complex &a) const {
	complex quotient;

	if (a.real != 0 || a.imaginary != 0) {
		double divisor = (a.real * a.real) + (-1 * a.imaginary * a.imaginary);
		quotient.real = ((real * a.real) + (-1 * imaginary * a.imaginary)) / divisor;
		quotient.imaginary = ((-1 * real * a.imaginary) + (a.real * imaginary)) / divisor;
	}
	else {
		cout << "divide by 0 error" << endl;
		return 0;
	}

	return quotient;
}

//Pre-condition: assumed that a is a valid complex number 
//Post-condition: this method returns true if the a equals the calling object 
bool complex::operator==(const complex &a) const
{
	return (real == a.real && imaginary == a.imaginary);
}

//Pre-condition: assumed that a is a valid complex number 
//Post-condition: this method returns true if the a doesnt equals the calling object 
bool complex::operator!=(const complex &a) const
{
	return !(*this == a);
}

//Pre-condition: assumed that a is a valid complex number and the calling object exists 
//Post-condition: this method returns the calling object after adding a to it 
complex& complex::operator+=(const complex &a)
{
	//return (*this + a);
	real = real + a.real;
	imaginary = imaginary - a.imaginary;

	return *this;
}

//Pre-condition: assumed that a is a valid complex number and the calling object exists 
//Post-condition: this method returns the calling object after subtracting a from it 
complex& complex::operator-=(const complex &a)
{
	//return (*this - a);
	real = real - a.real;
	imaginary = imaginary - a.imaginary;

	return *this;
}

//Pre-condition: assumed that a is a valid complex number and the calling object exists 
//Post-condition: this method returns the calling object after multiplying a to it 
complex& complex::operator*=(const complex &a)
{
	//return (*this * a);
	real = (real*a.real) + (-1 * imaginary + a.imaginary);
	imaginary = (real*a.imaginary) + (imaginary*a.real);

	return *this;
}

//Pre-condition: assumed that a is a valid complex number and the calling object exists
//Post-condition: this method returns the calling object after dividing it by a 
complex& complex::operator/=(const complex &a) 
{
	//return (*this / a);
	if (a.real != 0 || a.imaginary != 0) {
		double divisor = (a.real * a.real) + (-1 * a.imaginary * a.imaginary);
		real = ((real * a.real) + (-1 * imaginary * a.imaginary)) / divisor;
		imaginary = ((-1 * real * a.imaginary) + (a.real * imaginary)) / divisor;
	}
	else {
		cout << "divide by 0 error" << endl;
	}

	return *this;
}

//Pre-condition: assumed that a isnt null
//Post-condition: prints out the complex number in the format X+Yi and X-Yi.
//prints out Yi if a=0, X if Y=0, and 0 if both X and Y = 0.
ostream& operator<<(ostream &output, const complex &a)
{
	if (a.getReal() == 0 && a.getImaginary() == 0) return output << "0";
	else 
	{
		if (a.getReal() != 0)
		{
			if (a.getReal() < 0)
			{
				output << "-";
			}
			a.getImaginary() > 0 ? output << a.getReal() << "+" : output << a.getReal();
		}
		if (a.getImaginary() != 0)
		{
			/*if (a.getImaginary() < 0)
			{
				output << "-";
			}*/
			if (a.getImaginary() == 1)
			{
				return output << "i";
			}
			else if (a.getImaginary() == -1)
			{
				return output << "-i";
			}
			else
			{
				return output << a.getImaginary() << "i";
			}
		}
		return output;
	}
}

//Post-condition: takes in two doubles and creates a complex number with a 
//real and an imaginary part.
istream& operator>>(istream &input, complex &a)
{
	input >> a.real >> a.imaginary;
	return input;
}

//Accessor method for the real instance variable of the complex number  
double complex::getReal() const
{
	return real;
}
//Accessor method for the imaginary instance variable of the complex number  
double complex::getImaginary() const
{
	return imaginary;
}

