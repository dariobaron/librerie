#ifndef random_h
#define random_h

#include <random>
#include <mutex>
using namespace std;

//	USAGE: when including, a RandomEngine object must be initialized (possibly in main.cpp) as global variable,
//		with default or seed constructor.

template<typename URNG = mt19937_64>
class RandomEngine{
public:
	RandomEngine() : engine( random_device()() ) {}
	RandomEngine(int seed) : engine(seed) {}
	void discard(unsigned long long n){ engine.discard(n); }
	auto max() const{ return engine.max(); }
	auto min() const{ return engine.min(); }
	void seed(int s){ engine.seed(s); }
	auto operator()(){
		lock_guard<mutex> guard(mtx);
		return engine();
	}
protected:
	URNG engine;
	mutex mtx;
};

extern RandomEngine<> random_engine;

//	USAGE RandomDistr: when creating the object, using the distributions provided by the STD <random>: http://www.cplusplus.com/reference/random/
//	RandomDistr<distribution<>> name(randomEngine(),constructionArgs);		//	"constructionArgs" represent the arguments of the distribution constructor.
//	RandomDistr<distribution<>> name(randomEngine(),distr);					//	"distr" represent the distribution to construct via copy-constructor.

//	N.B. c++17 introduce automatic deduction of template parameters, so you are allowed to use the syntax:		RandomDistr name(randomEngine(),distr);


template <typename T>
class RandomDistr{
public:
	template<typename... Args>
	RandomDistr(Args ... args) : distribution(args...) {}
	RandomDistr(T distr) : distribution(distr) {}
	template<typename... Args>
	void initialize(Args &&... args){
		distribution.param(T(args...));
	}
	double generate(){ return distribution(random_engine); }
	double generate(double min, double max){
		double to_return = distribution(random_engine);
		while( to_return > max || to_return < min ){
			to_return = distribution(random_engine);
		}
		return to_return;
	}
protected:
	T distribution;
};


template<typename T>
class Discrete{
public:
	Discrete(vector<T> outcome_possibilities, vector<double> probability) :
				outcomes(outcome_possibilities), distribution(probability.begin(), probability.end()){};
	template<typename URNG>
	T operator()(URNG & g){
		return outcomes[distribution(g)];
	}
protected:
	vector<T> outcomes;
	discrete_distribution<> distribution;
};

#endif