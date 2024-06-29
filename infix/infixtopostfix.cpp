//4001406135
#include <iostream>
#include <string>

using namespace std;

class Stack {
private:
	char *stack;
	int end = 0;
public:
	Stack(int size) {
		stack = new char(size);
	}
	
	~Stack() {
		delete stack;
	}
	
	void push(char c) {
		stack[end] = c;
		end++;
	}
	
	char pop() {
		if (!isEmpty()) {
			char c = stack[end];
			end--;
			return c;
		}
	}
	
	char top() {
		if (!isEmpty()) 
			return stack[end-1];
	}
	
	bool isEmpty(){
		return (end == 0);
	}
};

int getPrecedence(char op) {
	if (op == '^') 
		return 3;
	else if (op == '*' || op == '/') 
		return 2;
	else if (op == '+' || op == '-') 
		return 1;
	else 
		return 0;
}

bool isDigit(char ch) {
	if ((ch >= '0' && ch <= '9') || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return true;
	else 
		return false;
}

bool isOperator(char op) {
	return (getPrecedence(op) != 0);
}



string infixToPostfix(string input) {
	string out;
	Stack st(20);
	for (int i = 0; i < input.length(); i++) {
		char c = input[i];
		if (c == '(') 
			st.push('(');
		
		else if (isDigit(c))
			out += c;
			
		else if (isOperator(c)) {
			while (!st.isEmpty()) {
				if (st.top() == '(') 
					break;
					
				else if (getPrecedence(c) <= getPrecedence(st.top())) {
					out += st.top();
					st.pop();
				}
				else 
					break;
			}
			st.push(c);
		}
		
		else if (c == ')') {
			while (!st.isEmpty()) {
				if(st.top() == '(') {
					st.pop();
					break;
				}
				out += st.top();
				st.pop();
			}
		}
	}
	
	while (!st.isEmpty())
	{
		out += st.top();
		st.pop();
	}
	
	return out;
}

int main() {
	string infix;
	cin >> infix;
	string postfix = infixToPostfix(infix);
	cout << postfix;
}