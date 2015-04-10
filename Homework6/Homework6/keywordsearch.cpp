/* Name: Erphun Ranjbar
* Date: 11/12/2014
*
* Enviroment:
*    Written and compiled in Ubuntu terminal
*
* If ran in a terminal use command:
*  "keywordsearch.cpp commands.txt"
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
#include <queue>
using namespace std;

string toLowerCase(string temp){
	string lowered = "";
	for (int i = 0; i < temp.length(); i++){
		lowered += tolower(temp[i]);
	}
	return lowered;
}

class nodeType{
public:
	string info;
	nodeType *next;
	nodeType *prev;
};

class Nodes{
public:
	nodeType *start = NULL, *temp1, *temp2;
	void placeintolist(string word){
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

	void removeDuplicatesInList(){
		struct nodeType *duplicate;
		temp1 = new nodeType;
		temp2 = new nodeType;
		temp1 = start;
		while (temp1 != NULL && temp1->next != NULL){
			temp2 = temp1;
			while (temp2->next != NULL){
				if (temp1->info == temp2->next->info){
					duplicate = temp2->next;
					temp2->next = temp2->next->next;
					free(duplicate);
				}
				else
					temp2 = temp2->next;
			}
			temp1 = temp1->next;
		}
	}

	void UnionTestA(struct nodeType* head){
		if (head == NULL)
			return;
		else{
			placeintolist(head->info);
			UnionTestA(head->next);
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
};

class MapADT {
public:
	MapADT();
	MapADT(string filename);

	string find(const string& key);
	void insert(const string& key, const string& value);
	string remove(const string& key);

	void print();
protected:
	unsigned int hash(const string& key);

	int find_index(const string& key, bool override_duplicated_key);

	const static unsigned int size_max = 10000;
	string keys[size_max];
	string values[size_max];
};

MapADT::MapADT() {
	for (int i = 0; i < size_max; i++) {
		keys[i] = string();
		values[i] = string();
	}
}

unsigned int MapADT::hash(const string& k)
{
	unsigned int value = 0;
	for (int i = 0; i < k.length(); i++)
		value = 37 * value + k[i];
	return value;
}

int MapADT::find_index(const string& key, bool override_duplicate_key = true) {
	unsigned int h = hash(key) % size_max, offset = 0, index;
	while (offset < size_max) {
		index = (h + offset) % size_max;

		if (keys[index].empty() ||
			(override_duplicate_key && keys[index] == key))
			return index;

		offset++;
	}
	return -1;
}

class DictionaryADT : public MapADT {
public:
	DictionaryADT() : MapADT() {}
	DictionaryADT(string filename);

	void insert(const string& key, const string& value);
	queue<string> find_all(const string& key);
	queue<string> remove(const string& key);
};

void DictionaryADT::insert(const string& key, const string& value) {
	int index = find_index(key, false);
	if (index == -1) {
		return;
	}
	keys[index] = key;
	values[index] = value;
}

queue<string> DictionaryADT::find_all(const string& key) {
	queue<string> result;
	string temp = toLowerCase(key);
	for (int i = 0; i < size_max; i++)
		if (toLowerCase(keys[i]) == temp)
			result.push(values[i]);
	return result;
}

queue<string> DictionaryADT::remove(const string& key) {
	queue<string> result;
	for (int i = 0; i < size_max; i++)
		if (keys[i] == key) {
		result.push(values[i]);
		keys[i].clear();
		values[i].clear();
		}
	return result;
}

int readFile(Nodes &Array, string fileName) {
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
		Array.placeintolist(toLowerCase(word));
	}
	read.close();
}

void QuickSortList(nodeType *pLeft, nodeType *pRight){
	nodeType *pStart;
	nodeType *pCurrent;
	string nCopyInteger;
	if (pLeft == pRight) return;
	pStart = pLeft;
	pCurrent = pStart->next;
	while (1){
		if (pStart->info < pCurrent->info){
			nCopyInteger = pCurrent->info;
			pCurrent->info = pStart->info;
			pStart->info = nCopyInteger;
		}
		if (pCurrent == pRight) break;
		pCurrent = pCurrent->next;
	}
	nCopyInteger = pLeft->info;
	pLeft->info = pCurrent->info;
	pCurrent->info = nCopyInteger;
	nodeType *pOldCurrent = pCurrent;
	pCurrent = pCurrent->prev;
	if (pCurrent != NULL){
		if ((pLeft->prev != pCurrent) && (pCurrent->next != pLeft))
			QuickSortList(pLeft, pCurrent);
	}
	pCurrent = pOldCurrent;
	pCurrent = pCurrent->next;
	if (pCurrent != NULL){
		if ((pCurrent->prev != pRight) && (pRight->next != pCurrent))
			QuickSortList(pCurrent, pRight);
	}
}

int main(int argv, char **argc){
	ifstream readMyFile;
	string line;
	string word;
	string command;
	string gello;
	string _command;
	string nums;
	Nodes removelist;
	bool opened = true;
	DictionaryADT d;
	readMyFile.open(argc[1]);
	if (!readMyFile.is_open()){
		return 0;
	}
	while (getline(readMyFile, line)){
		istringstream sst(line, istringstream::in);
		sst >> command;
		if (!strcmp("Stop_word", command.c_str())){
			sst >> command;
			readFile(removelist, command);
		}
		else if (!strcmp("Add_doc", command.c_str())){
			ifstream readDoc;
			sst >> gello;
			readDoc.open(gello.c_str());
			if (!readDoc.is_open()){
				opened = false;
			}
			if (opened){
				while (readDoc >> word){
					for (int i = 0; i < word.length(); i++){
						if (ispunct(word[i])) {
							word.erase(i--, 1);
						}
					}
					d.insert(toLowerCase(word), gello);
				}
				struct nodeType* head = removelist.GetHead();
				while (head != NULL){
					d.remove(head->info);
					head = head->next;
				}
			}
		}
		else if (!strcmp("Search", command.c_str())){
			sst >> nums;
			int numofwords = atoi(nums.c_str());
			int hold = 0;
			int counter = 1;
			bool sweg;
			Nodes tempsadded;
			while (hold < numofwords){
				sst >> _command;
				Nodes temps;
				queue<string> k1v = d.find_all(toLowerCase(_command));
				while (!k1v.empty()) {
					temps.placeintolist(k1v.front());
					if (numofwords == 1){
						cout << k1v.front() << endl;
					}
					k1v.pop();
				}
				tempsadded.UnionTestA(temps.GetHead());
				nodeType* okay = temps.GetHead();
				while (okay){
					nodeType* old = okay;
					okay = okay->next;
					delete old;
				}
				hold++;
			}
			if (numofwords > 1){
				QuickSortList(tempsadded.GetHead(), tempsadded.getTail());
				nodeType* alright = tempsadded.GetHead();
				while (alright->next != NULL){
					if (alright->info == alright->next->info){
						counter++;
					}

					else{
						counter = 1;
					}
					if (counter == numofwords){
						cout << alright->info << endl;
						counter = 1;
					}
					alright = alright->next;
				}
			}
			cout << endl;
			nodeType* okay = tempsadded.GetHead();
			while (okay){
				nodeType* old = okay;
				okay = okay->next;
				delete old;
			}
		}
	}
}