#include <fstream>
#include <iostream>
#include <cstring>
#include <cctype>
#include <sstream>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Node {
public:
	string word;
	Node* right;
	Node* left;
	Node(string _word): word(_word), right(NULL), left(NULL) {}
};
class NodeArray {
private:
	Node* root;
	Node* end;
	int length;
public:
	NodeArray(): root(NULL), end(NULL) ,length(0){}
	void push_back(string _word) {
		length++;
		if (root == NULL) {
			root = new Node(_word);
			end = root;
			return;
		}
		Node* temp = new Node(_word);
		end->right = temp;
		temp->left	= end;
		end = temp;
	}
	int getlength(){
		return length;
	}
	void print_forward() {
		Node* crt = root;
		if(length == 0){
			cout <<"list is empty \n";
		} else{
			while (crt != NULL) {
				cout << crt->word << "\n";
				crt = crt->right;
			}
		}
	
	}
	void insert(string Word, string chosen){
		int count = 0;
		Node *crt = root;
		Node *New;                                                                                                               
		Node *next;
		while(strcmp(chosen.c_str(), (crt->word).c_str()) != 0){    
			if(crt->right == NULL){
				return;
			}   
			crt = crt->right;
		} 
		if(crt->right == NULL){
			push_back(Word);
		} else{
			New = new Node(Word);
			next = crt->right;
			crt->right = New;
			New-> left = crt;
			New->right = next;
			next->left = New;
			length++;
		}
	}
	void deleteword(string Word){
		int count = 0;
		Node* crt = root;
		Node* temp;
		Node* temp2;
		while(strcmp(Word.c_str(), (crt->word).c_str()) != 0){
			if(crt->right == NULL){
				return;
			}
			crt = crt->right;
		
		}

		if(crt->left == NULL){              // if it is the first word
			if(length == 1){
				root->right = NULL;
				end->left = NULL;
				root = NULL;
				end = NULL;
				delete crt;
				length--;
			}else{
				crt->right->left= NULL ;
				root = crt->right;
				delete crt;
				length--;
			}
			
		} else if(crt->right == NULL){       // if it is the last word
			crt->left->right = NULL;
			end = crt->left;
			delete crt;
			length--;
		} else{                              //anywhere in the middle of the list
			temp = crt->right;
			temp2 = crt->left;
			temp->left = temp2;
			temp2->right = temp;
			length--;
			delete crt;
		}
	}
	void print_backward(){
		Node *crt = end;
		if(length == 0){
			cout << "Linked list is empty.\n";
		} else{
			while(crt != NULL){
				cout << crt->word <<"\n";
				crt = crt->left;
			}
		}
		
	}
	string& operator[] (int i) {
     	int crtIndex = 0;
		Node *crt = root;
		while(crtIndex != i){
			crtIndex++;
			crt = crt->right;
		}
		return (crt->word);
    }
    const string& operator[] (int i) const {
       	int crtIndex = 0;
		Node *crt = root;
		while(crtIndex != i){
			crtIndex++;
			crt = crt->right;
		}
		return (crt->word);
    }


};
void readfile(NodeArray &myArray, string file){
	ifstream read; 
	string word;
	read.open(file.c_str());
	if(read.fail()){
		cout << "File could not be found\n";
		return;
	}
	while(read >> word){
		for (int i = 0; i < word.length(); i++){
	        if (ispunct(word[i])) {
	            word.erase(i--, 1);
	        }
	    }
	    myArray.push_back(word);
	}
	read.close();
}
int main(int argv, char **argc){
	NodeArray myArray;
	ifstream read;
	string line;
	string next;
	string next_;
	read.open(argc[1]);
	if(read.fail()){
		cout << "File could not be found\n";
		exit(1);
	}
	while(getline(read, line)){
		istringstream sst(line, istringstream::in);
		sst >> next;
		if(!strcmp("Read", next.c_str())){
			sst >> next;
			readfile(myArray, next);
		} else if(!strcmp("Insert", next.c_str())){
			sst >> next >> next_;
			myArray.insert(next, next_);
		} else if(!strcmp("Delete", next.c_str())){
			sst >> next;
			myArray.deleteword(next);
		} else if(!strcmp("Print", next.c_str())){
			sst >> next;
			if(!strcmp("forward", next.c_str())){
				myArray.print_forward();
			} else if(!strcmp("backward", next.c_str())){
				myArray.print_backward();
			}
		}
	}
}