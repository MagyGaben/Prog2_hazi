#include "matrix.h"
#include <math.h>

matrix::matrix()	//Constructor without values
{
	n = 0; m = 0;
	data = nullptr;
}

matrix::matrix(int n, int m, double** data) //Constructor with values
{
	this->n = n;
	this->m = m;
	this->data = data;
	this->data = data;
}

matrix::matrix(int Size)	//Size sized identity matrix
{
	n = Size; m = Size;
	this->data = new double* [Size];
	for (int i = 0; i < Size; i++)
	{
		this->data[i] = new double[Size];
	}


	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (i == j) this->data[i][j] = 1.0;
			else this->data[i][j] = 0.0;
		}
	}
}

matrix::matrix(matrix& ref)	//Copy Constructor
{
	*this = ref;
}

matrix::~matrix() //Destructor
{
	for (int i = 0; i < n; i++)
	{
		delete[] data[i];
	}
	delete[] data;
	data = nullptr;	//enélkül hibát dob néhány függvény
	n = 0;
	m = 0;
}

bool matrix::fill(int n, int m, double* data)	//Array to matrix filler
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}	//Avoiding memory leak

	//Creating new matrix
	this->data = new double* [n];
	for (int i = 0; i < n; i++)
	{
		this->data[i] = new double[m];
	}

	//Filling matrix with given values
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i][j] = data[(i * m) + j];
		}
	}
	this->n = n;
	this->m = m;
	return true;
}

bool matrix::fill(int n, int m, double** data)	//2 dimension array to matrix filler
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}	//Avoiding memory leak

	//Creating new matrix
	this->data = new double* [n];
	for (int i = 0; i < n; i++)
	{
		this->data[i] = new double[m];
	}

	//Filling matrix with given values
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i][j] = data[i][j];
		}
	}
	this->n = n;
	this->m = m;
	return true;
}

bool matrix::fill(int n, int m, double value) //Fills matrix with one value
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}	//Avoiding memory leak

	//Creating new matrix
	this->data = new double* [n];
	for (int i = 0; i < n; i++)
	{
		this->data[i] = new double[m];
	}

	//Filling matrix with given value
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i][j] = value;
		}
	}
	this->n = n;
	this->m = m;
	return true;
}

bool matrix::null()	//erase values from matrix, fills it with 0
{
	if (data == nullptr) return false;
	this->fill(n, m, 0.0);
	return true;
}

bool matrix::null(int n, int m)	//fills matrix with zeros if the matrix has no values yet
{
	if (data != nullptr) return false;
	this->fill(n, m, 0.0);
	return true;
}

matrix& matrix::del_row(int ezt) const	//returns this matrix without the selected row
{
	matrix* sol = new matrix;
	if (this->data == nullptr)
	{
		return *sol;
	}
	sol->n = this->n - 1;
	sol->m = this->m;
	sol->data = new double* [n];
	for (int i = 0; i < n - 1;i++)
	{
		sol->data[i] = new double[m];
		for (int j = 0; j < m; j++)
		{

			sol->data[i][j] = (this->data[i + int(i >= ezt)][(j)]);

		}

	}
	return *sol;
}

matrix& matrix::del_col(int ezt) const	//returns this matrix without the selected column
{
	matrix* sol = new matrix;
	if (this->data == nullptr)
	{
		return *sol;
	}
	sol->n = this->n;
	sol->m = this->m - 1;
	sol->data = new double* [n];
	for (int i = 0; i < n;i++)
	{
		sol->data[i] = new double[m - 1];
		for (int j = 0; j < (m - 1); j++)
		{

			sol->data[i][j] = (this->data[i][(j + int(j >= ezt))]);

		}

	}
	return *sol;
}

void matrix::print(std::ostream& out)	//prints matrix to the selected output, if nothing selected, uses standard output
{
	out << "row:\t" << n << std::endl;
	out << "column:\t" << m << std::endl << std::endl;
	if (data == nullptr)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			out << data[i][j] << ", ";
		}
		out << std::endl;
	}
	out << std::endl;
	return;
}

