#include <iostream>
#include <chrono>

int main() {

	std::cout << "system_clock durations can represent: "<<std::endl;
	std::cout << "min: " <<  std::chrono::system_clock::duration::min().count() << std::endl;
	std::cout << "max:  " << std::chrono::system_clock::duration::max().count() << std::endl;
  

    std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
    std::chrono::system_clock::duration dtn = tp.time_since_epoch();

    std::cout << "current time since epoch, expressed in:" << std::endl;
    std::cout << "periods: " << dtn.count() << std::endl;
    std::cout << "seconds: " << dtn.count() * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den;
    std::cout << std::endl;

    std::cout<<"------------------------------------------------"<<std::endl;

    using std::chrono::system_clock;
    std::chrono::duration<int, std::ratio<60*60*24> > one_day (1);
    system_clock::time_point today = system_clock::now();
    system_clock::time_point tomorrow = today + one_day;
    std::time_t tt = system_clock::to_time_t (today);
    std::cout << "today is: " << ctime(&tt);
    tt = system_clock::to_time_t ( tomorrow );
    std::cout << "tomorrow will be: " << ctime(&tt);

    std::cout<<"------------------------------------------------"<<std::endl;

    using namespace std::chrono;

  	steady_clock::time_point t11 = steady_clock::now();
  	std::cout << "printing out 1000 stars...\n";
  	for (int i = 0; i < 1000; ++i)
  		std::cout << "*";
  	std::cout << std::endl;

  	steady_clock::time_point t12 = steady_clock::now();
  	duration<double> time_span1 = duration_cast<duration<double>>(t12 - t11);
  	std::cout << "It took me " << time_span1.count() << " seconds.";
  	std::cout << std::endl;


  	std::cout<<"------------------------------------------------"<<std::endl;

  	using namespace std::chrono;
  	high_resolution_clock::time_point t21 = high_resolution_clock::now();

  	std::cout << "printing out 1000 stars...\n";
  	for (int i = 0; i < 10000; ++i)
  		std::cout << "*";
    std::cout << std::endl;

  	high_resolution_clock::time_point t22 = high_resolution_clock::now();
  	duration<double> time_span2 = duration_cast<duration<double>>(t22 - t21);
  	std::cout << "It took me " << time_span2.count() << " seconds.";
  	std::cout << std::endl;

  	std::cout<<"------------------------------------------------"<<std::endl;

  	std::chrono::seconds s(1);
  	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds> (s);

  	ms += std::chrono::milliseconds(2500);
  	s = std::chrono::duration_cast<std::chrono::seconds> (ms);
  	std::cout << "ms: " << ms.count() << std::endl;
  	std::cout << "s:  " << s.count() << std::endl;


  	std::cout<<"------------------------------------------------"<<std::endl;

  	using namespace std::chrono;
  	typedef duration<int, std::ratio<60*60*24>> days_type;
  	time_point<system_clock, days_type> today1 = time_point_cast<days_type>(system_clock::now());
  	std::cout << today1.time_since_epoch().count() << " days since epoch" << std::endl;
}