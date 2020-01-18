/**************************************************************************************
 * Conway's Game of Life Using 2-D Arrays, Functions and Control Structures
 * @Author: Sukrut Patil | Intern ID 170026
 * Approach Followed: Bottom Up Approach
 * All Rights Reserved.
 * Created On: 2018-09-20
 **************************************************************************************/

#include <stdio.h>
#include <memory.h>
/*********************** Variable and Method Declarations *****************************/

void applyConway(); // Declare the routine to apply all the rules of Conway's Game on Each Cell of the Input Array
void print2DArray(); // Declare the routine to print any 2D integer array
void applyRules(); // Declare the routine which apply the four rules on provided pattern
void overPopulation(); // Declare the routine which will apply overpopulation rule
void underPopulation(); // Declare the routine which will apply underpopulation rule
void reproduction(); // Declare the routine which will apply reproduction rule
void survival(); // Declare the routine which will apply survival rule
int ROWS; // Total Number of Rows
int COLS; // Total Number of Columns
int indx; // Row Index which will be used for assigning Alive Cells
int cndx; // Column Index which will be used for assigning Alive Cells
int generations=1; // Variable which stores the ongoing number of generation being calculated

/*************************************************************************************
 * The following function generates the next generation of entered pattern
 * by applying the 4 rules of Conway's Game Of Life
 *************************************************************************************/
void applyConway(int pattern[ROWS][COLS],int r, int c) { // The function takes the initial array and
	//dimensions of that array as parameters
	int copy[r][c]; // Initialize a copy array for the next generation
	memset(copy,0,sizeof( int[ROWS][COLS])); // with all elements as 0

	printf("\n**********************************************************************************************\n");

	for (int i=0;i<r;i++) { // Iterate through each row
		int count=0; // Adjacent Alive Cell Counter

		for (int j=0; j<c;j++) {
			count =0; // Reset the counter

			/*** Special Condition 1: Top Row ***/
			if (i==0) {
				// Check the adjacent cells if they are alive or not and
				// if they are alive then increment the counter by 1 for each cell
				if (j!=0) { //If it is not the top-left cell
					if (pattern[i][j-1]==1) count++; //Left
					if (pattern[i+1][j-1]==1) count ++;// Down Left
				}

				if (pattern[i+1][j]==1) count++; //Down
				if (j!=c-1){ // If it is not the top right cell
					if (pattern[i][j+1]==1) count ++; //Right
					if (pattern[i+1][j+1]==1) count ++; //Down Right
				}

				applyRules(pattern,copy,count,i,j); // Apply the 4 rules on the current cell
				continue;
			}
			/*** Special Condition 2: Bottom Row ***/
			if (i==r-1) {
				if (pattern[i-1][j]==1) count++; //Up
				if (j!=c-1) { // If it is not the bottom right cell
					if (pattern[i][j+1]==1) count ++; //Right
					if (pattern[i-1][j+1]==1) count ++; //Up Right

				}
				if (j!=0) { // If it is not the bottom left cell
					if (pattern [i-1][j-1]==1) count ++; //Up Left
					if (pattern[i][j-1]==1) count++; //Left

				}

				applyRules(pattern,copy,count,i,j); // Apply the 4 rules on the current cell
				continue;
			}
			/*** Special Condition 3: Leftmost Column ***/
			if (j==0) {
				if (i!=0) { // If it is not the top left cell
					if (pattern[i-1][j]==1) count++; //Up
					if (pattern[i-1][j+1]==1) count ++; //Up Right
				}
				if (i!=r-1) { // If it is not the bottom left cell
					if (pattern[i+1][j]==1) count++; //Down
					if (pattern[i+1][j+1]==1) count ++; //Down Right
				}
				if (pattern[i][j+1]==1) count ++; //Right

				applyRules(pattern,copy,count,i,j); // Apply the 4 rules on the current cell
				continue;
			}
			/*** Special Condition 4: Rightmost Column ***/
			if (j==c-1) {

				if (i!=0) { // If it is not the top right cell
					if (pattern[i-1][j]==1) count++; //Up
					if (pattern [i-1][j-1]==1) count ++; //Up Left
				}
				if (i!=r-1) // If it is not the bottom right cell
				{
					if (pattern[i+1][j]==1) count++; //Down
					if (pattern[i+1][j-1]==1) count ++;// Down Left
				}
				if (pattern[i][j-1]==1) count++; //Left
				applyRules(pattern,copy,count,i,j); // Apply the 4 rules on the current cell
				continue;
			}

			/*** General Conditions ***/
			if (pattern[i][j-1]==1) count++; //Left
			if (pattern[i-1][j]==1) count++; //Up
			if (pattern[i+1][j]==1) count++; //Down
			if (pattern[i][j+1]==1) count ++; //Right
			if (pattern [i-1][j-1]==1) count ++; //Up Left
			if (pattern[i-1][j+1]==1) count ++; //Up Right
			if (pattern[i+1][j+1]==1) count ++; //Down Right
			if (pattern[i+1][j-1]==1) count ++;// Down Left

			applyRules(pattern,copy,count,i,j); // Apply the 4 rules on the current cell
			continue;
		}
	}
	fflush(stdout); //Clear the buffer stored in the console
	print2DArray(copy, r,c); // Print the next generation
	printf("\n**********************************************************************************************\n");
	memset(pattern,0,sizeof( int[ROWS][COLS])); //Clear the array and set all elements to 0 so that
	for (int i=0;i<r;i++) {
		for (int j=0;j<c;j++) {
			pattern[i][j]=copy[i][j]; // the next generation can be stored in it
		}
	}

	return;
}
/**********************************************************************************************************************
 *  The following function applies the four rules of Conway's Game of Life on the
 *  given cell and sets the values for the next generation array accordingly.
 *  The four rules are:
 *  1. Any live cell with fewer than two live neighbors dies, as if by under population. [Underpopulation Rule]
 * 	2. Any live cell with two or three live neighbors lives on to the next generation. [Survival Rule]
 * 	3. Any live cell with more than three live neighbors dies, as if by overpopulation. [Overpopulation Rule]
 * 	4. Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction. [Reproduction Rule]
 ***********************************************************************************************************************/
