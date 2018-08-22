/*
Author: Deeksha Sharma 
Date: 12/11/2017
*/

#include "LongInt.h"
#include<string>

using namespace std;

/*
Pre-condition: the input line is a string 
Post-condition: a LongInt is created vis the input stream 
*/
istream &operator>>(istream &in, LongInt &rhs)
{
	string input;
	getline(in, input);
	rhs = LongInt(input);
}

/*
Pre-condition: rhs isnt NULL
Post-condition: the LongInt stored in rhs is output with the proper sign and without leading zeros 
*/
ostream &operator<<(ostream &out, const LongInt &rhs)
{
	//creates a temp LongInt to use in printing rhs 
	Deque<char> temp = rhs.digits;
	if ((rhs.digits.size() == 1) && (rhs.digits.getFront() == '0')) //if rhs holds only a '0' then that is printed on the screen 
	{
		cout << '0' << endl;
	}
	else
	{
		if (rhs.negative) out << '-'; //if rhs is negative the '-' sign is printed on the screen 
		while (temp.getFront() == '0') temp.removeFront(); //removes leading zero's 
		while (!temp.isEmpty()) //prints digits in temp until it is empty 
		{
			out << temp.removeFront();
		}
	}
	return out;
}

/*
Pre-condition: str is an initialized string 
Post-condition: a LongInt object of the string is created 
*/
LongInt::LongInt(const string str)
{
	digits.clear();
	negative = false;

	int i = 0;
	if (str[i] == '-') //checks if str is negative and sets the negative data member accordingly 
	{
		i += 1;
		negative = true;
	}
	
	for (; i < str.length(); i++) //skips over leading zeros 
	{
		if (str[i] > '0' && str[i] <= '9') break;
		if (str[i] == '0') continue;
	}

	for (; i < str.length(); i++) //creates a LongInt of the remaining string characters 
	{
		if (str[i] >= '0' && str[i] <= '9') digits.addBack(str[i]);
	}
}

/* 
Pre-condition: rhs is a LongInt 
Post-condition: creates a copy of rhs 
*/
LongInt::LongInt(const LongInt & rhs)
{
	digits.clear();
	digits = rhs.digits;
	negative = rhs.negative;
}

/*
Default construstor 
Post-condition: new LongInt created equaling 0
*/
LongInt::LongInt()
{
	digits.clear();
	negative = false;
	digits.addFront('0');
}

/*
Pre-condition: calling object is a valid LongInt
Post-condition: deallacates memory for this LongInt
*/
LongInt::~LongInt()
{
	digits.~Deque();
}

/*
Pre-condition: rhs is a LongInt
Post-condition: returns a LongInt which is the sum of *this and rhs 
*/
LongInt LongInt::operator+(const LongInt &rhs) const
{
	int carry = 0;
	int result = 0;
	LongInt sum;
	LongInt copyLeft = *this;
	LongInt copyRight = rhs;
	Deque<char> left = digits;
	Deque<char> right = rhs.digits;
	sum.digits.clear();

	if (left.size() < right.size()) { //finds the longest between *this and rhs and makes it so longer of the 2 is on the left side of the + operator
		sum = rhs + *this;
	}
	else if (negative && rhs.negative) { //if both *this and rhs are negative do: -lhs + (-rhs) = -(lhs + rhs)
		copyLeft.negative = false;
		copyRight.negative = false;
		sum = copyLeft + copyRight;
		sum.negative = true;
	}
	else if (negative) { //if *this is negative do: -lhs + rhs = rhs - lhs
		copyLeft.negative = false;
		sum = rhs - copyLeft;
	}
	else if (rhs.negative) { //if rhs is negative do: lhs + (-rhs) = lhs - rhs
		copyRight.negative = false;
		sum = *this - copyRight;
	}
	else { //if both values are positive do: lhs + rhs = lhs + rhs 
		while (!(right.isEmpty())) { //do until right is empty 
			int l = left.removeBack() - 48;
			int r = right.removeBack() - 48;
			result = (l + r + carry) % 10;
			carry = (l + r + carry) / 10;
			sum.digits.addFront(result + 48);
		}

		while ((carry > 0) && !(left.isEmpty())) { //add carry to the left until a carry > 0 remains 
			int l = left.removeBack() - 48;
			result = (l + carry) % 10;
			carry = (l + carry) / 10;
			sum.digits.addFront(result + 48);
		}

		if (carry > 0) { 
			sum.digits.addFront(carry + 48);
		}

		while (!(left.isEmpty())) { //adds the remaining values of left to sum
			char l = left.removeFront();
			sum.digits.addFront(l);
		}
	}
	return sum;
}

