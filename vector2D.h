#ifndef vector2D_h
#define vector2D_h

#include <iostream>
#include <algorithm>
#include <valarray>
using namespace std;

template<typename T = double>
class vector2D{
public:
	vector2D() : rows(0), cols(0), v() {};
	vector2D(int _row, int _col) : rows(_row), cols(_col), v(rows*cols) {};
	vector2D(const vector<vector<T>> & vecofvecs) : rows(vecofvecs.size()), cols(vecofvecs[0].size()), v(rows*cols) {
		for(int i = 0; i < v.size(); ++i){
			v[i] = vecofvecs[i / cols][i % cols];
		}
	}
	int row() const { return rows; }
	int col() const { return cols; }
	void setRow(int r, const vector<T> & input){
		if( checkComponents(cols, input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				v[r*cols + i] = input[i];
			}
		}
	}
	void setCol(int c, const vector<T> & input){
		if( checkComponents(rows, input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				v[i*rows + c] = input[i];
			}
		}
	}
	void pushBackRow(const vector<T> & input){
		if( checkComponents(cols, input.size()) ){
			v.insert(v.end(), input.begin(), input.end());
		}
	}
	void pushBackCol(const vector<T> & input){
		if( checkComponents(rows, input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				v.insert(v.begin() + i*cols, input[i]);
			}
		}
	}
	vector<T> getRow(int r) const{
		vector<T> to_return(v.begin() + r*cols, v.begin() + (r+1)*cols);
		return to_return;
	}
	vector<T> getCol(int c) const{
		vector<T> to_return(rows);
		for(int i = 0; i < to_return.size(); ++i){
			to_return[i] = v[i*rows + c];
		}
		return to_return;
	}
	T & element(int r, int c){
		return v[r*cols + c];
	}
	void print(ostream & os) const{
		for(int i = 0; i < rows; ++i){
			for(int j = 0; j < cols; ++j){
				os << v[i*cols + j] << "\t";
			}
			os << endl;
		}
	}
	void printTransposed(ostream & os) const{
		for(int j = 0; j < cols; ++j){
			for(int i = 0; i < rows; ++i){
				os << v[i*cols + j] << "\t";
			}
			os << endl;
		}
	}
protected:
	int rows;
	int cols;
	valarray<T> v;
private:
	bool checkComponents(int n, int inputsize){
		if( n == inputsize ){
			return true;
		} else{
			cerr << "The insertion cannot be done, wrong number of components in the inserting vector" << endl;
			return false;
		}
	}
};

#endif