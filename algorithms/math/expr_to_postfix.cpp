#include <iostream>
#include <string>
#include <cctype>
#include <stack>

int priority(char ch) {
	if (ch == '+' || ch == '-') {
		return 1;
	}
	if (ch == '*' || ch == '/') {
		return 2;
	}
}

void get_postfixx(std::string& expr, std::string& res) {

	std::stack<char> s;

	for (char ch : expr) {
		if (std::isdigit(ch)) {
			res.push_back(ch);
		}
		else if(ch == '(') {
			s.push(ch);
		}
		else if (ch == ')') {
			while (s.top() != '(') {
				res.push_back(s.top());
				s.pop();
			}
			s.pop();
		}
		else if (!std::isdigit(ch) && ch != '(') {
			if (s.empty() || priority(s.top()) < priority(ch)) {
				s.push(ch);
			}
			else {
				while (!s.empty() && s.top() != '(' && priority(s.top()) >= priority(ch)) {				
					res.push_back(s.top());
					s.pop();
				}
				s.push(ch);
			}
		}	
	}

	while (!s.empty()) {
		res.push_back(s.top());
		s.pop();
	}
}

int main() {
	std::string expr = "5+(1+6)*1-8+(4+(2*5))";
	std::string postfix_result;
	get_postfixx(expr, postfix_result);
	std::cout << expr << std::endl;
	std::cout << postfix_result << std::endl;
}
