#pragma once
#include <iostream>
class matrix
{
private:
	int n, m;
	double** data;

public:
	/*Basic Test*/
	matrix();
	matrix(int n, int m, double** data);
	matrix(int sqr);
	matrix(matrix& ref);
	~matrix();

	bool fill(int n, int m, double* data);
	bool fill(int n, int m, double** data);
	bool fill(int n, int m, double value);
	bool null();
	bool null(int n, int m);

	matrix& del_row(int ezt = 0) const;
	matrix& del_col(int ezt = 0) const;

	void print(std::ostream & = std::cout);
	/*Basic Test*/



	/*Linear algebra test*/
	double gauss();
	/*Linear algebra test*/


	/*Matrix Operations Test*/
	matrix& T() const;
	double determinant() const;
	matrix& inverse() const;
	/*Matrix Operations Test*/



	/*Matrix Operator Test*/
	matrix& operator+(const matrix& theother) const;
	matrix& operator*(const matrix& theother) const;
	matrix& operator*(const double scalar) const;
	void operator=(const matrix& theother);

	matrix& operator&(const matrix& theother) const;	//Egymás után fûz két mátrixot
	/*Matrix Operator Test*/
};

