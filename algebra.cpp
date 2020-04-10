#include "algebra.h"
#include <algorithm>
#include "random.cpp"
using namespace std;


vector<double> buildRandomPoint(int dim, double radius){
	Random <normal_distribution<>, double, double> rnd(randomEngine(), 0., 1.);
	vector<double> v(dim);
	for(auto & i : v){
		i = rnd.generate();
	}
	normalize(v,radius);
	return v;
}


vector< vector<double> > tangentBundle(const vector<double> v){
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

	//random_shuffle(to_return.begin()+1, to_return.end());			QUESTO NON SO SE HA SENSO FARLO RANDOM OPPURE NO

	// Orthogonalizing the base vectors using Gram-Schimdt algorithm
	for(int i = 1; i < to_return.size(); ++i){
		vector<double> temp(v.size(), 0.);
		for(int j = 0; j < i; ++j){
			temp = temp + ( to_return[j] * (to_return[j]*to_return[i])/(to_return[j]*to_return[j]) );
		}
		to_return[i] = to_return[i] - temp;
	}

	// Normalizing the new base vectors
	for(auto & i : to_return){
		normalize(i);
	}

	// Removing the first vector (to obtain the tangent bundle)
	to_return.erase(to_return.begin());
	return to_return;
}