#include "algebra3D.h"
#include <numeric>


Matrix3::Matrix3(double a, double b, double c, double d, double e, double f, double g, double h, double l){
	array<double,3> row1 = {a,b,c};
	array<double,3> row2 = {d,e,f};
	array<double,3> row3 = {g,h,l};
	_mat = {row1,row2,row3};
}


Matrix3::Matrix3(array< array<double, 3>, 3 > m) : _mat(m){}


Matrix3 Matrix3::operator*(const Matrix3 & m) const{
	array< array<double,3>, 3 > to_return;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			to_return[i][j] = getRow(i)*m.getCol(j);
		}
	}
	return Matrix3(to_return);
}


array<double,3> Matrix3::operator*(const array<double,3> & v) const{
	array<double,3> to_return;
	for(int i = 0; i < 3; ++i){
		to_return[i] = getRow(i) * v;
	}
	return to_return;
}


array<double,3> Matrix3::getRow(int row) const{
	return _mat[row];
}


array<double,3> Matrix3::getCol(int col) const{
	array<double,3> to_return;
	for(int i = 0; i < 3; ++i){
		to_return[i] = _mat[i][col];
	}
	return to_return;
}


void Matrix3::transpose(){
	for(int i = 0; i < 3; ++i){
		for(int j = i; j < 3; ++j){
			double provv(_mat[i][j]);
			_mat[i][j] = _mat[j][i];
			_mat[j][i] = provv;
		}
	}
}


Matrix3 Matrix3::getTransposed() const{
	array< array<double,3>, 3 > to_return;
	for(int i = 0; i < 3; ++i){
		for(int j = 0; j < 3; ++j){
			to_return[i][j] = _mat[j][i];
		}
	}
	return Matrix3(to_return);
}


double Matrix3::trace() const{
	double to_return = 0;
	for(int i = 0; i < 3; ++i){
		to_return += _mat[i][i];
	}
	return to_return;
}


double Matrix3::determinant() const{
	double to_return = 0;
	int count = 0;
	int j = 0;
	for(unsigned int i = 0; i < 3 || count < 3; ++i){
		double add = 1, sub = 1;
		for(count = 0; count < 3; ++count){
			add = add * _mat[i][j];
			sub = sub * _mat[i][2-j];
			++i; ++j;
			i = i%3; j = j%3;
		}
		cout << i << "  " << add << "  " << sub << endl;
		to_return += add;
		to_return -= sub;
	}
}


double operator*(array<double,3> a, array<double,3> b){
	double to_return = 0;
	for(int i = 0; i < 3; ++i){
		to_return += a[i] * b[i];
	}
	return to_return;
}


ostream & operator<<(ostream & os, Matrix3 m){
	for(int i = 0; i < 3; ++i){
		for(auto j : m.getRow(i)){
			cout << j << " ";
		}
		cout << endl;
	}
	return os;
}


ostream & operator<<(ostream & os, array<double,3> v){
	for(auto i : v){
		os << i << " ";
	}
	os << endl;
	return os;
}