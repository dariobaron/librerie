#ifndef timer_h
#define timer_h

#include <chrono>
#include <ctime>
#include <vector>
using namespace std;
using namespace chrono;

#include <iostream>


template<typename UoM = seconds, typename ClockType = steady_clock>
class Timer{
public:
	Timer() : starting_point(ClockType::now()), laps({starting_point}) {}
	void restart(){
		starting_point = ClockType::now();
		laps = {starting_point};
	}
	auto lap(){
		auto newlap = ClockType::now();
		auto interval = (duration_cast<UoM>( newlap - laps.back() )).count();
		laps.push_back(newlap);
		return interval;
	}
	auto stop(){
		end_point = ClockType::now();
		laps.push_back(end_point);
		return (duration_cast<UoM>( end_point - starting_point )).count();
	}
protected:
	time_point<ClockType> starting_point;
	time_point<ClockType> end_point;
	vector<time_point<ClockType>> laps;
};


#endif