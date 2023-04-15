/* Introduce to <chrono> 
	
	-- A precision-neutral library for time and date
	
 * clocks:
 *
 * std::chrono::system_clock:  current time according to the system (it is not steady)
 * std::chrono::steady_clock:  goes at a uniform rate (it can't be adjusted)
 * std::chrono::high_resolution_clock: provides smallest possible tick period. 
 *                   (might be a typedef of steady_clock or system_clock)
 *
 * clock period is represented with std:ratio<>
 */
#include <iostream>
#include <chrono>

int main() {
    std::ratio<1,10>  r; // 
    std::cout << r.num << "/" << r.den << std::endl;

    std::cout << std::chrono::system_clock::period::num << "/" << std::chrono::system_clock::period::den << std::endl;
    std::cout << std::chrono::steady_clock::period::num << "/" << std::chrono::steady_clock::period::den << std::endl;
    std::cout << std::chrono::high_resolution_clock::period::num << "/" << std::chrono::high_resolution_clock::period::den << std::endl;

/*
 *
 * std:chrono::duration<>:  represents time duration
 *    duration<int, ratio<1,1>> --  number of seconds stored in a int  (this is the default)
 *    duration<double, ration<60,1>> -- number of minutes (60 seconds) stored in a double
 *    convenince duration typedefs in the library:
 *    nanoseconds, microseconds, milliseconds, seconds, minutes, hours
 * system_clock::duration  -- duration<T, system_clock::period>
 *                                 T is a signed arithmetic type, could be int or long or others
 */
    std::chrono::microseconds mi(2745);
    std::chrono::nanoseconds na = mi;
    std::chrono::milliseconds mill = std::chrono::duration_cast<std::chrono::milliseconds>(mi);  // when information loss could happen, convert explicitly
														  // Truncation instead of rounding
	mi = mill + mi;  // 2000 + 2745 = 4745
	mill = std::chrono::duration_cast<std::chrono::milliseconds>(mill + mi);  // 6
	std::cout << na.count() << std::endl;
	std::cout << mill.count() << std::endl;
	std::cout << mi.count() << std::endl;

    std::cout << "min: " << std::chrono::system_clock::duration::min().count() << "\n";
    std::cout << "max: " << std::chrono::system_clock::duration::max().count() << "\n";


 /* std::chrono::time_point<>: represents a point of time
 *       -- Length of time elapsed since a spacific time in history: 
 *          00:00 January 1, 1970 (Corordinated Universal Time - UTC)  -- epoch of a clock
 * time_point<system_clock, milliseconds>:  according to system_clock, the elapsed time since epoch in milliseconds
 *
 * typdefs
  system_clock::time_point  -- time_point<system_clock, system_clock::duration>
  steady_clock::time_point  -- time_point<steady_clock, steady_clock::duration>
 */
	// Use system_clock
	std::chrono::system_clock::time_point tp = std::chrono::system_clock::now();
	std::cout << tp.time_since_epoch().count() << std::endl;  
	tp = tp + std::chrono::seconds(2);  // no need for cast because tp is very high resolution
	std::cout << tp.time_since_epoch().count() << std::endl;

	// Calculate time interval
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::cout << "I am bored" << std::endl;
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	std::chrono::steady_clock::duration d = end - start;
	if (d == std::chrono::steady_clock::duration::zero())
		std::cout << "no time elapsed" << std::endl;
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(d).count() << std::endl;

    // Using system_clock may result in incorrect value
    return 0;
}
