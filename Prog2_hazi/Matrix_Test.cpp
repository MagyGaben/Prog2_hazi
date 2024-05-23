#include"matrix.h"
#include<iostream>

using namespace std;

int Matrix_Test_Basic(void)
{
	cout << "Matrix Test: Basic Functions\t begin..." << endl << endl << endl;
	matrix haromketto;
	vector<double> arr[3];
	arr[0] = { 0,1 };
	arr[1] = { 2,3 };
	arr[2] = { 4,5 };
	haromketto.fill(3, 2, arr);
	cout << "Testing Constructor:" << endl << endl << haromketto;

	matrix harom(3);
	cout << "Testing Overload Constructor" << endl << endl << harom;

	matrix copy = haromketto;
	cout << "Testing Copy Constructor" << endl << endl << copy;

	matrix nulmx;
	matrix nulmxs(haromketto);
	nulmx.null(4, 4);
	nulmxs.null();
	cout << "Testing Null" << endl << endl << nulmx << nulmxs;

	matrix DR = haromketto.del_row(1);
	cout << "Testing Row Delete" << endl << endl << DR;
	matrix DC = haromketto.del_col();
	cout << "Testing Column Delete" << endl << endl << DC << haromketto;

	vector<double> v = { 1,2,3,4,5 };
	matrix vec(v);
	cout << "Testing Vector Constructor" << endl << endl << vec;
	cout << "Matrix Test: Basic Functions\t ends..." << endl << endl;
	return 0;
}

int Matrix_Test_Operators(void)
{
	cout << "Matrix Test: Matrix Operators\t begin..." << endl << endl << endl;
	matrix egyik(3);
	cout << "Testing Multiplication with Scalar:" << endl << endl;
	matrix masik = egyik * 3;
	masik.print(cout);
	cout << "Testing Add Operator:" << endl << endl;
	matrix harmadik = egyik + masik;
	harmadik.print(cout);
	cout << "Testing Multiplication with Matrix:" << endl << endl;
	egyik = harmadik * masik;
	egyik.print();
	cout << "Testing & Operator:" << endl << endl;
	harmadik = egyik & masik;
	harmadik.print();
	cout << "Testing [] Operator:" << endl << endl;
	vector<double> ve = harmadik[1];
	matrix vectr(ve);
	vectr.print();
	cout << "Testing Multiplication with Vector:" << endl << endl << ve << harmadik;
	vectr = harmadik * ve;
	vectr.print();
	cout << "Matrix Test: Matrix Operators\t ends..." << endl << endl;
	return 0;
}

int Matrix_Test_Operations(void)
{
	cout << "Matrix Test: Operations with Matrices\t begin..." << endl << endl << endl;
	vector<double> tmb [4] = 
	{	{0,1,2,3},
		{4,5,6,7},
		{8,9,10,11} };
	matrix test;
	test.fill(3, 4, tmb);
	cout << "Testing Transpose:" << endl << endl << test;
	matrix Transpose = test.T();
	cout << "Transpose:" << endl << endl <<Transpose;
	test.~matrix();

	cout << "Testing Determinant:" << endl << endl;
	vector<double> negy[2] = {	{1,2} ,
								{3,4} };
	test.fill(2, 2, negy);
	test.print();
	cout << "Determinant:" << endl << endl;
	double d = test.determinant();
	cout << d << endl << endl;
	matrix egyseg(3);
	egyseg.print();
	cout << "Determinant:" << endl << endl;
	d = egyseg.determinant();
	cout << d << endl << endl;
	vector<double> ultimate[4] =	{{6 ,1 , 8 , 5 }, 
									{2 , 10, 7 , 13}, 
									{15, 4 , 12, 16}, 
									{0 , 11, 3 , 9 } }; //wolfram alfa szerint 2155
	matrix uj;
	uj.fill(4, 4, ultimate);
	uj.print();
	cout << "Determinant:" << endl << endl;
	d = uj.determinant();
	cout << d << endl << endl;
	cout << "Testing inverse:" << endl << endl;
	matrix inv1 = test.inverse();
	matrix inv2 = egyseg.inverse();
	matrix inv3 = uj.inverse();
	cout << test << inv1 << egyseg << inv2  << uj << inv3;
	inv2.plusat(69, 1, 1);
	cout << "Testing plusat:" << endl << endl << inv2;
	cout << "Matrix Test: Operations with Matrices\t ends..." << endl << endl;
	return 0;
}
int Matrix_Test_Further_Functions(void)
{
	matrix uj;
	vector<double> ultimate[4] = { {6 ,1 , 8 , 5 },
									{2 , 10, 7 , 13},
									{15, 4 , 12, 16},
									{0 , 11, 3 , 9 } };
	uj.fill(4, 4, ultimate);
	cout << "Matrix Test: Further functions\t begin..." << endl << endl << endl;
	uj.fill(4, 4, ultimate);
	double valami = uj.gauss();
	uj.print();
	cout << valami;
	cout << endl << endl << "Matrix Test: Further functions\t ends..." << endl << endl;
	return 0;
}
int Matrix_Test(void)
{
	int r = Matrix_Test_Basic();
	r += Matrix_Test_Operators();
	r += Matrix_Test_Operations();
	r += Matrix_Test_Further_Functions();
	return r;
}