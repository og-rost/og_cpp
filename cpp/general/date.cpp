#include <iostream>
#include <ctime>

class Date {
public:
    void printFullDate() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        std::cout << asctime(now);
    }

    void printTime() {
        time_t currentTime;
        struct tm* localTime;

        time(&currentTime); 
        localTime = localtime(&currentTime);

        //int Day    = localTime->tm_mday;
        //int Month  = localTime->tm_mon + 1;
        //int Year   = localTime->tm_year + 1900;
        int Hour   = localTime->tm_hour;
        int Min    = localTime->tm_min;
        int Sec    = localTime->tm_sec;
        std::cout << Hour << ":" << Min << ":" << Sec << std::endl;
    }

    void printDay() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        std::cout << now->tm_mday<< std::endl;
    }

    void printMonth() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        std::cout << (now->tm_mon + 1) << std::endl;
    }

    void printYear() {
        time_t t = time(0);
        struct tm* now = localtime(&t);
        std::cout << (now->tm_year + 1900) << std::endl;
    }
};
 

int main() {
    Date date;
    date.printFullDate();
    date.printTime();
    date.printDay();
    date.printMonth();
    date.printYear();
}
