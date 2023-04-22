#include <iostream>
#include <string>
#include <stack>
#include <numeric>
#include <regex>

enum class enum_op_t : char
{ OP_ADD = '+', OP_SUB = '-', OP_MUL = '*', OP_DIV = '/', OP_INVALID = '0' };

int precedence(enum_op_t op){
    if(op == enum_op_t::OP_ADD || op == enum_op_t::OP_SUB)
        return 1;
    if(op == enum_op_t::OP_MUL || op == enum_op_t::OP_DIV)
        return 2;
    return 0;
}

double performOp(enum_op_t var, int lhs, int rhs) {
    switch (var) {
        case enum_op_t::OP_ADD:
            return lhs + rhs;
        case enum_op_t::OP_SUB:
            return lhs - rhs;
        case enum_op_t::OP_DIV:
            if (!rhs) {
                throw std::runtime_error("error: division by zero.\n");
            } else {
                return lhs / rhs;
            }
        case enum_op_t::OP_MUL:
            return lhs * rhs;
        default: return 0.0;
    }
}

class Calculator {
public:
    explicit Calculator(std::string str) : _expr(std::move(str)) {
        _expr.erase(std::remove(_expr.begin(), _expr.end(), ' '), _expr.end());
    }

    double startEval() {
        std::stack<char> p_stack;
        for (char ch : _expr) {
            switch (ch) {
                case '(':
                    p_stack.push('(');
                    break;
                case ')':
                    if (p_stack.empty() || p_stack.top() != '(') {
                        throw std::runtime_error("error: unbalanced or unexpected parentheses\n");
                    }
                    else {
                        p_stack.pop();
                    }
                    break;
                default:
                    break;
            }
        }
        if (!p_stack.empty()) {
            throw std::runtime_error("error: unbalanced or unexpected parentheses\n");
        }
        return evaluate();
    }
private:
    std::string           _expr;
    std::string::iterator _cur = std::begin(_expr);
    std::stack<std::pair<enum_op_t, double>> mid;

    enum_op_t getOperator() {
        switch (*_cur) {
            case '+': _cur++; return enum_op_t::OP_ADD;
            case '-': _cur++; return enum_op_t::OP_SUB;
            case '*': _cur++; return enum_op_t::OP_MUL;
            case '/': _cur++; return enum_op_t::OP_DIV;
            default:          return enum_op_t::OP_INVALID;
        }
    }

    double getNumerical() {
        std::string::iterator _tmp = _cur;
        for (; std::isdigit(*(_tmp)); ++_tmp) {}
        std::string tempString = std::string(_cur, _tmp);
        if (!std::regex_match(tempString, std::regex {"[+-]?([0-9]*)?[0-9]+"})) {
            throw std::runtime_error("error: could not parse token, expect <int>.\n");
        }
        auto returnValue = std::stod(tempString);
        _cur = _tmp;
        return returnValue;
    };

    double getValue() {
        if (std::isdigit(*_cur)) {
            return getNumerical();
        } else if (*_cur == '(') {
            _cur++;
            double retValue = evaluate();
            if (*_cur != ')') {
                if (_cur <= std::end(_expr)) {
                    throw std::runtime_error("error");
                }
                throw std::runtime_error("error: value expected, got token.\n");
            }
            _cur++;
            return retValue;
        } else if (*_cur == '+') {
            _cur++;
            return getValue();
        } else if (*_cur == '-') {
            _cur++;
            return getValue() * (-1);
        } else {
            throw std::runtime_error("error: unexpected expression, could not parse.\n");
        }
    }

    double evaluate() {
        mid.push({ enum_op_t::OP_INVALID, 0 });
        double returnValue = getValue();
        while (!mid.empty()) {
            enum_op_t var = getOperator();
            while (precedence(var) < precedence(mid.top().first) ||
                  (precedence(var) == precedence(mid.top().first) && var == enum_op_t::OP_INVALID)) {
                if (mid.top().first == enum_op_t::OP_INVALID) {
                    mid.pop();
                    return returnValue;
                }
                returnValue = performOp(mid.top().first, mid.top().second, returnValue);
                mid.pop();
            }
            mid.push({ var, returnValue }); returnValue = getValue();
        }
        return 0;
    }
};

bool evaluate(const char* expression, int &result) {
    try {
        Calculator c(std::string{expression});
        result = c.startEval();
        return true;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl;
        result = std::numeric_limits<int>::max();
        return false;
    }
}

int main() {
    std::cout << std::boolalpha;
    int result;
    std::cout << evaluate("1 + 3", result) << "  " << result << std::endl;
    std::cout << evaluate("(1 + 3) * 2", result) << "  " << result << std::endl;
    std::cout << evaluate("(4 / 2) + 6", result) << "  " << result << std::endl;
    std::cout << evaluate("4 + (12 / (1 * 2))", result) << "  " << result << std::endl;
    std::cout << evaluate("4 + (12 / (1 * -2))", result) << "  " << result << std::endl;
    std::cout << evaluate("(1 + (12 * 2)", result) << "  " << result << std::endl;
    std::cout << evaluate("1 + 12 * 2)", result) << "  " << result << std::endl;
    std::cout << evaluate(nullptr, result) << "  " << result << std::endl;
    std::cout << evaluate("1 + (12 / 0)", result) << "  " << result << std::endl;
    return 0;
}