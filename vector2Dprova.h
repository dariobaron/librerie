#ifndef vectorofvectors_h
#define vectorofvectors_h

#include <iostream>
#include <algorithm>
#include "algebra.h"
using namespace std;

template<typename T = double>
class vectorofvectors{
public:
	vectorofvectors() : rows(0), cols(0), v() {};
	vectorofvectors(int _row, int _col) : rows(row), cols(col){
		for(int i = 0; i < rows; ++i){
			v.emplace_back(cols);
		}
	}
	vectorofvectors(const vector<vector<T>> & vecofvecs) : rows(vecofvecs.size()), cols(vecofvecs[0].size()), v(vecofvecs) {};
	int row() const { return rows; }
	int col() const { return cols; }
	void row(int i, const vector<T> & input){
		if( input.size() == cols ){
			v[i] = input;
		} else{
			cerr << "The insertion cannot be done, wrong number of columns in the inserting vector" << endl;
		}
	}
	void col(int j, const vector<T> & input){
		if( input.size() == rows ){
			for(int i = 0; i < input.size(); ++i){
				v[i][j] = input[j];
			}
		} else{
			cerr << "The insertion cannot be done, wrong number of rows in the inserting vector" << endl;
		}
	}
	void pushBackRow(const vector<T> & input){
		if( input.size() == cols ){
			v.push_back(input);
			v.back().shrink_to_fit();
		} else{
			cerr << "The insertion cannot be done, wrong number of columns in the inserting vector" << endl;
		}
	}
	void pushBackCol(const vector<T> & input){
		if( input.size() == rows ){
			for(int i = 0; i < input.size(); ++i){
				v[i].push_back(input[i]);
				v[i].shrink_to_fit();
			}
		} else{
			cerr << "The insertion cannot be done, wrong number of rows in the inserting vector" << endl;
		}
	}
	vector<T> & operator[](int i){
		return v[i];
	}
	void print(ostream & os){
		for(auto & i : v){
			for(auto & j : i){
				os << j << "\t";
			}
			os << endl;
		}
	}
	void printTransposed(ostream & os){
		for(int j = 0; j < cols; ++j){
			for(int i = 0; i < rows; ++i){
				os << v[i][j] << "\t";
			}
			os << endl;
		}
	}
protected:
	int rows;
	int cols;
	vector<vector<T>> v;
};

#endif