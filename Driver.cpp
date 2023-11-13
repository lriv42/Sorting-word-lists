/*
	Title: Driver.cpp
	Name: Liam Rivers
	Date 9/18/2023
	Purpose: demonstrate knowledge of algorithms
*/

#include "Timer.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct wordCount{
	string word;
	int count;
};

//testing out param comment
/*
	@param wordArray the structure containing words and their word count
	@param numWords the number of words brought in from the file, wordArray file size
	@return nothing-void
*/
void insertionSort(wordCount *wordArray, int numWords);
void bubbleSortReverse(wordCount *wordArray, int numWords);
void quicksort(wordCount *wordArray, int low, int high);
int partition(wordCount *wordArray, int left, int right);

int main()
{
	wordCount* wordArray = new wordCount[150000]; //wordArray is array
	int numWords = 0; //array size
	string temp;
	int num;
	
	ofstream outfile;
	ifstream infile;

	time_t start, end;
	char filename[50];
	cout << "\nWhich file are you opening?\n";
	cin >> filename;
	infile.open(filename);
	
	if(!infile)
	{
		cout << "\nSorry, I couldn't find that file.\n";
		return 1;
	}

	while(getline(infile, temp) && numWords != 150000)
	{
		wordArray[numWords].word = temp;
		infile >> num;
		infile.ignore();
		wordArray[numWords].count = num;
		numWords++;
	}
	cout << "you've read in " << numWords << " words.\n";

	//sort the songs using insertion sort and print them out to the text file sortFileInsertion.txt
	start = getTime(); //Starts timer.   

	//LOOK!!!!  CALL THE INSERTION SORT ALGORITHM HERE
	insertionSort(wordArray, numWords); //numWords does not need to be modified for the loop in this function

	end = getTime(); //Ends timer.
	outfile.open("sortFileInsertion.txt");
	cout << "\nInsertion sort: " << totalTime(start, end) << " seconds\n\n";
	for(int x=0; x<numWords; x++)
	{
		outfile << wordArray[x].word << " : " << wordArray[x].count << endl;
	}
	outfile.close();

	//sort the songs in reverse order using bubble sort & print them out to the text file sortFileReverseBubble.txt
	start = getTime(); //Starts timer. 

	//LOOK!!!!  CALL THE REVERSE BUBBLE SORT ALGORITHM HERE
	bubbleSortReverse(wordArray, numWords); //numWords will be decreased inside function

	end = getTime(); //Ends timer.
	outfile.open("sortFileReverseBubble.txt");
	cout << "\nReverse bubble sort: " << totalTime(start, end) << " seconds\n\n";
	for(int x=0; x<numWords; x++)
	{
		outfile << wordArray[x].word << " : " << wordArray[x].count << endl;
	}
	outfile.close();

	//sort the songs with quick sort & print them out to sortFileQuick.txt
	start = getTime(); //Starts timer. 
	
	//LOOK!!!!  CALL THE QUICKSORT ALGORITHM HERE
	quicksort(wordArray, 0, numWords -1); //numWords - 1 so we dont go out of bounds

	end = getTime(); //Ends timer.
	cout << "\nQuicksort: " << totalTime(start, end) << " seconds\n\n";
	outfile.open("sortFileQuick.txt");
	for(int x=0; x<numWords; x++)
	{
		outfile << wordArray[x].word << " : " << wordArray[x].count << endl;
	}
	outfile.close();
	
	delete [] wordArray;
	return 0;
}

//LOOK!  WRITE YOUR INSERTION SORT FUNCTION HERE

void insertionSort(wordCount* wordArray, int numWords){
	int holder; // holds the element we are sorting
	string wordHolder;
	int pos; //position of the element being sorted

	for(int i = 1; i < numWords; i++){ //going through the array
		holder = wordArray[i].count; //assigns the element to be sorted to holder
		wordHolder = wordArray[i].word;
		pos = i-1; //start point of comparison
		while(pos >= 0 && wordArray[pos].count > holder){ //so long as the position is inside of the array and the element at position is greater than the ...
			wordArray[pos + 1].count = wordArray[pos].count; //element being sorted, move the elements in array up and ...
			wordArray[pos + 1].word = wordArray[pos].word;
			pos = pos-1; //move the position marker down
		}
		wordArray[pos + 1].count = holder; //places the element into proper position
		wordArray[pos + 1].word = wordHolder;
	}
}

//LOOK!  WRITE YOUR REVERSE BUBBLE SORT FUNCTION HERE
void bubbleSortReverse(wordCount *wordArray, int numWords){
	string wordHolder; //holds the array content to be swapped later
	int holder;

	for(int elementCount = (numWords - 1); elementCount > 0; elementCount--){ //bubblesort goes through however many elements there are
		for(int i = 0; i < elementCount; i ++){//going through the array
			if(wordArray[i].count < wordArray[i + 1].count){ // if occurances greater than word we are checking

				wordHolder = wordArray[i+1].word;
				holder = wordArray[i+1].count; //store values in temp variables

				wordArray[i + 1].count = wordArray[i].count; //move elements up
				wordArray[i + 1].word = wordArray[i].word;

				wordArray[i].count = holder;//places the greater element below the compared element
				wordArray[i].word = wordHolder;
			}
		}
	}
}

//LOOK!  WRITE YOUR RECURSIVE QUICK SORT FUNCTION HERE
void quicksort(wordCount *wordArray, int low, int high){

	//low and high are sent into quicksort again
	int pivot = 0; //initializes the pivot
	if(low >= high){
		return; //means the sort is complete
	}

	pivot = partition(wordArray, low, high); //making the partition
	quicksort(wordArray, low, pivot); //recursively calls to make partitions for left half
	quicksort(wordArray, pivot + 1, high); //recursively calls to make partitions for the right half
}


//LOOK!  WRITE YOUR PARTITION FUNCTION HERE
int partition(wordCount *wordArray, int left, int right){

	int arrCheck; //where we want to check an element against
	int tempCount; //holds the count number for swap
	string tempWord; // holds the word for swap


	arrCheck = wordArray[left].count; //assigns the element to check against

	int l = left-1; //setting the boundaries correctly
	int r = right +1;

	//this while loop will make all values ascend not descend by count value
	while(l > r){ 
		do{
			r--; //keep moving the right marker down until we find a false value (right side less than the check)
		}while(wordArray[r].count > arrCheck);
		do{
			l++; //now we move the left marker up until we find a false value (left value greater than check)
		}while(wordArray[l].count < arrCheck);

		if(l < r){ //change to boolean

			tempCount = wordArray[l].count; //we store one of the variables, for this program the left marker variable
			tempWord = wordArray[l].word;

			wordArray[l].count = wordArray[r].count; //replace the left variable with the right variable
			wordArray[l].word = wordArray[r].word;

			wordArray[r].count = tempCount; //now we take the left variable we stored earlier and assign it to ...
			wordArray[r].word = tempWord; //the right variable, completing the swap of variables

		}
	}
	return r;
}