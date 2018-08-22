#pragma once
#include<vector>
using namespace std;
/*
// This is the header file for the Cannibals class which holds 
// the data members and member functions of the class.
//
// Deeksha Sharma 11/02/2017
*/

class Cannibals
{
public:
	//last char is L if boat is on left bank and is R if boat is on right bank
	char leftBank[7]; 
	char rightBank[6];
	//possibleMoves is a vector of vectors of chars that holds all possible combination of moves 
	vector<vector<char>> possibleMoves = {{'E', 0 },{ 'C', 0 },{ 'E','E' },{ 'C','C' },{ 'E','C' }}; 
	//this will hold all the moves that lead to the solution
	char solutionArray[40];

	Cannibals(); //default constructor 
	bool ValidState(char[]); //checks if banks are at a valid state
	bool MoveBoat(int); //moves people between banks 
	bool TryAMove(int); //the recursisve method 
	int SizeOfArray(char[]); //gets size of array 
	char PrintArray(char[]); //prints the array 
	bool Remove(int, char[]); //removes target char from targetArray 
	bool Add(int, char[]); //adds target to targetArray 
};

