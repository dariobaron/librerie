#ifndef algebra3D_h
#define algebra3D_h

#include <array>
#include <iostream>
using namespace std;

class Matrix3{
public:
	// Costruttore di default + costruttore che prende i singoli elementi (ordinamento righe-colonne)
	Matrix3(double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0, double = 0);
	// Costruttore che prende un array bidimensionale
	Matrix3(array< array<double,3>, 3 > );
	// Operatore per il prodotto righe*colonne tra matrici
	Matrix3 operator*(const Matrix3 & ) const;
	// Operatore per il prodotto righe*colonne tra matrice e vettore
	array<double,3> operator*(const array<double,3> & ) const;
	// Ritorna una copia della n-esima riga della matrice
	array<double,3> getRow(int n) const;
	// Ritorna una copia della n-esima colonna della matrice
	array<double,3> getCol(int n) const;
	// Traspone questa matrice
	void transpose();
	// Ritorna una copia della matrice trasposta lasciando inalterata questa matrice
	Matrix3 getTransposed() const;
	// Ritorna la traccia della matrice
	double trace() const;
	// Ritorna il determinante della matrice
	double determinant() const;
private:
	array< array<double,3>, 3 > _mat;
};

// Operatore per il prodotto interno tra vettori
double operator*(array<double,3> , array<double,3> );

// Operatore per la stampa di matrici
ostream & operator<<(ostream & , Matrix3 );

// Operatore per la stampa di vettori
ostream & operator<<(ostream & , array<double,3> );

#endif