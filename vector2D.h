#ifndef vector2D_h
#define vector2D_h

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

template<typename T = double>
class vector2D{
public:
	vector2D() : rows(0), cols(0), v() {};
	vector2D(int r, int c) : rows(r), cols(c), v(rows*cols) {};
	vector2D(const vector<vector<T>> & vecofvecs) : rows(vecofvecs.size()), cols(vecofvecs[0].size()), v(rows*cols) {
		for(int i = 0; i < v.size(); ++i){
			v[i] = vecofvecs[i / cols][i % cols];
		}
	}
	int row() const { return rows; }
	int col() const { return cols; }
	T & element(int r, int c){
		return v[r*cols + c];
	}
	vector<T> getRow(int r) const{
		return vector<T>(v.begin() + r*cols, v.begin() + (r+1)*cols);
	}
	vector<T> getCol(int c) const{
		vector<T> to_return(rows);
		for(int i = 0; i < to_return.size(); ++i){
			to_return[i] = v[i*cols + c];
		}
		return to_return;
	}
	void setRow(int r, const vector<T> & input){
		if( checkColSize(input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				v[r*cols + i] = input[i];
			}
		}
	}
	void setCol(int c, const vector<T> & input){
		if( checkRowSize(input.size()) ){
			for(int i = 0; i < input.size(); ++i){
				v[i*cols + c] = input[i];
			}
		}
	}
	void insertRow(int r, const vector<T> & input){
		if( checkColSize(input.size()) ){
			++rows;
			v.insert(v.begin() + r*cols, input.begin(), input.end());
		}
	}
	void insertCol(int c, const vector<T> & input){
		if( checkRowSize(input.size()) ){
			++cols;
			for(int i = 0; i < input.size(); ++i){
				v.insert(v.begin() + i*cols + c, *input.begin() + i);
			}
		}
	}
	void eraseRow(int r){
		v.erase(v.begin() + r*cols, v.begin() + (r+1)*cols);
		--rows;
	}
	void eraseCol(int c){
		for(int i = 0; i < rows; ++i){
			v.erase(v.begin() + i*cols + c);
		}
		--cols;
	}
	void pushBackRow(const vector<T> & input){
		if( checkColSize(input.size()) ){
			++rows;
			v.insert(v.end(), input.begin(), input.end());
		}
	}
	void pushBackCol(const vector<T> & input){
		if( checkRowSize(input.size()) ){
			++cols;
			for(int i = 0; i < input.size(); ++i){
				v.insert(v.begin() + (i+1)*cols - 1, input[i]);
			}
		}
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
	vector<T> v;
private:
	bool checkColSize(int inputsize){
		if( v.size() == 0 ){
			cols = inputsize;
			return true;
		}
		if( cols == inputsize ){
			return true;
		} else{
			cerr << "The insertion cannot be done, wrong number of components in the inserting vector" << endl;
			return false;
		}
	}
	bool checkRowSize(int inputsize){
		if( v.size() == 0 ){
			rows = inputsize;
			return true;
		}
		if( rows == inputsize ){
			return true;
		} else{
			cerr << "The insertion cannot be done, wrong number of components in the inserting vector" << endl;
			return false;
		}
	}
};

#endif