void applyRules(int pattern[ROWS][COLS], int copy[ROWS][COLS], int count,int i, int j) {
	underPopulation( pattern,  copy,  count,  i,  j);
	survival(pattern,  copy,  count,  i,  j);
	overPopulation( pattern,  copy,  count,  i,  j);
	reproduction( pattern,  copy,  count,  i,  j);
	// The following condition handles the garbage values which are thrown by C in case the above
	// rules not apply on the cell. Note that this condition applies in emergency (very rare conditions)
	// just in order to make sure that probability of getting a garbage values is 0.
	if (copy[i][j]!=0 && copy[i][j]!=1) copy[i][j]=pattern[i][j];
}

/*********************************************************************************
 * The Underpopulation Rule:
 * Any live cell with fewer than two live neighbors dies, as if by under population.
 *********************************************************************************/
void underPopulation(int pattern[ROWS][COLS], int copy[ROWS][COLS], int count, int i, int j) {
	if (count<2 && pattern [i][j]==1) { // If the cell is alive and has less than two alive neighbors,
		copy[i][j]=0;	 // it will die in next generation
		return;
	}
}

/*********************************************************************************************
 * The Survival Rule:
 *Any live cell with two or three live neighbors lives on to the next generation.
 *********************************************************************************************/
void survival(int pattern[ROWS][COLS], int copy[ROWS][COLS], int count, int i, int j) {
	if ((count ==2 || count==3)&&pattern[i][j]==1) { // If the cell is alive and has two or three alive neighbors,
		copy[i][j]=1;  // it will survive in next generation
		return;
	}
}

/*********************************************************************************
 * The Overpopulation Rule:
 * Any live cell with more than three live neighbors dies, as if by overpopulation.
 **********************************************************************************/
void overPopulation(int pattern[ROWS][COLS], int copy[ROWS][COLS], int count, int i, int j) {
	if (count>3 && pattern [i][j]==1)  { // If the cell is alive and has more than three alive neighbors,
		copy[i][j]=0; // it will die in next generation
		return;
	}
}

/*********************************************************************************************
 * The Reproduction Rule:
 * Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.
 *********************************************************************************************/
void reproduction(int pattern[ROWS][COLS], int copy[ROWS][COLS], int count, int i, int j) {
	//Special Conditions: Considering the game-plot as a sphere //
	if (i==ROWS-1) { //For the Last Row, reproduction rule will reproduce a cell in the first row
		if (pattern[i][j-1]==1 && pattern[i][j+1]==1) {
			copy[0][j]=1;
			return;
		}
	}
	if (i==0) { //For the First Row, reproduction rule will reproduce a cell in the last row
		if (pattern[i][j-1]==1 && pattern[i][j+1]==1) {
			copy[ROWS-1][j]=1;
			return;
		}
	}
	if (j==COLS-1) { //For the Last Column, reproduction rule will reproduce a cell in the first column
		if (pattern[i+1][j]==1 && pattern[i-1][j]==1) {
			copy[i][0]=1;
			return;
		}
	}
	if (j==0) { //For the First Column, reproduction rule will reproduce a cell in the last column
		if (pattern[i+1][j]==1&&pattern[i-1][j]==1) {
			copy[i][COLS-1]=1;
			return;
		}
	}

	if (count==3 && pattern [i][j]==0)  { // If the cell is dead and has exactly three live neighbors,
		copy[i][j]=1;  // it will live in next generation
		return;
	}
}

/***************************************************
 * Helper Function to Print Any Integer 2D Array
 ***************************************************/
