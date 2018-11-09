#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;
//Function to produce sumMatrix 
long long int** createSumMatrix(long long int **sumMatrix,int rows,int columns,int **timberForest){
	sumMatrix = new long long int*[rows+1];

	for(int i = 0; i <= rows; i++){
		sumMatrix[i] = new long long int[columns+1];
		for(int j = 0; j <= columns; j++){
			if(i == 0 ||j == 0)
				sumMatrix[i][j] = 0;
			else{
				sumMatrix[i][j] = timberForest[i-1][j-1] + sumMatrix[i-1][j] + sumMatrix[i][j-1] - sumMatrix[i-1][j-1];
			}
		}
	}
	return sumMatrix;
}
//Function containing the main dynamic programming algorithm to produce answer
void executeAlgorithm(long long int **sumMatrix,long long int **plotPoints,long long int numberOfInputPlots,int **timberForest,int rows,int columns){
	//Variables to store each index of given pair of points 
	long long int x1;
	long long int y1;
	long long int x2;
	long long int y2;
	//for loop for calculating sum of the volume of trees in every given rectangular pieces of land
	for(long long int i = 0; i < numberOfInputPlots; i++){
		x1 = plotPoints[i][0];
		y1 = plotPoints[i][1];
		x2 = plotPoints[i][2];
		y2 = plotPoints[i][3];
		long long int answer = 0;
		//Checking bad inputs 
		if((x1 > x2 || y1 > y2) || (x1 <= 0 || x2 <= 0 || y1 <= 0 || y2 <= 0)|| (x1 > rows || x2 > rows || y1 > columns || y2 > columns)){
			cout << "Wrong input plot points!" << endl;
		}
		else{
			answer = sumMatrix[x2][y2] - sumMatrix[x2][y1-1] - sumMatrix[x1-1][y2] + sumMatrix[x1-1][y1-1]; 
			cout << answer << endl;
		}
	}
}
//Main function
int main(int argc,char *argv[]){
	//Variables
	int **timberForest = NULL; //Given timber forest - 2d array
	int rows; //Number of rows
	int columns; //Number of columns
	long long int numberOfInputPlots; //Number of given pair of plot points
	long long int **plotPoints = NULL; //Given pair of plot points - 2d array
	long long int **sumMatrix = NULL; //sumMatrix 

	//Taking input from given input file using command line and storing the input
	ifstream fileIn(argv[1]);	
	fileIn >> rows >> columns;
	timberForest = new int*[rows];

	for(int i = 0; i < rows; i++){
		timberForest[i] = new int[columns];
		int value = 0;
		for(int j = 0; j < columns; j++){
			fileIn >> value;
			timberForest[i][j] = value;
		}
	}

	fileIn >> numberOfInputPlots;
	if(numberOfInputPlots > 0){
		plotPoints = new long long int*[numberOfInputPlots];

		for(long long int i = 0; i < numberOfInputPlots; i++){
			plotPoints[i] = new long long int[4];
			long long int value = 0;
			for(long long int j = 0; j < 4; j++){
				fileIn >> value;
				plotPoints[i][j] = value;
			}
		}

		//Calling the required function for producing sumMatrix
		sumMatrix = createSumMatrix(sumMatrix,rows,columns,timberForest);

		//Calling the required function for producing answer given the input
		executeAlgorithm(sumMatrix,plotPoints,numberOfInputPlots,timberForest,rows,columns);
	}
	else if(numberOfInputPlots == 0){
		//Nothing is printed 
	}
	else{
		cout << "Wrong input!" << endl;
	}
	fileIn.close();
	return 0;
}
