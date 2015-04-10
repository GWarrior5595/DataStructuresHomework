#include "Array.h"
#include <iostream>
#include <stdio.h>

using namespace std;
Array::Array(): index(0), rindex(0){
	check = 0;
	myarray = new Word[150]; //initial size of words, will grow if array gets full
}
Array::~Array(){
	delete[] myarray;
}
void Array::add(char c){
	if((c <= 90 && c >= 65) || (c >= 97 && c <= 122 )){ //checks if c is a letter
		myarray[index].append(c);
		check = 1;
	} else if(check == 1){ //will change to the next word
		check = 0;
		if(myarray[index].getLength() >=4){
			if(index > 0){
				if(isRepeated(myarray[index], rindex) ){ // checks if word is repeated
					myarray[index].clearword();
					myarray[rindex].Frequency(); //updates the times repeated
				} else{
					myarray[index].Frequency(); //new word, so it has at least one occurrence
					index++;
				}
			} else{ // will only run for the first time, when index == 0
				myarray[index].Frequency();
				index++;
			}
		} else{   //will not count any word less than 4 characters
			myarray[index].clearword();
		}			
	} //if check is false that means there are two or more incorrect
	 // characters.
}
int Array::getIndex(){
	return index;
}
bool Array::isRepeated(Word A, int& index_){
	for(int i = 0; i < index; i++){
		if(myarray[i].compare(A)){
			index_ = i;
			return 1;                   //returns 1 if word is a repeat
		}								//index_ is the original word index							
	}
	return 0;
}
void Array::getMax(){
	int max = myarray[0].getFrequency();
	rindex = 0;
	for(int i = 1; i < index ;i++){
		if(max < myarray[i].getFrequency()){
			max = myarray[i].getFrequency();
			rindex = i;
		}
	}
	cout << myarray[rindex].c_str() << " = " << myarray[rindex].getFrequency();
	//printf("%s = %d \n", myarray[rindex].c_str(),myarray[rindex].getFrequency());
}
