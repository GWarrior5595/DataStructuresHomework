/* Name: Erphun Ranjbar
* Date: 10/28/2014
*
* Enviroment:
*    Written and compiled in Ubuntu terminal
*
* If ran in a terminal use command:
*  "spellchecker.cpp dictionary.txt input.txt"
*
*/

#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <string>
#include <stdio.h>
using namespace std;

string toLowerCase(string temp){
	string lowered = "";
	for (int i = 0; i < temp.length(); i++){
		lowered += tolower(temp[i]);
	}
	return lowered;
}

void binarySearchh(string array[], int lowerbound, int upperbound, string key){
	int position;
	string temp = toLowerCase(key);
	// To start, find the subscript of the middle position.
	position = (lowerbound + upperbound) / 2;

	while (array[position] != temp && (lowerbound <= upperbound)){
		if (array[position] > temp){               // If the string is > key, ..
			upperbound = position - 1;				// decrease position by one.
		}
		else{                                                        // Else, increase position by one.
			lowerbound = position + 1;
		}
		position = (lowerbound + upperbound) / 2;
	}
	if (lowerbound <= upperbound){
	
	}
	else
		cout << key << endl;
	return;  // you may also consider returning the subscript
}


bool isopen = true;
class nodeType{
public:
	string info;
	nodeType *next;
	nodeType *prev;
};

class NodeArray {
private:
public:
	nodeType *start = NULL, *temp1, *temp2, *temp3;
	//Recursive printing forward
	//Recursion
	void printForwards(struct nodeType* head) {
		if (isopen){
			if (head == NULL)
				return;
			cout << head->info << endl;
			if ((head->next) == NULL)
				return;
			else
				printForwards(head->next);
		}
	}

	//Recursive printing backward
	//Recursion
	void printReverse(struct nodeType* head){
		if (isopen){
			if (head == NULL)
				return;
			printReverse(head->next);
			cout << head->info << endl;
		}
	}

	void placeintolist(string word){
		if (isopen){
			temp1 = new nodeType;
			temp1->info = word;
			if (start == NULL){
				start = temp1;
				temp1->next = NULL;
				temp1->prev = NULL;
			}
			else{
				temp2 = start;
				while (temp2->next != NULL)
					temp2 = temp2->next;
				temp2->next = temp1;
				temp1->prev = temp2;
				temp1->next = NULL;
			}
		}
	}
	struct nodeType* GetHead(){
		return start;
	}

	struct nodeType *getTail(){
		nodeType* cur = start;
		while (cur != NULL && cur->next != NULL)
			cur = cur->next;
		return cur;
	}
	void setHead(nodeType* A){
		start = A;
	}

	void printNotInDictionary(struct nodeType* diction, struct nodeType* doc){
		nodeType* a = diction;
		nodeType* b = doc;
		nodeType* c = diction;
		nodeType* d = doc;
		int count = 0;
		while (a != NULL){
			a = a->next;
			count++;
		}
		//cout << count << endl;
		string *dictarray = new string[count];
		for (int i = 0; i < count; i++){
			dictarray[i] = c->info;
			c = c->next;
		}
		int counter = 0;
		while (b != NULL){
			b = b->next;
			counter++;
		}
		//cout << counter << endl;
		string *docarray = new string[counter];
		for (int i = 0; i < counter; i++){
			docarray[i]=d->info;
			d = d->next;
		}
		while (doc){
			nodeType* old = doc;
			doc = doc->next;
			delete old;
		}
		while (diction){
			nodeType* old = diction;
			diction = diction->next;
			delete old;
		}
		int counts = 0;
		for (int i = 0; i < counter; i ++){
			binarySearchh(dictarray, 0, count, docarray[i]);
		}
	}
};

void removeDuplicates(struct nodeType* head){
	struct nodeType* current = head;
	struct nodeType* next_next;
	if (current == NULL)
		return;
	while (current->next != NULL){
		if (current->info == current->next->info){
			next_next = current->next->next;
			free(current->next);
			current->next = next_next;
		}
		else{
			current = current->next;
		}
	}
}

/*void sortNodes(nodeType * ptr) {
	string temp = "";
	nodeType * curr;
	for (bool didSwap = true; didSwap;) {
		didSwap = false;
		for (curr = ptr; curr->next != NULL; curr = curr->next) {
			if (curr->info > curr->next->info) {
				temp = curr->info;
				curr->info = curr->next->info;
				curr->next->info = temp;
				didSwap = true;
			}
		}
	}
}*/

int readFile(NodeArray &Array, string fileName) {
	ifstream read;
	string word;
	read.open(fileName.c_str());
	if (read.fail()){
		return 0;
	}
	while (read >> word){
		for (int i = 0; i < word.length(); i++){
			if (ispunct(word[i])) {
				word.erase(i--, 1);
			}
		}
		Array.placeintolist(word);
	}
	read.close();
}

void QuickSortList(nodeType *pLeft, nodeType *pRight){
	nodeType *pStart;
	nodeType *pCurrent;
	string nCopyInteger;
	// If the left and right pointers are the same, then return
	if (pLeft == pRight) return;
	// Set the Start and the Current item pointers
	pStart = pLeft;
	pCurrent = pStart->next;
	// Loop forever (well until we get to the right)
	while (1){
		// If the start item is less then the right
		if (pStart->info < pCurrent->info){
			// Swap the items
			nCopyInteger = pCurrent->info;
			pCurrent->info = pStart->info;
			pStart->info = nCopyInteger;
		}

		// Check if we have reached the right end
		if (pCurrent == pRight) break;
		// Move to the next item in the list
		pCurrent = pCurrent->next;
	}

	// Swap the First and Current items
	nCopyInteger = pLeft->info;
	pLeft->info = pCurrent->info;
	pCurrent->info = nCopyInteger;
	// Save this Current item
	nodeType *pOldCurrent = pCurrent;
	// Check if we need to sort the left hand size of the Current point
	pCurrent = pCurrent->prev;
	if (pCurrent != NULL){
		if ((pLeft->prev != pCurrent) && (pCurrent->next != pLeft))
			QuickSortList(pLeft, pCurrent);
	}

	// Check if we need to sort the right hand size of the Current point
	pCurrent = pOldCurrent;
	pCurrent = pCurrent->next;
	if (pCurrent != NULL){
		if ((pCurrent->prev != pRight) && (pRight->next != pCurrent))
			QuickSortList(pCurrent, pRight);
	}
}


int main(int argv, char **argc){
	NodeArray *myArray = new NodeArray[2];
	struct nodeType* a = NULL;
	struct nodeType* b = NULL;
	//NodeArray *inputfile = new NodeArray;
	readFile(myArray[0], argc[1]); //dictionaryfile
	readFile(myArray[1], argc[2]); //inputfile
	QuickSortList(myArray[0].GetHead(), myArray[0].getTail());
	QuickSortList(myArray[1].GetHead(), myArray[1].getTail());
	removeDuplicates(myArray[0].GetHead());
	removeDuplicates(myArray[1].GetHead());
	myArray[0].printNotInDictionary(myArray[0].GetHead(), myArray[1].GetHead());
}