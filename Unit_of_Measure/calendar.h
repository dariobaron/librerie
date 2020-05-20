#ifndef calendar_h
#define calendar_h

class JulianDay;
class ModJulianDay;


class GregorianCal{
public:
	GregorianCal(int y, int m, int d, int h = 0, int min = 0, double sec = 0.) : year(y), month(m), day(d){
		day += (h + (min + sec / 60.) / 60.) / 24.;
	}
	GregorianCal(JulianDay jd);
	GregorianCal(ModJulianDay mjd);
	int getYear() const { return year; }
	int getMonth() const { return month; }
	double getDay() const { return day; }
	void operator++(){
		++day;
		while(checkIfCarryOver()){}
	}
	template<typename NumVal>
	void operator+(NumVal n){
		day += n;
		while(checkIfCarryOver()){}
	}
protected:
	int year;
	int month;
	double day;
private:
	bool checkIfCarryOver(){
		vector<int> days_for_month({31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
		if( year % 4 != 0 ){}
		else if( year % 100 != 0){ ++days_for_month[1]; }
		else if( year % 400 != 0 ){}
		else{ ++days_for_month[1]; }
		int max_days = days_for_month[month - 1];
		if( day >= max_days + 1 ){
			day -= max_days;
			++month;
			if( month > 12 ){
				month -= 12;
				++year;
			}
			return true;
		}
		return false;
	}
};


class JulianDay{
public:
	JulianDay(double t) : time(t) {}
	JulianDay(GregorianCal gd){
		auto Y = gd.getYear();
		auto M = gd.getMonth();
		auto D = gd.getDay() - 0.5;
		time = D - 32075 + 1461 * ( Y + 4800 + (M-14)/12 ) / 4 + 367 * ( M - 2 - (M-14)/12*12 ) / 12 - 3 * ( ( Y + 4900 + (M-14)/12 ) / 100 ) / 4;
	}
	JulianDay(ModJulianDay mjd);
	double getTime() const { return time; }
	void operator++(){ ++time; }
	template<typename NumVal>
	void operator+(NumVal n){ time += n; }
protected:
	double time;
};


class ModJulianDay{
public:
	ModJulianDay(double t) : time(t) {}
	ModJulianDay(JulianDay jd) : time( jd.getTime() - 2400000.5 ) {}
	ModJulianDay(GregorianCal gd){
		auto Y = gd.getYear();
		auto M = gd.getMonth();
		auto D = gd.getDay() - 0.5;
		time = D - 32075 + 1461 * ( Y + 4800 + (M-14)/12 ) / 4 + 367 * ( M - 2 - (M-14)/12*12 ) / 12 - 3 * ( ( Y + 4900 + (M-14)/12 ) / 100 ) / 4 - 2400000.5;
	}
	double getTime() const { return time; }
	template<typename NumVal>
	void operator+(NumVal n){ time += n; }
protected:
	double time;
};


inline GregorianCal::GregorianCal(JulianDay jd){
	int JD0 = jd.getTime();
	double F = jd.getTime() - JD0;
	int L = JD0 + 68569;
	int N = 4 * L / 146097;
	L = L - ( 146097*N + 3 ) / 4;
	int I = 4000 * (L + 1) / 1461001;
	L = L - 1461 * I / 4 + 31;
	int J = 80 * L / 2447;
	day = L - 2447 * J / 80 + F + 0.5;
	L = J / 11;
	month = J + 2 - 12 * L;
	year = 100 * (N - 49) + I + L;
}


inline GregorianCal::GregorianCal(ModJulianDay mjd) : GregorianCal(JulianDay(mjd)) {}


inline JulianDay::JulianDay(ModJulianDay mjd) : time( mjd.getTime() + 2400000.5 ) {}


#endif