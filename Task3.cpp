#include <iostream>
#include <string>
#include <cctype>
using namespace std;
struct CharNode {
    char data;
    CharNode* next;
};

class CharStack {
private:
    CharNode* topNode;
public:
    CharStack() { topNode = nullptr; }
    
    ~CharStack() { clear(); }

    void push(char val) {
        CharNode* newNode = new CharNode;
        newNode->data = val;
        newNode->next = topNode;
        topNode = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        CharNode* temp = topNode;
        char val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    char peek() {
        if (isEmpty()) return '\0';
        return topNode->data;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    void clear() {
        while (topNode != nullptr) {
            CharNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};

struct IntNode {
    int data;
    IntNode* next;
};

class IntStack {
private:
    IntNode* topNode;
public:
    IntStack() { topNode = nullptr; }
    
    ~IntStack() { clear(); }

    void push(int val) {
        IntNode* newNode = new IntNode;
        newNode->data = val;
        newNode->next = topNode;
        topNode = newNode;
    }
    
    int pop() {
        if (isEmpty()) return 0;
        IntNode* temp = topNode;
        int val = temp->data;
        topNode = topNode->next;
        delete temp;
        return val;
    }

    bool isEmpty() {
        return topNode == nullptr;
    }

    void clear() {
        while (topNode != nullptr) {
            IntNode* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';
}


string infixToPostfix(string expression, bool& isValid) {
    isValid = true;
    if (expression.empty()) {
        cout << "Error: Expression is empty.\n";
        isValid = false;
        return "";
    }

    CharStack opStack;
    string postfix = "";
    int i = 0;
    int len = expression.length();

    while (i < len) {
        char c = expression[i];

        // Skip blank spaces
        if (c == ' ') {
            i++;
            continue;
        }

        if (isdigit(c)) {
            while (i < len && isdigit(expression[i])) {
                postfix += expression[i];
                i++;
            }
            postfix += " ";
            continue;
        }

        if (c == '(') {
            opStack.push(c);
        } 
        else if (c == ')') {
            bool foundOpening = false;
            while (!opStack.isEmpty()) {
                if (opStack.peek() == '(') {
                    opStack.pop();
                    foundOpening = true;
                    break;
                }
                postfix += opStack.pop();
                postfix += " ";
            }
            if (!foundOpening) {
                cout << "Error: Mismatched parentheses (Extra closing parenthesis).\n";
                isValid = false;
                return "";
            }
        } 
        else if (isOperator(c)) {
            while (!opStack.isEmpty() && getPrecedence(opStack.peek()) >= getPrecedence(c)) {
                postfix += opStack.pop();
                postfix += " ";
            }
            opStack.push(c);
        } 
        else {
            cout << "Error: Invalid character '" << c << "' found.\n";
            isValid = false;
            return "";
        }
        i++;
    }

    while (!opStack.isEmpty()) {
        if (opStack.peek() == '(') {
            cout << "Error: Mismatched parentheses (Extra opening parenthesis).\n";
            isValid = false;
            return "";
        }
        postfix += opStack.pop();
        postfix += " ";
    }

    return postfix;
}

int evaluatePostfix(string postfix, bool& isValid) {
    isValid = true;
    IntStack evalStack;
    int i = 0;
    int len = postfix.length();

    while (i < len) {
        // Skip spaces
        if (postfix[i] == ' ') {
            i++;
            continue;
        }

        if (isdigit(postfix[i])) {
            int num = 0;
            while (i < len && isdigit(postfix[i])) {
                num = (num * 10) + (postfix[i] - '0');
                i++;
            }
            evalStack.push(num);
            continue;
        }

        // If it's an operator
        if (isOperator(postfix[i])) {
            char op = postfix[i];

            if (evalStack.isEmpty()) { isValid = false; return 0; }
            int val2 = evalStack.pop();

            if (evalStack.isEmpty()) { isValid = false; return 0; }
            int val1 = evalStack.pop();

            int result = 0;
            if (op == '+') result = val1 + val2;
            else if (op == '-') result = val1 - val2;
            else if (op == '*') result = val1 * val2;
            else if (op == '/') {
                if (val2 == 0) {
                    cout << "Error: Division by zero.\n";
                    isValid = false;
                    return 0;
                }
                result = val1 / val2;
            } 
            else if (op == '%') {
                if (val2 == 0) {
                    cout << "Error: Modulus by zero.\n";
                    isValid = false;
                    return 0;
                }
                result = val1 % val2;
            }
            evalStack.push(result);
        }
        i++;
    }

    int finalResult = evalStack.pop();
    
    if (!evalStack.isEmpty()) {
        isValid = false;
        return 0;
    }

    return finalResult;
}

void runTest(string label, string infixExpression) {
    cout << "=== " << label << " ===\n";
    cout << "Infix   : " << infixExpression << "\n";

    bool status = true;
    string postfix = infixToPostfix(infixExpression, status);

    if (status) {
        cout << "Postfix : " << postfix << "\n";
        int result = evaluatePostfix(postfix, status);
        if (status) {
            cout << "Result  : " << result << "\n";
        }
    }
    cout << "\n";
}

int main() {
    runTest("Test 1", "2 + 3 * 4");
    runTest("Test 2", "(2 + 3) * 4");
    runTest("Test 3", "10 + 2 * 6");
    runTest("Test 4", "(10 + 2) * (6 - 3)");
    runTest("Test 5", "20 / 5 + 3");
    runTest("Nested Parentheses Test", "((2 + 3) * 2) % 3");
    runTest("Multiple Operators Test", "10 + 5 * 2 - 4 / 2");
    runTest("Empty Expression Test", "");
    runTest("Mismatched Parentheses (Extra Close)", "2 + 3) * 4");
    runTest("Mismatched Parentheses (Extra Open)", "(2 + 3 * 4");
    runTest("Division by Zero", "10 / 0");
    return 0;
}
