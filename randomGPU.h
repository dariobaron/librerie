#ifdef __CUDACC__

#ifndef randomGPU_h
#define randomGPU_h

#define HD_CALL __host__ __device__

#include <iostream>
#include <random>
#include <algorithm>
#include <thrust/random/uniform_real_distribution.h>
#include <curand_kernel.h>
#include <curand_mtgp32_host.h>
using namespace std;


template<typename TargetClass, typename SourceClass>
__global__ void initializeClassOnGPU(int n, TargetClass * interface_state, SourceClass * cuda_states){
	for(int i = 0; i < n; ++i){
		void * placement = interface_state + i;
		TargetClass * temp = new(placement) TargetClass(cuda_states + i);
	}
}


template<typename T>
__global__ void freeClassOnGPU(int n, T * ptr){
	for(int i = 0; i < n; ++i){
		(ptr+i)->~T();
	}
}


class MTGP32_state{
public:
	typedef unsigned int result_type;
	static const result_type max = 4294967295;
	static const result_type min = 0;

	HD_CALL MTGP32_state() : state(nullptr) {}
	HD_CALL MTGP32_state(curandStateMtgp32 * p) : state(p) {}
	HD_CALL ~MTGP32_state(){ state = nullptr; }
	HD_CALL void operator=(const MTGP32_state source){ state = source.getPtr(); }
	HD_CALL void operator=(curandStateMtgp32 * p){ state = p; }
	
	HD_CALL curandStateMtgp32 * getPtr() const{ return state; }
	HD_CALL curandStateMtgp32 * getPtr(){ return state; }
	HD_CALL unsigned int operator()(){
		return curand(state);
	}
protected:
	curandStateMtgp32 * state;
};


class MTGP32{
public:
	__host__ MTGP32(int & th_per_bl, int & bl, int seed = 0) : threads_per_block(min(th_per_bl, 256)), blocks(min(bl, 200)){
		if( th_per_bl > 256 ){
			cerr << "WARNING: up to 256 threads_per_block can be used, automatic reset of the variable" << endl;
			th_per_bl = 256;
		}
		if( bl > 200 ){
			cerr << "WARNING: up to 200 blocks can be used, automatic reset of the variable" << endl;
			bl = 200;
		}
		if( seed == 0 ){
			seed = random_device()();
		}
		// Allocate space for MTGP kernel parameters
		cudaMalloc((void**)&d_kernelparams, sizeof(mtgp32_kernel_params));
		// Copy pre-generated parameters into d_kernelparams 
		curandMakeMTGP32Constants(mtgp32dc_params_fast_11213, d_kernelparams);
		// Allocate space for the MTGP states readable by CUDA
		cudaMalloc((void **)&d_MTGPstates, blocks * sizeof(curandStateMtgp32));
		// Set-up "blocks" kernel states in the region addressed by d_MTGPstates from d_kernelparams, with seed
		curandMakeMTGP32KernelState(d_MTGPstates, mtgp32dc_params_fast_11213, d_kernelparams, blocks, seed);

		// Allocate space for the MTGP32_state interface written above
		cudaMalloc((void **)&states, blocks * sizeof(MTGP32_state));
		// Initialization
		initializeClassOnGPU<<<1,1>>>(blocks, states, d_MTGPstates);
	}
	__host__ ~MTGP32(){
		freeClassOnGPU<<<1,1>>>(blocks, states);
		cudaFree(d_MTGPstates);
		cudaFree(d_kernelparams);
		d_MTGPstates = nullptr;
		d_kernelparams = nullptr;
	}
	__host__ MTGP32_state * getStatesPtr(){ return states; }
protected:
	int threads_per_block;
	int blocks;
	MTGP32_state * states;
	curandStateMtgp32 * d_MTGPstates;
    mtgp32_kernel_params * d_kernelparams;
};


template <typename T>
class RandomDistrGPU{
public:
	template<typename... Args>
	HD_CALL RandomDistrGPU(MTGP32_state * eng, Args ... args) : engine(eng), distribution(args...) {
//		printf("RandomDistrGPU Constructor at attress %p with engine at %p\n", this, engine);
	}
	HD_CALL RandomDistrGPU(MTGP32_state * eng, T distr) : engine(eng), distribution(distr) {}
	HD_CALL ~RandomDistrGPU(){ engine = nullptr; }//printf("RandomDistrGPU Destructor at address %p\n", this); }
	template<typename... Args>
	HD_CALL void initialize(Args &&... args){
		distribution.param(T(args...));
	}
	HD_CALL double generate(){ return distribution(*engine); }
	HD_CALL double generate(double min, double max){
		double to_return = distribution(*engine);
		while( to_return > max || to_return < min ){
			to_return = distribution(*engine);
		}
		return to_return;
	}
protected:
	MTGP32_state * engine;
	T distribution;
};


class DiscreteGPU{
public:
	HD_CALL DiscreteGPU(int size, double * output, double * probability) : n(size){
		outcomes = new double[n];
		histogram = new double[n];
		for(int i = 0; i < n; ++i){
			outcomes[i] = output[i];
			histogram[i] = probability[i];
		}
		double sum = 0.;
		for(int i = 0; i < n; ++i){
			sum += histogram[i];
		}
		if( sum != 1. ){
			for(int i = 0; i < n; ++i){
				histogram[i] = histogram[i] / sum;
			}
		}
		for(int i = 1; i < n; ++i){
			histogram[i] = histogram[i] + histogram[i-1];
		}
	}
	template<typename URNG>
	HD_CALL double operator()(URNG & g){
		double val = distribution(g);
		int idx = 0;
		while( val > histogram[idx] && idx < n ){ ++idx; }
		return outcomes[idx];
	}
protected:
	const int n;
	double * outcomes;
	double * histogram;
	thrust::uniform_real_distribution<> distribution;
};


#endif

#endif