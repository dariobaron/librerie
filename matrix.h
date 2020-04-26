#ifndef matrix_h
#define matrix_h

#include <valarray>
using namespace std;

template<typename T = double>
class Matrix{
public:
	Matrix(int r, int c = r) : rows(r), cols(c), m(rows*cols) {}:
	
protected:
	int rows;
	int cols;
	valarray<T> m;
};

#endif