/*
Pre-condition: rhs is a LongInt	
Post-condition: returns a LongInt which is the difference of *this and rhs 
*/
LongInt LongInt::operator-(const LongInt &rhs) const 
{
	int borrow = 0;
	int result = 0;
	LongInt diff;
	LongInt copyLeft = *this;
	LongInt copyRight = rhs;
	Deque<char> left = digits;
	Deque<char> right = rhs.digits;
	diff.digits.clear();

	if (left.size() < right.size()) { //finds the longest between *this and rhs and makes it so longer of the 2 is on the left side of the - operator
		diff = rhs + *this;
	}
	else if (negative && rhs.negative) { //if both *this and ths are negative do: -lhs - (-rhs) = rhs - lhs
		copyLeft.negative = false;
		copyRight.negative = false;
		diff = copyLeft - copyRight;
	}
	else if (negative) { //if *this is negative do: -lhs - rhs = -(lhs + rhs)
		copyLeft.negative = false;
		diff = copyLeft + copyRight;
		diff.negative = true;
	}
	else if (rhs.negative) { //if rhs is negative do: lhs - (-rhs) = lhs + rhs
		copyRight.negative = false;
		diff = copyLeft + copyRight;
	}
	else { //if both *this and rhs are positive do: lhs - rhs = lhs - rhs
		int top = 0;
		int bottom = 0;
		while (!(left.isEmpty())) { //do until left is empty 
			top = left.removeBack() - 48;
			if (!(right.isEmpty())) {
				bottom = right.removeBack() - 48;
			}
			else {
				bottom = 0;
			}

			if (borrow == 1) {
				top--;
				borrow--;
			}

			if (top < bottom && !(left.isEmpty())) {
				top += 10;
				borrow++;
			}
			if ((top - bottom) < 0 && left.isEmpty()) {
				result = (top - bottom) * -1;
				diff.negative = true;
			}
			else {
				result = top - bottom;
			}
			diff.digits.addFront(result + 48);
		}
	}
	return diff;
}

/*
Pre-condition: rhs is a LongInt 
Post-condition: returns *this after assigning the value of rhs to it 
*/
const LongInt &LongInt::operator=(const LongInt &rhs)
{
	digits = rhs.digits;
	negative = rhs.negative;
	return *this;
}

/*
Pre-condition: rhs is a LongInt 
Post-condition: returns true if *this is less than rhs and false otherwise 
*/
bool LongInt::operator<(const LongInt & rhs) const
{
	if (*this == rhs) return false;
	else if (negative && rhs.negative) //if *this and rhs are negative test their positive counterparts like so: leftCopy > rightCopy 
	{
		LongInt leftCopy = *this;
		LongInt rightCopy = rhs;
		leftCopy.negative = false; 
		rightCopy.negative = false; 
		return leftCopy > rightCopy;
	}
	else if (negative) return true; 
	else if (rhs.negative) return false;
	else 
	{
		if (digits.size() == rhs.digits.size()) //do if *this and rhs are of the same size 
		{
			Deque<char> left = digits;
			Deque<char> right = rhs.digits;
			for (int i = 0; i < left.size(); i++)
			{
				int l = left.removeFront();
				int r = right.removeFront();
				if (l > r) return false;
			}
			return true;
		}
		else if (digits.size() < rhs.digits.size()) return true;
		else return false; 
	}
	return true;
}

/*
Pre-condition: rhs is a LongInt 
Post-condition: returns true if *this is less than or equal to rhs and false otherwise 
*/
bool LongInt::operator<=(const LongInt & rhs) const
{
	if (*this == rhs || *this < rhs) return true;
	return false;
}

/*
Pre-condition: rhs is a LongInt 
Post-condition: returns true if *this is greater than rhs and false otherwise 
*/
bool LongInt::operator>(const LongInt & rhs) const
{
	if (*this == rhs) return false;
	else if (negative && rhs.negative) //if *this and rhs are negative test their positive counterparts like so: leftCopy < rightCopy 
	{
		LongInt leftCopy = *this;
		LongInt rightCopy = rhs;
		leftCopy.negative = false;
		rightCopy.negative = true;
		return leftCopy < rightCopy;
	}
	else if (negative) return false;
	else if (rhs.negative) return true;
	else
	{
		if (digits.size() == rhs.digits.size()) //do if *this and rhs are of the same length 
		{
			Deque<char> left = digits;
			Deque<char> right = rhs.digits;
			for (int i = 0; i < left.size(); i++)
			{
				int l = left.removeFront();
				int r = right.removeFront();
				if (l < r) return false;
			}
			return true;
		}
		else if (digits.size() > rhs.digits.size()) return true;
		else return false;
	}
}

/*
Pre-condition: rhs is a LongInt
Post-condition: returns true if *this is greater than or equal to rhs and false otherwise
*/
bool LongInt::operator>=(const LongInt & rhs) const
{
	if (*this == rhs || *this > rhs) return true;
	return false; 
}

/*
Pre-condition: rhs is a LongInt  
Post-condition: returns true if *this is equal to rhs and false otherwise 
*/
bool LongInt::operator==(const LongInt & rhs) const
{
	Deque<char> left = digits;
	Deque<char> right = rhs.digits;
	if (left.size() != right.size()) return false;
	else
	{
		if (negative != rhs.negative) return false;
		while (!left.isEmpty())
		{
			int l = left.removeFront();
			int r = right.removeFront();
			if (l != r) return false;
		}
	}
	return true;
}

/*
Pre-condition: rhs is a LongInt 
Post-condition: returns true if *this is not equal to rhs and false otherwise 
*/
bool LongInt::operator!=(const LongInt & rhs) const
{
	return !(*this == rhs);
}