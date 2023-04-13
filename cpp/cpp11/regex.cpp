/* 
   Regular Expression:  a regular expression is a specific pattern that provides concise and flexible means 
   to "match" strings of text, such as particular characters, words, or patterns of characters. - wikipedia
   */

#include <regex>
#include <iostream>

void f1() {
    std::string str;
    while (true) {
        std::cin >> str;
        //regex e("abc.", regex_constants::icase);   // .   Any character except newline
        //regex e("abc?");               // ?       Zero or 1 preceding character
        //regex e("abc*");               // *       Zero or more preceding character
        //regex e("abc+");               // +       One of more preceding character
        //regex e("ab[cd]*");            // [...]   Any character inside the square brackets
        //regex e("ab[^cd]*");           // [...]   Any character not inside the square brackets
        //regex e("ab[cd]{3,5}");
        //regex e("abc|de[\]fg]");         // |       Or
        //regex  e("(abc)de+\\1");       // \1      First group
        //regex  e("(ab)c(de+)\\2\\1");
        //regex e("[[:w:]]+@[[:w:]]+\.com"); // [[:w:]] word character: digit, number, or underscore

        //regex e("abc.$");                 // $   End of the string
        std::regex e("^abc.+", std::regex_constants::grep);                 // ^   begin of the string


        //bool match = regex_match(str, e);
        bool match = regex_search(str, e);

        std::cout << (match? "Matched" : "Not matched") << std::endl << std::endl;
    }
}

/*

   Regular Expression Grammars:

   ECMAScript
   basic
   extended
   awk
   grep 
   egrep

*/

/***************  Deal with subexpression *****************/

/* 
   std::match_results<>  Store the detailed matches
   smatch                Detailed match in string

   smatch m;
   m[0].str()   The entire match (same with m.str(), m.str(0))
   m[1].str()   The substring that matches the first group  (same with m.str(1))
   m[2].str()   The substring that matches the second group
   m.prefix()   Everything before the first matched character
   m.suffix()   Everything after the last matched character
   */

void f2() {
    std::string str;

    while (true) {
        std::cin >> str;
        std::smatch m;        // typedef std::match_results<string>

        std::regex e("([[:w:]]+)@([[:w:]]+)\.com");  

        bool found = regex_search(str, m, e);

        std::cout << "m.size() " << m.size() << std::endl;
        for (int n = 0; n< m.size(); n++) {
            std::cout << "m[" << n << "]: str()=" << m[n].str() << std::endl;
            std::cout << "m[" << n << "]: str()=" << m.str(n) << std::endl;
            std::cout << "m[" << n << "]: str()=" << *(m.begin()+n) << std::endl;
        }
        std::cout << "m.prefix().str(): " << m.prefix().str() << std::endl;
        std::cout << "m.suffix().str(): " << m.suffix().str() << std::endl;
    }
}

/**************** Regex Iterator ******************/
void f3() {
    std::cout << "Hi" << std::endl;

    std::string str;

    while (true) {
        std::cin >> str;

        std::regex e("([[:w:]]+)@([[:w:]]+)\.com"); 

        std::sregex_iterator pos(str.cbegin(), str.cend(), e);
        std::sregex_iterator end;  // Default constructor defines past-the-end iterator
        for (; pos!=end; pos++) {
            std::cout << "Matched:  " << pos->str(0) << std::endl;
            std::cout << "user name: " << pos->str(1) << std::endl;
            std::cout << "Domain: " << pos->str(2) << std::endl;
            std::cout << std::endl;
        }
        std::cout << "=============================" << std::endl;
    }
}

/**************** Regex Token Iterator ******************/
void f4() {
    std::cout << "Hi" << std::endl;

    //string str = "Apple; Orange, {Cherry}; Blueberry";
    std::string str = "boq@yahoo.com, boqian@gmail.com; bo@hotmail.com";

    //regex e("[[:punct:]]+");  // Printable character that is not space, digit, or letter.
    //regex e("[ [:punct:]]+"); 
    std::regex e("([[:w:]]+)@([[:w:]]+)\.com");

    std::sregex_token_iterator pos(str.cbegin(), str.cend(), e, 0);
    std::sregex_token_iterator end;  // Default constructor defines past-the-end iterator
    for (; pos!=end; pos++) {
        std::cout << "Matched:  " << *pos << std::endl;
    }
    std::cout << "=============================" << std::endl;


    std::cin >> str;
}

/**************** regex_replace ******************/
void f5() {
    std::cout << "Hi" << std::endl;

    std::string str = "boq@yahoo.com, boqian@gmail.com; bo@hotmail.com";

    std::regex e1("([[:w:]]+)@([[:w:]]+)\.com");
    std::regex e2("([[:w:]]+)@([[:w:]]+)\.com", std::regex_constants::grep|std::regex_constants::icase );

    //cout << regex_replace(str, e, "$1 is on $2");
    std::cout << regex_replace(str, e1, "$1 is on $2", std::regex_constants::format_no_copy|std::regex_constants::format_first_only);
    std::cout << regex_replace(str, e2, "$1 is on $2");


    std::cin >> str;
}

int main() {
    f1();
    f2();
    f3();
    f4();
    f5();

    return 0;
}
