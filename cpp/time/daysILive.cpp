#include <iostream>
#include <chrono>
#include <ctime>

using namespace std::chrono;
typedef duration<int, std::ratio<60*60*24>> days_type;

void daysIlive(int year, int month, int day) {
	std::tm timeinfo = std::tm();
	timeinfo.tm_year = year; 
	timeinfo.tm_mon  = month;    
	timeinfo.tm_mday = day;     

	std::time_t tt = std::mktime (&timeinfo);

	time_point<system_clock, days_type> bday = time_point_cast<days_type>(system_clock::from_time_t (tt));  	
  	time_point<system_clock, days_type> today = time_point_cast<days_type>(system_clock::now());
  	
  	std::cout << (today - bday).count() + ((today - bday).count())/365/4 << std::endl;
}

void daysIlive2(int y1, int m1, int d1, int y2, int m2, int d2) {
	struct std::tm a = {0, 0, 0, d1, m1, y1}; 
    struct std::tm b = {0, 0, 0, d2, m2, y2}; 
    std::time_t x = std::mktime(&a);
    std::time_t y = std::mktime(&b);

    if (x != (std::time_t)(-1) && y != (std::time_t)(-1)) {
        double difference = std::difftime(y, x) / (60 * 60 * 24);
        std::cout << std::ctime(&x);
        std::cout << std::ctime(&y);
        std::cout << "difference = " << difference + difference/365/4 << " days" << std::endl;
    }
}

int main() {
	daysIlive(93, 7, 3);
	std::cout<<"----------------------------"<<std::endl;
	daysIlive2(93, 7, 3, 115, 9, 21);
}
