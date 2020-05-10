#ifndef random_h
#define random_h

////////	Macro for definition of CUDA declspecs (__host__ or __device__)
#ifdef __CUDACC__
#define CUDA_CALLABLE_FUNCTION __host__ __device__
#else
#define CUDA_CALLABLE_FUNCTION
#endif
////////


#include <random>
#include <vector> 

using namespace std;

//	USAGE: when including, a RandomEngine object must be initialized (possibly in main.cpp) as global variable,
//		with default or seed constructor.

template<typename URNG = mt19937_64>
class RandomEngine{
public:
	CUDA_CALLABLE_FUNCTION RandomEngine() : engine( random_device()() ) {}
	CUDA_CALLABLE_FUNCTION RandomEngine(int seed) : engine(seed) {}
	CUDA_CALLABLE_FUNCTION void discard(unsigned long long n){ engine.discard(n); }
	CUDA_CALLABLE_FUNCTION auto max() const{ return engine.max(); }
	CUDA_CALLABLE_FUNCTION auto min() const{ return engine.min(); }
	CUDA_CALLABLE_FUNCTION void seed(int s){ engine.seed(s); }
	CUDA_CALLABLE_FUNCTION auto operator()(){
		return engine();
	}
protected:
	URNG engine;
};


/*__host__ __device__ void initRandomEngine(){
	randomEng = new mt19937_64( random_device()() );
}


__host__ __device__ void initRandomEngine(long int seed){
	randomEng = new mt19937_64( seed );
}*/


//	USAGE RandomDistr: when creating the object, using the distributions provided by the STD <random>: http://www.cplusplus.com/reference/random/
//	RandomDistr<distribution<>> name(random_engine,constructionArgs);		//	"constructionArgs" represent the arguments of the distribution constructor.
//	RandomDistr<distribution<>> name(random_engine,distr);					//	"distr" represent the distribution to construct via copy-constructor.

//	N.B. c++17 introduce automatic deduction of template parameters, so you are allowed to use the syntax:		RandomDistr name(random_engine,distr);


template <typename T>
class RandomDistr{
public:
	template<typename... Args>
	CUDA_CALLABLE_FUNCTION RandomDistr(RandomEngine<> * random_engine, Args ... args) : engine(random_engine), distribution(args...) {}
	CUDA_CALLABLE_FUNCTION RandomDistr(RandomEngine<> * random_engine, T distr) : engine(random_engine), distribution(distr) {}
	CUDA_CALLABLE_FUNCTION ~RandomDistr(){ engine = nullptr; }
	template<typename... Args>
	CUDA_CALLABLE_FUNCTION void initialize(Args &&... args){
		distribution.param(T(args...));
	}
	CUDA_CALLABLE_FUNCTION double generate(){ return distribution(*engine); }
	CUDA_CALLABLE_FUNCTION double generate(double min, double max){
		double to_return = distribution(*engine);
		while( to_return > max || to_return < min ){
			to_return = distribution(*engine);
		}
		return to_return;
	}
protected:
	T distribution;
	RandomEngine<> * engine;
};


class Discrete{
public:
	CUDA_CALLABLE_FUNCTION Discrete(vector<double> outcome_possibilities, vector<double> probability) :
				outcomes(outcome_possibilities), distribution(probability.begin(), probability.end()){};
	template<typename URNG>
	CUDA_CALLABLE_FUNCTION double operator()(URNG & g){
		return outcomes[distribution(g)];
	}
protected:
	vector<double> outcomes;
	discrete_distribution<> distribution;
};

#endif