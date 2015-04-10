/*
	This is the hw i've been doing. There are two text files in the zip. "list.txt" has the word "the" 18 times.
	text1.txt has the word "metallicmagnet" 14 times.
*/
#include "Array.h"
#include "Word.h"
/* Written by Victor M, Lopez Rodriguez    PS ID: 1261271
 Assignment 0: Given a text file of at max 150 words find the most repeated word.

 Written and compiled in Fedora 20.
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using namespace std;

int main(int narg, char** argv) {
	if (narg > 2) {
		printf("You entered too many arguments. Only 2 are needed.\n");
		exit(2);
	} else if(narg < 2){
		printf("Two arguments are needed. -executable- Filename.\n");
		exit(2);
	}
	Array list;
	char letter;

	ifstream read;
	read.open(argv[1]);
	if(!read){
		cout << "File could not be opened.\n";
	}
	while(read.get(letter)){
		list.add(letter);
	}
	list.add(' ');                               //for end of file
	if(list.getIndex() == 0){
		cout << " none " << endl;
	} else{
		list.getMax();
	}
	read.close();

	return 0;
	
}