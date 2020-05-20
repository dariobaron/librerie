#ifndef random_h
#define random_h

#include <random>
#include <vector>

using namespace std;


mt19937_64 * randomEngine(){
	static mt19937_64 * randomEng = new mt19937_64( random_device()() );
	return randomEng;
}

//	USAGE RandomDistr: when creating the object, using the distributions provided by the STD <random>: http://www.cplusplus.com/reference/random/
//	RandomDistr<distribution<>> name(randomEngine(),constructionArgs);		//	"constructionArgs" represent the arguments of the distribution constructor.
//	RandomDistr<distribution<>> name(randomEngine(),distr);					//	"distr" represent the distribution to construct via copy-constructor.

//	N.B. c++17 introduce automatic deduction of template parameters, so you are allowed to use the syntax:		RandomDistr name(randomEngine(),distr);


template <typename T>
class RandomDistr{
public:
	template<typename... Args>
	RandomDistr(Args ... args) : engine(randomEngine()), distribution(args...) {}
	RandomDistr(T distr) : engine(randomEngine()), distribution(distr) {}
	~RandomDistr(){ engine = nullptr; }
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
	mt19937_64 * engine;
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

#endif