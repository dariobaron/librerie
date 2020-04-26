#ifndef algebra_h
#define algebra_h

#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include "random.h"
using namespace std;


template<typename T>
short sign(T val){
	if( val > 0 ){
		return 1;
	} else if( val == 0 ){
		return 0;
	}
	return -1;
}


template<typename pointType>
void normalize(pointType & v, double radius = 1.){
	double norm = sqrt(inner_product(v.begin(), v.end(), v.begin(), 0.));
	for(auto & i : v){
		i = i * radius / norm;
	}
	return;
}


template<typename pointType>
double norm(const pointType & v){
	return sqrt(inner_product(v.begin(), v.end(), v.begin(), 0.));
}


template<typename pointType>
pointType operator+(pointType a, const pointType & b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] + b[i];
	}
	return a;
}


template<typename pointType>
pointType operator-(pointType a, const pointType & b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] - b[i];
	}
	return a;
}


template<typename pointType>
pointType operator*(pointType a, double b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] * b;
	}
	return a;
}
template<typename pointType>
pointType operator*(double b, pointType a){
	return a * b;
}


template<typename pointType>
pointType operator/(pointType a, double b){
	for(int i = 0; i < a.size(); ++i){
		a[i] = a[i] / b;
	}
	return a;
}


template<typename pointType>
double operator*(const pointType & a, const pointType & b){
	return inner_product(a.begin(), a.end(), b.begin(), 0.);
}


//	Builds a random point on the "dim"-dimension hypersphere of radius "radius"
template<typename pointType>
pointType buildRandomPoint(int dim, double radius = 1.){
	Random <normal_distribution<>, double, double> rnd(randomEngine(), 0., 1.);
	pointType v(dim);
	for(auto & i : v){
		i = rnd.generate();
	}
	normalize(v,radius);
	return v;
}


template<typename pointType>
void ortonormalizeGramSchmidt(vector<pointType> & set){
	for(int i = 1; i < set.size(); ++i){
		vector<double> temp(set[i].size(), 0.);
		for(int j = 0; j < i; ++j){
			temp = temp + ( set[j] * (set[j]*set[i])/(set[j]*set[j]) );
		}
		set[i] = set[i] - temp;
	}
	// Normalizing the new base vectors
	for(auto & i : set){
		normalize(i);
	}
	return;
}


//	Create the tangent bundle of the point passed as argument
template<typename pointType>
vector<pointType> tangentBundle(const pointType v){
	// Creating base vectors (assuming v orthogonal to the standard basis with probability 1)
	vector< vector<double> > to_return(v.size());
	to_return[0] = v;
	for(int i = 1; i < to_return.size(); ++i){
		vector<double> temp(v.size(), 0.);
		for(int j = 0; j < v.size(); ++j){
			if(i == j){
				temp[j] = 1.;
			}
		}
		to_return[i] = temp;
	}
	ortonormalizeGramSchmidt(to_return);
	// Removing the first vector (to obtain the tangent bundle)
	to_return.erase(to_return.begin());
	return to_return;
}


#endif