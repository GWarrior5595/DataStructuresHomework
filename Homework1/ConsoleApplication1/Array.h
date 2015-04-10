#ifndef ARRAY_H
#define ARRAY_H

#include "Word.h"
class Array{
private:
	Word* myarray;
	unsigned short int index;
	bool check;
	int rindex; //index of the repeated word

public:
	Array();
	~Array();
	void add(char c);
	int getIndex();
	bool isRepeated(Word A, int&);
	void getMax();
	void increaseSize();
};

#endif