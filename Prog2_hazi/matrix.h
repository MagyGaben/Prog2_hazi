#pragma once
#include <iostream>
#include "memtrace.h"
#include <vector>

using namespace std;

class matrix
{
private:
	int n, m; //rows, colums
	vector<double>* data;

public:
	/*Basic Test*/

	//Constructors
	matrix(); 
	matrix(int sqr);
	matrix(const matrix& ref);
	matrix(vector<double> v);
	matrix(const int n, const int m, vector<double>* data);
	//Destructor
	~matrix();

	//getter of the n attribute
	int getn() const;
	//getter of the m attribute
	int getm() const;
	//getter of the data pointer
	vector<double>* getData() const;

	//fills the matrix
	bool fill(int n, int m, vector<double> data);
	bool fill(int n, int m, vector<double>* data);
	bool fill(int n, int m, double value);

	//nullify the values in the matrix
	bool null();
	//fills the matrix with nulls
	bool null(int n, int m);

	//returns matrix without the row "ezt"
	matrix del_row(int ezt = 0) const;
	//returns matrix without the column "ezt"
	matrix del_col(int ezt = 0) const;

	//only for test purposes (easier to find in code with ctrl + F)
	void print(std::ostream & = std::cout);
	/*Basic Test*/



	/*Linear algebra test*/
	double gauss();	//gauss elimination on this value returns the determinant
	/*Linear algebra test*/


	/*Matrix Operations Test*/
	matrix T() const;	//returns transpose
	double determinant() const;	//returns determinant (better)
	double qdeterminant() const;	//returns deeterminant (quicker)
	matrix inverse() const;	//returns inverse
	void plusat(const double d, const unsigned i, const unsigned j);	//adds number d to the i,j indexes of the matrix
	/*Matrix Operations Test*/



	/*Matrix Operator Test*/
	matrix operator+(const matrix& theother) const;	//adds two matrices
	matrix operator*(const matrix& theother) const;	//multiply with a matrix
	matrix operator*(const vector<double>& theother) const;	//multiply with a vector
	matrix operator*(const double scalar) const;	//multiply with a scalar
	void operator=(const matrix& theother);	
	vector<double> operator[](const unsigned i) const;	//returns i-vector
	friend ostream& operator<<(ostream& out, const matrix& theother);	//ostream operator, friend

	matrix operator&(const matrix& theother) const;	//Puts a matrix after another, upgrade purposes
	/*Matrix Operator Test*/
};
ostream& operator<<(ostream& out, const matrix& op);

