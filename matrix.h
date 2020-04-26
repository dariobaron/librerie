#ifndef matrix_h
#define matrix_h

#include <valarray>
#include <iostream>
using namespace std;

template<typename T = double>
class Matrix{
public:
	Matrix(int n) : rows(n), cols(n), m(n*n) {};
	Matrix(int r, int c) : rows(r), cols(c), m(rows*cols) {};
	Matrix(const Matrix & m1) : rows(m1.row()), cols(m1.col()), m(rows*cols){
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < cols; ++j){
				element(i,j) = m1.element(i,j);
			}
		}
	}
	int row() const{ return rows; }
	int col() const{ return cols; }
	T & element(int r, int c){
		return m[r*cols + c];
	}
	T element(int r, int c) const{
		return m[r*cols + c];
	}
	valarray<T> operator[](int r) const{
		return valarray<T>( m[slice(r*cols, cols, 1)] );
	}
	valarray<T> getRow(int r) const{
		return valarray<T>( m[slice(r*cols, cols, 1)] );
	}
	valarray<T> getCol(int c) const{
		return valarray<T>( m[slice(c, rows, cols)] );
	}
	void setRow(int r, const valarray<T> & input){
		if( checkColSize(input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				m[r*cols + i] = input[i];
			}
		}
	}
	void setCol(int c, const valarray<T> & input){
		if( checkRowSize(input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				m[i*cols + c] = input[i];
			}
		}
	}
	void transpose(){
		for(int i = 0; i < rows; ++i){
			for(int j = i; j < cols; ++j){
				swap(element(i,j), element(j,i));
			}
		}
	}
	Matrix<T> getTransposed() const{
		auto to_return(*this);
		to_return.transpose();
		return to_return;
	}
	void print(ostream & os) const{
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < cols; ++j){
				os << m[i*cols + j] << "\t";
			}
			os << endl;
		}
	}
	void printTransposed(ostream & os) const{
		for(int j = 0; j < cols; ++j){
			for(int i = 0; i < rows; ++i){
				os << m[i*cols + j] << "\t";
			}
			os << endl;
		}
	}
	bool checkColSize(int inputsize) const{
		if( cols == inputsize ){
			return true;
		} else{
			cerr << "The operation cannot be done, wrong number of components in the input vector" << endl;
			return false;
		}
	}
	bool checkRowSize(int inputsize) const{
		if( rows == inputsize ){
			return true;
		} else{
			cerr << "The operation cannot be done, wrong number of components in the input vector" << endl;
			return false;
		}
	}
protected:
	int rows;
	int cols;
	valarray<T> m;
};


template<typename T>
valarray<T> operator*(const Matrix<T> & m, const valarray<T> & v){
	if( m.checkColSize(v.size()) ){
		valarray<T> to_return(m.row());
		for(int i = 0; i < to_return.size(); ++i){
			to_return[i] = m[i]*v;
		}
		return to_return;
	} else{
		return valarray<T>(v.size());
	}
}


template<typename T>
ostream & operator<<(ostream & os, const Matrix<T> & m){
	os << endl;
	for(int i = 0; i < m.row(); ++i){
		for(int j = 0; j < m.col(); ++j){
			if( j != 0 ){
				os << "\t";
			}
			os << m.element(i,j);
		}
		os << endl;
	}
	return os;
}

#endif