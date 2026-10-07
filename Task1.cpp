#include <iostream>
#include <string>
using namespace std;
struct Node {
	char data;
	Node* next;
};
class Stack {
private:
	Node* topNode;

public:
	Stack() : topNode(nullptr) {}

	~Stack() {
		clear();
	}

	void push(char ch) {
		Node* newNode = new Node();
		newNode->data = ch;
		newNode->next = topNode;
		topNode = newNode;
	}
	
	bool pop() {
		if (isEmpty()) {
			return false;
		}
		Node* temp = topNode;
		topNode = topNode->next;
		delete temp;
		return true;
	}

	char top() const {
		if (isEmpty()) {
			return -1;
		}
		return topNode->data;
	}

	bool isEmpty() const {
		return topNode == nullptr;
	}

	void display() const {
		if (isEmpty()) {
			cout << "Stack is empty." << endl;
			return;
		}
		Node* current = topNode;
		cout << "Stack (top to bottom): ";
		while (current != nullptr) {
			cout << current->data << " ";
			current = current->next;
		}
		cout << endl;
	}

	void clear() {
		while (!isEmpty()) {
			pop();
		}
	}
};

bool isMatchingPair(char opening, char closing) {
	if (opening == '(' && closing == ')') return true;
	if (opening == '[' && closing == ']') return true;
	if (opening == '{' && closing == '}') return true;
	return false;
}

bool checkBalance(const string& expr) {
	Stack s;

	if (expr.empty()) {
		return true;
	}

	for (char ch : expr) {
		if (ch == '(' || ch == '[' || ch == '{') {
			s.push(ch);
		}
		else if (ch == ')' || ch == ']' || ch == '}') {
			if (s.isEmpty()) {
				return false;
			}
			if (!isMatchingPair(s.top(), ch)) {
				return false;
			}
			s.pop();
		}
	}
	return s.isEmpty();
}

int main() {
	string testCases[] = {
		"(A+B)",
		"{A+[B*C]}",
		"(A+B]",
		"((A+B)",
		"{[()]}",
		"A+B*C",
		"([A+B])"
	};
	cout << "--- Parentheses Balance Checker Results ---" << endl;

	for (const string& expr : testCases) {
		cout << "Expression: " << (expr.empty() ? "\"\"" : expr) << " -> ";
		if (checkBalance(expr)) {
			cout << "Balanced" << endl;
		}
		else {
			cout << "Not Balanced" << endl;
		}
	}
	return 0;
}
