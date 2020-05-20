#ifndef useful_h
#define useful_h

#include <utility>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <random>
#include <ctime>
using namespace std;


// Estrae casualmente n elementi da un vettore senza ripetizione
template<typename T>
vector<T> extractNRandom(const vector<T> & v, unsigned int n){
	vector<T> toreturn;
	if( n > v.size() ){}
	else{
		toreturn = v;
		random_shuffle(toreturn.begin(), toreturn.end());
		int casuale(0);
		if( v.size() != n ){
			casuale = rand() % (v.size()-n);
		}
		toreturn.erase(toreturn.begin(), toreturn.begin()+casuale);
		toreturn.erase(toreturn.begin()+n, toreturn.end());
	}
	return toreturn;
}


// Ordinatore di pair in base al primo elemento
template<typename T1, typename T2>
bool sortbyfirst(pair<T1, T2> a, pair<T1, T2> b){
	return ( a.first < b.first );
}


// Ordinatore di pair in base al secondo elemento
template<typename T1, typename T2>
bool sortbysecond(pair<T1, T2> a, pair<T1, T2> b){
	return ( a.second < b.second );
}


template <typename T = long long int>
class Factorial{
public:
	Factorial(unsigned int n = 1) : values(n+1){
		values[0] = 1;
		for(int i = 1; i < values.size(); ++i){
			values[i] = i * values[i-1];
		}
	};
	T operator()(unsigned int n){
		static int cont = 0;
		double provv;
		if( n > 20 && cont == 0 && typeid(values[0]) != typeid(provv) ){
			++cont;
			cerr << "WARNING: Be sure to declare Factorial<double>, otherwise it will cause overflow" << endl;
		}
		while( n >= values.size() ){
			values.push_back( values.size() * values.back() );
		}
		return values[n];

	};
protected:
	vector<T> values;
};


// Inizia a far partire il timer
inline clock_t startTimer(){
	return clock();
}


// Restituisce il tempo impiegato in secondi
inline double stopTimer(clock_t begin){
	return (double)( clock() - begin ) / CLOCKS_PER_SEC;
}

#endif