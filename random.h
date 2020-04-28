#ifndef random_h
#define random_h

#include <random>

using namespace std;

//	USAGE: when creating the object, using the distributions provided by the STD <random>: http://www.cplusplus.com/reference/random/
//	Random<distribution<>> name(randomEngine(),constructionArgs);		//	"constructionArgs" represent the arguments of the distribution constructor.
//	Random<distribution<>> name(randomEngine(),distr);					//	"distr" represent the distribution to construct via copy-constructor.

//	N.B. c++17 introduce automatic deduction of template parameters, so you are allowed to use the syntax:		Random name(randomEngine(),distr);

template <typename T>
class Random{
public:
	template<typename... Args>
	Random(mt19937 * eng, Args ... args) : engine(eng), distribution(args...) {}
	Random(mt19937 * eng, T distr) : engine(eng), distribution(distr) {}
	~Random(){ engine = nullptr; }
	template<typename... Args>
	void initialize(Args &&... args){
		distribution.param(T(args...));
	}
	double generate(){ return distribution(*engine); }
	double generate(double min, double max){
		double to_return = distribution(*engine);
		while( to_return > max || to_return < min ){
			to_return = distribution(*engine);
		}
		return to_return;
	}
protected:
	mt19937 * engine;
	T distribution;
};


class Discrete{
public:
	Discrete(vector<double> outcome_possibilities, vector<double> probability) :
				outcomes(outcome_possibilities), distribution(probability.begin(), probability.end()){};
	template<typename URNG>
	double operator()(URNG & g){
		return outcomes[distribution(g)];
	}
protected:
	vector<double> outcomes;
	discrete_distribution<> distribution;
};


template <typename URNG = mt19937>
URNG * randomEngine(int seed = -1){
	if( seed == -1 ){
		seed = random_device()();
	}
	static URNG * randomEng = new URNG( seed );
	return randomEng;
}

#endif