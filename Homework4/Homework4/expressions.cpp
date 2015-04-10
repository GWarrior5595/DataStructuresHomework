/* Name: Erphun Ranjbar
* Date: 10/14/2014
*
* Enviroment:
*    Written and compiled in Ubuntu terminal
*
* If ran in a terminal use command:
*  "expression.cpp commands.txt"
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
#include <sstream>
#include "myStack.h"
using namespace std;


//Postfix to infix
string InfixToPostfix(string theExpression);
int HasHigherOrder(char operator1, char operator2);
bool CheckOperator(char C);
bool CheckOperand(char C);

string InfixToPostfix(string theExpression){
	// Declaring a Stack from stl
	int length = theExpression.length() * 10;
	stackType<char> stack(length);
	stack.initializeStack();
	string postfix = ""; // Initialize postfix as empty string.
	for (int i = 0; i< theExpression.length(); i++) {
		if (theExpression[i] == ' ' || theExpression[i] == ',') 
			continue;
		else if (CheckOperator(theExpression[i])){
			postfix += " ";
			while (!stack.empty() && stack.top() != '(' && HasHigherOrder(stack.top(), theExpression[i])){
				postfix += stack.top();
				stack.pop();
				postfix += " ";
			}
			stack.push(theExpression[i]);
		}
		// Else if character is an operand
		else if (CheckOperand(theExpression[i])){
			postfix += theExpression[i];
		}

		else if (theExpression[i] == '('){
			stack.push(theExpression[i]);
		}

		else if (theExpression[i] == ')'){
			while (!stack.empty() && stack.top() != '(') {
				postfix += " ";
				postfix += stack.top();
				stack.pop();
			}
			stack.pop();
		}
	}
	postfix += " ";
	while (!stack.empty()) {
		postfix += stack.top();
		postfix += " ";
		stack.pop();
	}

	return postfix;
}

// Function to verify whether a character is a variable.
bool CheckOperand(char i){
	if (i >= '0' && i <= '9') 
		return true;
	if (i >= 'a' && i <= 'z') 
		return true;
	if (i >= 'A' && i <= 'Z') 
		return true;
	return false;
}

// Function to verify whether a character is operator symbol or not.
bool CheckOperator(char i){
	if (i == '+' || i == '-' || i == '*' || i == '/' || i == '$')
		return true;
	return false;
}

bool CheckOperatorString(string i){
	if (i == "+" || i == "-" || i == "*" || i == "/" || i == "$")
		return true;
	return false;
}

// Function to verify whether an operator is right associative or not.
int IsOnTheRight(char operators){
	if (operators == '$') 
		return true;
	return false;
}

// Function to see which operator to do first
int GetOperatorOrder(char operators){
	switch (operators){
	case '+': 
		return 1;
		break;
	case '-': 
		return 1;
		break;
	case '*': 
		return 2;
		break;
	case '/': 
		return 2;
		break;
	case '$': 
		return 3;
		break;
	}
}

// Function to perform an operation and return output.
int HasHigherOrder(char operator1, char operator2){
	int Order1 = GetOperatorOrder(operator1);
	int Order2 = GetOperatorOrder(operator2);

	if (Order1 == Order2){
		if (IsOnTheRight(operator1)) 
			return false;
		else return true;
	}
	//assert statement
	return Order1 > Order2 ? true : false;
}
//End of Postfix to Infix

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

	void remove(string wordtodelete){
		if (isopen){
			int num = 1;
			bool search = true;
			temp1 = new nodeType;
			temp1 = start;
			if (wordtodelete == temp1->info && (temp1->next == temp1->prev)){
				temp1 = start;
				start->next = NULL;
				start->prev = NULL;
				start = NULL;
				delete temp1;
				return;
			}
			temp1 = start;
			while (search){
				if (temp1->info != wordtodelete)
					num++;
				else if (temp1->info == wordtodelete)
					search = false;
				temp1 = temp1->next;
				if (temp1->info == wordtodelete && temp1->next == NULL){
					num = -999;
					search = false;
				}
				else if (temp1->next == NULL && search == true){
					search = false;
					return;
				}
			}
			temp1 = start;
			if (wordtodelete == temp1->info){
				if (start == NULL){
				}
				else{
					temp1 = start;
					start = start->next;
					start->prev = NULL;
					delete temp1;
				}
			}
			else if (num == -999){
				while (temp1->next != NULL){
					temp2 = temp1;
					temp1 = temp1->next;
				}
				delete temp1;
				temp2->next = NULL;
			}
			else if (num != -999){
				temp1 = new nodeType;
				temp1 = start;
				temp2 = new nodeType;
				for (int i = 1; i < num; i++){
					if (start == NULL)
						return;
					else{
						temp2 = temp1;
						temp1 = temp1->next;
					}
				}
				temp3 = temp1->next;
				temp2->next = temp3;
				temp3->prev = temp2;
				delete temp1;
			}
		}
	}

	void insert(string wordstoinsert, string wordtoinsertafter){
		if (isopen){
			int number = 0;
			bool search = true;
			temp2 = new nodeType;
			temp1 = new nodeType;
			temp1->info = wordstoinsert;
			temp3 = start;
			while (temp3->next != NULL){
				temp3 = temp3->next;
			}
			if (wordtoinsertafter == temp3->info){
				temp2 = start;
				while (temp2->next != NULL)
					temp2 = temp2->next;
				temp2->next = temp1;
				temp1->prev = temp2;
				temp1->next = NULL;
			}
			else{
				temp1 = new nodeType;
				temp1 = start;
				while (search){
					if (temp1->info != wordtoinsertafter)
						number++;
					else if (temp1->info == wordtoinsertafter && temp1->next != NULL){
						search = false;
					}
					else if (temp1->next == NULL){
						search = false;
						return;
					}
					temp1 = temp1->next;
					if (temp1->next == NULL && search == true){
						search = false;
						return;
					}
				}
				search = true;
				temp1 = new nodeType;
				temp1->info = wordstoinsert;
				temp2 = new nodeType;
				temp2 = start;
				for (int i = 0; i < number + 1; i++){
					if (start == NULL)
						return;
					else{
						temp3 = temp2;
						temp2 = temp2->next;
					}
				}
				number = 0;
				temp1->next = temp2;
				temp3->next = temp1;
				temp1->prev = temp3;
				temp2->prev = temp1;
			}
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

	//Union functions in recursion
	void UnionTestA(struct nodeType* head){
		if (head == NULL)
			return;
		else{
			placeintolist(head->info);
			UnionTestA(head->next);
		}
	}
	//End of Union functions

	//Intersection function recursion
	void IntersectionTest(struct nodeType* head, struct nodeType* head1){
		if (head == NULL || head1 == NULL)
			return;
		else{
			if (head->info == head1->info)
				placeintolist(head->info);
			IntersectionTest(head->next, head1);
			IntersectionTest(head1->next, head);
		}
	}
	//end of intersection function

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
	nodeType* GetHead(){
		return start;
	}
	void setHead(nodeType* A){
		start = A;
	}
};


class listType{
public:
	string nameOfList;
	listType *next;
	listType *prev;
	int num;
};

class ListOfName{
private:
	listType *start = NULL, *temp1, *temp2;
public:
	void newFileAdded(string name, int place){
		temp1 = new listType;
		temp1->nameOfList = name;
		temp1->num = place;
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

	int getTheIndexOfList(string name_){
		temp1 = start;
		int index = -1;
		if (temp1->nameOfList == name_){
			index = temp1->num;
		}
		while (temp1->next != NULL){
			temp1 = temp1->next;
			if (temp1->nameOfList == name_)
				index = temp1->num;
		}
		return index;
	}

};

ListOfName list;

int getNumberList(string fileName){
	ifstream readMyFile;
	string line;
	string command;
	int num = 0;
	readMyFile.open(fileName);
	if (!readMyFile.is_open()){
		return -1;
	}
	while (getline(readMyFile, line)){
		istringstream sst(line, istringstream::in);
		sst >> command;
		int n = command.find_first_of('=', 0);
		if (!strcmp("Read", command.c_str())){
			num++;
		}
		else if (n != -1){
			num++;
		}
	}
	return num;
}

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

NodeArray eval(NodeArray &A, NodeArray &B, NodeArray &C, string operate){
	struct nodeType* head = NULL;
	struct nodeType* head1 = NULL;
	C.start = NULL;
	if (operate == "+"){
		C.UnionTestA(A.GetHead());
		C.UnionTestA(B.GetHead());
		C.removeDuplicatesInList();
		return C;
	}
	else if (operate == "*"){
		head = A.GetHead();
		head1 = B.GetHead();
		C.IntersectionTest(head, head1);
		C.removeDuplicatesInList();
		return C;
	}

}

int main(int argv, char **argc){ //when they call, going to pass two parameters
	int num = getNumberList(argc[1]);
	NodeArray *myArray = new NodeArray[num];
	ifstream readMyFile;
	string line;
	string command;
	string command_;
	string _command;
	string expression;
	string expressionName;
	struct nodeType* head = NULL;
	struct nodeType* head1 = NULL;
	int count = 0;
	readMyFile.open(argc[1]);
	if (!readMyFile.is_open()){
		return 0;
	}
	while (getline(readMyFile, line)){
		istringstream sst(line, istringstream::in);
		sst >> command;
		int n = command.find_first_of('=', 0);
		if (!strcmp("Read", command.c_str())){
			sst >> command;
			sst >> command_; // letter to read
			list.newFileAdded(command_, count);
			int index = list.getTheIndexOfList(command_);
			readFile(myArray[index], command);
			count++;
		}
		else if (!strcmp("Print", command.c_str())){
			sst >> command; //letter to print
			sst >> command_; //direction to print
			if (!strcmp("forward", command_.c_str())){
				int index = list.getTheIndexOfList(command);
				if (index != -1){
					head = myArray[index].GetHead();
					myArray[index].printForwards(head);
					cout << endl;
				}
			}
			else if (!strcmp("backward", command_.c_str())){
				int index = list.getTheIndexOfList(command);
				if (index != -1){
					head = myArray[index].GetHead();
					myArray[index].printReverse(head);
					cout << endl;
				}
			}
		}
		else if (n != -1){
			expression = "";
			expressionName = "";
			for (int i = 0; i < n; i++)
				expressionName += command[i];
			for (int i = n + 1; i < command.length(); i++)
				expression += command[i];
			string postfix = InfixToPostfix(expression);
			//cout << expressionName <<"="<<expression << endl;
			//cout << postfix << endl;
			//cout << "------------------"<<endl;
			int length = postfix.length() * 10;
			stackType<NodeArray> s(length);
			s.initializeStack();
			istringstream sgg(postfix, istringstream::in);
			while (sgg){
				string temp;
				sgg >> temp;
				if (CheckOperatorString(temp)){
					NodeArray &A = s.top();
					s.pop();
					if (s.empty()){
						break;
					}
					NodeArray &B = s.top();
					s.pop();
					NodeArray C;
					s.push(eval(B, A, C, temp));
				}
				else{
					int index = list.getTheIndexOfList(temp);
					if (index != -1){
						s.push(myArray[index]);
					}
					if (index == -1){
					}
				}
			}
			if (!s.empty()){
				list.newFileAdded(expressionName, count);
				int element = list.getTheIndexOfList(expressionName);
				myArray[element].setHead(s.top().GetHead());
			}
		count++;
		}
	}
}
