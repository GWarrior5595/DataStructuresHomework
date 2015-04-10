#ifndef WORD_H
#define WORD_H

class Word{
private:
	char data[50];
	unsigned short int length;
	unsigned short int frequency;
	
public:
	Word();
	void append(char c) ;
	const char* c_str();
	int getLength();
	void Frequency();
	int getFrequency();
	void clearword();
	bool compare(Word A);
};
#endif