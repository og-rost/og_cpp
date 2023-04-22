#include <map>
#include <iostream>
#include <cctype>
#include <string>
#include <sstream>

namespace Error {
    struct Zero_divide {};

    struct Syntax_error {
        const char* p;
        Syntax_error(const char* q) { p = q; }
    };
}

namespace Lexer {
    enum Token_value {
        NAME,		NUMBER,		END,
        PLUS='+',	MINUS='-',	MUL='*',	DIV='/',
        PRINT=';',	ASSIGN='=',	LP='(',		RP=')'
    };

    Token_value curr_tok;
    double number_value;
    std::string string_value;

    Token_value get_token();
}

namespace Parser {
    double prim(bool get);		// handle primaries
    double term(bool get);		// multiply and divide
    double expr(bool get);		// add and subtract

    using namespace Lexer;
    using namespace Error;
}

namespace Symbol_table {
    std::map<std::string, double> table;
}

namespace Driver {
    int no_of_errors;
    std::istream* input;

    void skip();
}

Lexer::Token_value Lexer::get_token() {
    char ch;

    do {	// skip whitespace except '\n'
        if(!Driver::input->get(ch)) 
            return curr_tok = END;
    } while (ch != '\n' && isspace(ch));

    switch (ch) {
        case 0:
            return END;
        case ';':
        case '\n':
            return curr_tok = PRINT;
        case '*':
        case '/':
        case '+':
        case '-':
        case '(':
        case ')':
        case '=':
            return curr_tok = Token_value(ch);
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
        case '.':
            Driver::input->putback(ch);
            *Driver::input >> number_value;
            return curr_tok = NUMBER;
        default:			// NAME, NAME =, or error
            if (isalpha(ch)) {
                string_value = ch;
                while (Driver::input->get(ch) && isalnum(ch))
                    string_value.push_back(ch);
                Driver::input->putback(ch);
                return curr_tok = NAME;
            }
            throw Error::Syntax_error("bad token");
    }
}

double Parser::prim(bool get) {
    if (get) get_token();

    switch (curr_tok) {
        case Lexer::NUMBER:	// floating point constant
            get_token();
            return number_value;
        case Lexer::NAME: {	
                              double& v = Symbol_table::table[string_value];
                              if (get_token() == ASSIGN) v = expr(1);
                              return v;
                          }

        case Lexer::MINUS:		// unary minus
                          return -prim(1);
        case Lexer::LP:	{	
                            double e = expr(1);
                            if (curr_tok != RP) 
                                throw Error::Syntax_error("`)' expected");
                            get_token();			  // eat ')'
                            return e;
                        }
        case Lexer::END:
                        return 1;
        default:
                        throw Error::Syntax_error("primary expected");
    }
}

double Parser::term(bool get) {
    double left = prim(get);

    while (true)			// ``forever''
        switch (curr_tok) {
            case Lexer::MUL:
                left *= prim(true);
                break;
            case Lexer::DIV:
                if (double d = prim(true)) {
                    left /= d;
                    break;
                }	
                throw Error::Zero_divide();
            default:
                return left;
        }
}

double Parser::expr(bool get) {
    double left = term(get);	

    while (true)				// ``forever''
        switch (curr_tok) {
            case Lexer::PLUS:
                left += term(true);
                break;
            case Lexer::MINUS:
                left -= term(true);
                break;
            default:
                return left;
        }
}

void Driver::skip() {
    ++no_of_errors;

    while (*input) {	// discard characters until newline or semicolon
        // note: skip doesn't know the state of the parser
        // so if the erro rwas caused by a newline
        // or a semicolon, we need to look for
        // yet another terminator
        char ch;
        input->get(ch);

        switch (ch) {
            case '\n':
            case ';':
                return;
        }
    }
}

int main() {
    using namespace Driver;

    input = &std::cin;
    // insert pre-defined names:
    Symbol_table::table["pi"] = 3.1415926535897932385;
    Symbol_table::table["e"]  = 2.7182818284590452354;

    while (*input) {
        std::cout<<"new expression: " << std::endl;
        try {
            Lexer::get_token();
            if (Lexer::curr_tok == Lexer::END) break;
            if (Lexer::curr_tok == Lexer::PRINT) continue;
            std::cout << Parser::expr(false) << '\n';
        }
        catch(Error::Zero_divide) {
            std::cerr << "attempt to divide by zero\n";
            skip();
        }
        catch(Error::Syntax_error e) {
            std::cerr << "syntax error:" << e.p << "\n";
            skip();
        }
    }

    if (input != &std::cin) 
        delete input;
    return no_of_errors;
}