matrix& matrix::T() const	//returns transpose of matrix
{
	matrix* sol = new matrix;
	sol->m = this->n;
	sol->n = this->m;
	sol->data = new double* [sol->n];
	for (size_t i = 0; i < m; i++)
	{
		sol->data[i] = new double[sol->m];
		for (size_t j = 0; j < n; j++)
		{
			sol->data[i][j] = this->data[j][i];
		}
	}
	return *sol;
}

double matrix::determinant() const	//returns determinant of matrix
{
	//shortcuts, necessary for recursion
	if (n != m)return 0.0;
	if (n == 1) return data[0][0];
	if (n == 2) return (data[0][0] * data[1][1] - data[0][1] * data[1][0]);
	double sol = 0.0;
	int j = -1;
	for (size_t i = 0; i < n; i++)
	{
		j *= -1;
		double sum = data[0][i] * j;
		matrix tmp = this->del_row(0);
		matrix rex = tmp.del_col(i);
		sum *= rex.determinant();
		sol += sum;
	}
	return sol;
}

matrix& matrix::inverse() const	//returns inverse matrix of this
{
	double det = (1 / (this->determinant()));
	matrix* sol = new matrix;
	if ((this->determinant()) == 0.0) return *sol;
	sol->data = new double* [n];
	for (size_t i = 0; i < n; i++)
	{
		sol->data[i] = new double[m];
		for (size_t j = 0; j < m; j++)
		{
			int k = pow(-1, i + j);
			matrix tmp = this->del_row(i);
			matrix rex = tmp.del_col(j);
			sol->data[i][j] = rex.determinant() * k;
		}
	}	//adjoint matrix

	sol->n = n;
	sol->m = m;

	*sol = *sol * det;
	*sol = sol->T();
	return *sol;
}



matrix& matrix::operator+(const matrix& theother) const	//addition of matrices
{
	matrix* sol = new matrix;
	if (this->n != theother.n || this->m != theother.m)
	{
		return *sol;
	}
	sol->n = n;
	sol->m = m;
	sol->data = new double* [n];
	for (size_t i = 0; i < n; i++)
	{
		sol->data[i] = new double[m];
		for (size_t j = 0; j < m; j++)
		{
			sol->data[i][j] = theother.data[i][j] + this->data[i][j];
		}
	}
	return *sol;
}

matrix& matrix::operator*(const matrix& theother) const	//multiplication of matrices
{
	matrix* sol = new matrix;
	if (this->n != theother.m || this->m != theother.n)
	{
		return *sol;
	}
	sol->n = this->n;
	sol->m = this->n;
	sol->data = new double* [n];
	for (size_t i = 0; i < n; i++)
	{
		sol->data[i] = new double[n];
		for (size_t j = 0; j < n; j++)
		{
			double c = 0;
			for (size_t l = 0; l < m; l++)
			{
				c += this->data[i][l] * theother.data[l][j];
			}

			sol->data[i][j] = c;
		}
	}
	return *sol;
}

matrix& matrix::operator*(const double scalar) const	//multiplication of matrices with scalar
{
	matrix* sol = new matrix;
	sol->n = this->n;
	sol->m = this->m;
	sol->data = new double* [n];
	for (size_t i = 0; i < n; i++)
	{
		sol->data[i] = new double[m];
		for (size_t j = 0; j < m; j++)
		{
			sol->data[i][j] = scalar * this->data[i][j];
		}
	}
	return *sol;
}

void matrix::operator=(const matrix& theother) /*Currently out of useage*/
{
	this->n = theother.n;
	this->m = theother.m;
	fill(theother.n, theother.m, theother.data);
}

matrix& matrix::operator&(const matrix& theother) const	//copies another matrix right nex to this
{
	matrix* sol = new matrix;
	if (this->n != theother.n)
	{
		return *sol;
	}
	sol->n = this->n;
	sol->m = this->m + theother.m;
	sol->data = new double* [n];
	for (size_t i = 0; i < n; i++)
	{
		sol->data[i] = new double[this->m + theother.m];
		for (size_t j = 0; j < this->m; j++)
		{
			sol->data[i][j] = this->data[i][j];
		}
		for (size_t j = 0; j < theother.m; j++)
		{
			sol->data[i][j + this->m] = theother.data[i][j];
		}
	}

	return*sol;
}
