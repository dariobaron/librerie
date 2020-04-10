#include <random>

using namespace std;

//	USAGE: when creating the object, using the distributions provided by the STD <random>: http://www.cplusplus.com/reference/random/
//	Random<distribution<>, typeArg1, typeArg2, etc> nomevariabile(randomEngine(),Arg1,Arg2,etc);
//	"Arg1,Arg2,etc" represent the arguments of the distribution constructor.

template <typename T, typename... Args>
class Random{
public:
	Random(mt19937 * eng, Args ... args) : engine(eng), distribution(args...){};
	~Random(){ engine = nullptr; }
	void initialize(Args &&... args){
		T temp(args...);
		distribution.param(temp.param());
	};
	double generate(){ return distribution(*engine); };
	double generate(double min, double max){
		double to_return = distribution(*engine);
		while( to_return > max || to_return < min ){
			to_return = distribution(*engine);
		}
		return to_return;
	};
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
	};
protected:
	vector<double> outcomes;
	discrete_distribution<> distribution;
};


template <typename URNG = mt19937>
URNG * randomEngine(){
	static URNG * randomEng = new URNG( random_device()() );
	return randomEng;
}