void print2DArray(int arr[ROWS][COLS], int row, int col) { // The function takes the 2D-Array and its dimensions to print it accordingly
	for (int i=0; i<row;i++) { // Iterate through the rows
		fflush(stdout); //Clear the buffer stored in the console
		printf("\n"); // Move to the next line to print next row
		fflush(stdout); //Clear the buffer stored in the console
				for (int j=0;j<col;j++) { //Iterate through the columns
			fflush(stdout); //Clear the buffer stored in the console
			printf("  %d\t| ",arr[i][j]); //Print the cell present at location given by the current row and column index
		}
	}
	fflush(stdout); //Clear the buffer stored in the console

}

/***********************************************
 * Controller (Main) Function
 ***********************************************/
int main() {
	printf("CONWAY'S GAME OF LIFE BY JASKIRAT GREWAL (INTERN ID 170027)\n Run-time Version\n\n"); // Show the Author Details
	fflush(stdout); //Clear the buffer stored in the console
	printf("Enter no of rows: "); // Request the number of rows from the user
	fflush(stdout); //Clear the buffer stored in the console
	scanf("%d",&ROWS); // Store the number of rows in the respective variable address
	fflush(stdout); //Clear the buffer stored in the console
	printf("Enter no of columns: "); // Request the number of columns from the user
	fflush(stdout); //Clear the buffer stored in the console
	scanf("%d",&COLS); // Store the number of columns in the respective variable address
	int pattern [ROWS][COLS]; //Initialize an array of dimensions provided by user and
	memset(pattern,0,sizeof( int[ROWS][COLS])); // set all its elements as 0
	int p=1; // This is the variable which will be used to keep the loop running
	while(p==1) {
		fflush(stdout); //Clear the buffer stored in the console
		//Request the user to enter the location of cell where he wants to have an alive cell
		//For Example, if user inputs 2 1 then the cell given by pattern[2][1] is made alive (i.e. the value gets equal to 1)
		//Upon pressing e, the control will shift to the next part of the program, which is-finding the next generation(s)
		printf("Enter the cell index in <Row Index> <Col Index> Format where you want alive cells and press e when done:\n");
		fflush(stdout); //Clear the buffer stored in the console
		if(getchar()=='e') goto calculateGenerations;
		else {
			scanf("%d %d",&indx,&cndx); //Store the entered indexes to respective variable addresses
			if (indx>=ROWS || cndx >=COLS) {
				//If user enters an index which exceeds the dimensions of the game-board defined by user itself,
				// then show the error
				printf("*********** Error: Index out of bound! *************\n");
				continue;
			}
			pattern[indx][cndx]=1; // Make the cell, given by user-entered index, alive
			fflush(stdout); //Clear the buffer data of console
		}
	}
	calculateGenerations:
	for (int i=0; i<ROWS; i++) {						//This is a validating routine which
		for (int j=0; j<COLS; j++) {					//finds out garbage values in the array and
			if (pattern[i][j]==1) continue;				//replace them by 0
			pattern[i][j]=0;
		}
	}
	fflush(stdout); //Clear the buffer data of console
	printf("\n**********************************************************************************************\n");
	fflush(stdout); //Clear the buffer data of console
	printf("The input array is:");
	print2DArray(pattern, ROWS,COLS); // Show the input generation to the User
	fflush(stdout); //Clear the buffer data of console
	printf("\nEnter number of generations:\n"); //Request the number of generations from the user
	int requiredGenerations; // Variable to store the required number of generations
	fflush(stdout); //Clear the buffer data of console
	scanf("%d",&requiredGenerations); //Store the input in the respective variable address
	printf("\n**********************************************************************************************\n");
	fflush(stdout); //Clear the buffer data of console

	int blankArray[ROWS][COLS]; //An array of same dimensions containing
	memset(blankArray, 0, sizeof(int [ROWS][COLS])); // all elements as 0

	/*** Check if the array is blank (i.e. all elements are zero) and print the respective generations ***/
	int expectedZeroes = ROWS*COLS; // Total number of elements of an array is given by product of its total number of rows and columns
	int actualZeroes=0; // Counter for counting zeroes in the array

	while (generations<=requiredGenerations) { //Calculate each generation until required number of generation is reached
		actualZeroes =0; // Reset the zero counter
		for (int i=0; i<ROWS;i++) { //Iterate through rows
			for (int j=0;j<COLS;j++) { // and columns
				if (pattern[i][j]==0) actualZeroes++; // for counting zeroes
			}
		}
		if (actualZeroes==expectedZeroes) { // If all elements of array are zero
			//then, inform the user and break-out from the loop
			printf("Entirely Dead Generation Reached!!!\nGeneration %d is the last generation\n",generations-1);
			break;
		}
		printf("Generation %d:\n",generations); //Tell the user about the ongoing generation
		fflush(stdout); //Clear the buffer data of console
		applyConway(pattern,ROWS,COLS); // Print the next generation using Rules of Conway's Game

		generations++; // Move to next generation
	}
	fflush(stdout); //Clear the buffer data of console
	printf("This Game is Made By Sukrut Patil (Intern ID 170026)\nThanks for Playing!"); // Show Author Details in Credits
	printf("\n**********************************************************************************************\n");
	return 0; // Terminate the program with Succesful Exit Status(0)
}

