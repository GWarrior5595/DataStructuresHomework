#include "Word.h"
#include <ctype.h>

Word::Word():length(0), frequency(0){}

void Word::append(char c){       //adds character c to char array
	data[length] = tolower(c); 
	length++;
}
const char* Word::c_str(){ // returns the word
	return data;
}
int Word::getLength(){
	return length;
}
void Word::Frequency(){
	frequency++;
}
int Word::getFrequency(){
	return frequency;
}
void Word::clearword(){
	for(int i = 0; i < length; i++){
		data[i] = '\0';
	}
	length = 0;
}
bool Word::compare(Word A){
	if( length == A.getLength()){
		for(int i = 0; i < length; i++){
			if(data[i] != A.data[i]){
				return 0;
			}	
		}
		return 1;   //words are equal, i.e. repeated
	} else{
		return 0;   
	}
}
