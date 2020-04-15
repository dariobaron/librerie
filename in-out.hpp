#ifndef in_out_hpp
#define in_out_hpp

#include <iostream>
#include <vector>
using namespace std;

//	Overloading for << ostream operator on vector of T. Works also for nested vectors
template<typename T>
ostream & operator<<(ostream & os, const vector<T> v){
	os << endl;
	for(int i = 0; i < v.size(); ++i){
		if( i != 0 ){
			os << "\t";
		}
		os << v[i];
	}
	return os;
}


#endif