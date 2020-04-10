#include <vector>
#include <cmath>
#include <numeric>
using namespace std;


template<typename T>
short sign(T val){
	if( val > 0 ){
		return 1;
	}
	else if( val == 0 ){
		return 0;
	}
	return -1;
}


template<typename Container>
void normalize(Container & v, double radius = 1.){
	double norm = sqrt(inner_product(v.begin(), v.end(), v.begin(), 0.));
	for(auto & i : v){
		i = i * radius / norm;
	}
}


template<typename Container>
Container operator+(Container a, const Container & b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] + b[i];
	}
	return a;
}


template<typename Container>
Container operator-(Container a, const Container & b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] - b[i];
	}
	return a;
}


template<typename Container>
Container operator*(Container a, double b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] * b;
	}
	return a;
}
template<typename Container>
Container operator*(double b, Container a){
	return a * b;
}


template<typename Container>
Container operator/(Container a, double b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] / b;
	}
	return a;
}


template<typename Container>
double operator*(const Container & a, const Container & b){
	return inner_product(a.begin(), a.end(), b.begin(), 0.);
}


vector<double> buildRandomPoint(int dim, double radius = 1.);


vector< vector<double> > tangentBundle(const vector<double> v);
