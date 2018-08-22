#include<iostream>
#include "Sharma_cannibals.h"

/*
// This class holds the recursive TryAMove function that finds the solution 
// to the explorers and cannibals problem. 
//
// Deeksha Sharma 11/02/2017
*/

using namespace std;

/*
This constructor initializes all the elements of the rightBank and solutionArray to 0. 
It initializes the leftBank array so it hold the following: {'E', 'E', 'E', 'C', 'C', 'C', 'L'}
*/
Cannibals::Cannibals()
{
	for (int i = 0; i < 6; i++)
	{
		rightBank[i] = 0;
	}
	for (int i = 0; i < 40; i++)
	{
		solutionArray[i] = 0;
	}
	for (int i = 0; i < 7; i++)
	{
		if (i < 3) leftBank[i] = 'E';
		else if (i < 6) leftBank[i] = 'C';
		else leftBank[6] = 'L';
	}
}

/*
Pre-condition: target is a valid char array 
Post-condition: returns true if number of explorers is more than number of
cannibals in the array passed in, false otherwise. 
*/
bool Cannibals::ValidState(char target[])
{ 
	int numC = 0; //will keep track of the number of Cs. 
	int numE = 0; //will keep track of the number of Es.
	for (int i = 0; i < SizeOfArray(target); i++)
	{ //this will loop through the array and keep track of the number of Es and Cs
		if (target[i] == 'E') numE++;
		else numC++;
	}
	if (numC > numE) return false;
	return true;
}

/*
Pre-condition: target is a valid char array 
Post-condition: returns the number of elements in the array 
*/
int Cannibals::SizeOfArray(char target[])
{
	int numElements = 0;
	for (int i = 0; i < SizeOfArray(target); i++)
	{
		if (target[i] != 0) numElements++;
	}
	return numElements;
}

/*
Pre-condition: target is a valid char array 
Post-condition: prints out all the elements in the array on one line 
*/
char Cannibals::PrintArray(char target[])
{
	//prints the target array 
	for (int i = 0; i < SizeOfArray(target); i++)
	{
		cout << target[i];
	}
	cout << endl;
}

/*
Pre-condition: assumed that target is a valid char vector, and targetArray is
a valid char array
Post-condition: returns true if the chars in the target vector passed 
in were found in targetArray and successfully removed. 
*/
bool Cannibals::Remove(int targetIndex, char targetArray[])
{
	bool sucRemove = false; //bool to keep track of whether the remove was successful 
	if (possibleMoves[targetIndex][1] != 0)
	{ //the following is executed if the target char vector passed in has 2 chars 
		for (int i = 0; i < SizeOfArray(targetArray); i++)
		{ //removes target in index 1 of vector if target is found in targetArray 
			if (targetArray[i] == possibleMoves[targetIndex][1])
			{
				targetArray[i] = 0;
				sucRemove = true;
			}
			else sucRemove = false;
		}
	}
	for (int i = 0; i < SizeOfArray(targetArray); i++)
	{ //removes target in index 0 of vector if target is found in targetArray 
		if (targetArray[i] == possibleMoves[targetIndex][0])
		{
			targetArray[i] = 0;
			sucRemove = true;
		}
		else sucRemove = false;
	}
	return sucRemove;
}

/*
Pre-condition: assumed that target is a valid char vector, and targetArray is 
a valid char array
Post-condition: returns true if the chars in the target vector passed in were
found in targetArray and successfully added.
*/
 bool Cannibals::Add(int targetIndex, char targetArray[])
{
	 bool sucAdd = false; //bool to keep track of whether the addition was successful 
	 if (possibleMoves[targetIndex][1] != 0)
	 { //the following is executed if the target char vector passed in has 2 chars 
		 for (int i = 0; i < SizeOfArray(targetArray); i++)
		 { //adds target in index 1 of vector in first uninitialized index of targetArray
			 if (targetArray[i] == 0)
			 {
				 targetArray[i] = possibleMoves[targetIndex][1];
				 sucAdd = true;
			 }
			 else sucAdd = false;
		 }
	 }
	 for (int i = 0; i < SizeOfArray(targetArray); i++)
	 { //adds target in index 0 of vector in first uninitialized index of targetArray
		 if (targetArray[i] == 0)
		 {
			 targetArray[i] = possibleMoves[targetIndex][0];
			 sucAdd = true;
		 }
		 else sucAdd = false;
	 }
	 return sucAdd;
}

/*
Pre-condition: assumed that targetIndex is a valid, initialzied int
Post-condition: returns true if the char vector at targetIndex was able to 
be moved from the bank the boat was on to the other bank.
*/
bool Cannibals::MoveBoat(int targetIndex) 
{
	// the following is executed if last char in leftBank array is L then the boat is on leftBank 
	if (leftBank[6] == 'L')
	{ 
		//following is executed if remove of targetIndex of possibleMoves vector from leftBank is successful 
		if (Remove(targetIndex, leftBank))
		{ 
			leftBank[6] = 'R';
			return Add(targetIndex, rightBank);
		}
	}
	else
	{
		//following is executed if remove of targetIndex of possibleMoves vector from rightBank is successful 
		if (Remove(targetIndex, rightBank))
		{
			leftBank[6] = 'L';
			return Add(targetIndex, leftBank); 
		}
	}
	return false;
}

/*
Pre-condition: assumed that targetIndex is a valid, initialzied int
Post-condition: returns true if a successful solution was found and false otherwise 
*/
bool Cannibals::TryAMove(int targetIndex) 
{
	cout << "very beginning of TryAMove" << endl; ////test output for code
	//following is executed if the move of targetIndex is successful 
	if (MoveBoat(targetIndex))
	{
		cout << targetIndex << ": in TryAMove after MoveBoat is called" << endl; ////test output for code
		//base case
		if (SizeOfArray(rightBank) == 6) 
		{
			return true;
		}

		// if both banks are at a valid state the for loop will try all possible moves using recursive calls 
		if (ValidState(leftBank) && ValidState(rightBank))
		{
			for (int i = 0; i < possibleMoves.size(); i++)
			{ 
				if (possibleMoves[i] == possibleMoves[targetIndex]) continue;
				if (TryAMove(i))
				{
					cout << i << ": TryAMove returns true" << endl; //test output for code 
					return Add(i, solutionArray); 
				}
			}
		}
		MoveBoat(targetIndex); //if at an invalid state this reset arrays to previous valid state
	}
	//if either bank is not at a valid state
	return false;
}

