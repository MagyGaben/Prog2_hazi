#include "memtrace.h"
#include "matrix.h"
#include <math.h>
using namespace std;

matrix::matrix()	//Constructor without values
{
	n = 0; m = 0;
	data = nullptr;
}

matrix::matrix(int n, int m, vector<double>* data) //Constructor with values
{
	this->n = n;
	this->m = m;
	this->data = data;
}

matrix::matrix(int Size)	//Size sized identity matrix
{
	n = Size; m = Size;
	this->data = new vector<double>[n];
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
		{
			if (i == j) this->data[i].push_back(1.0);
			else this->data[i].push_back(0.0);
		}
	}
}

matrix::matrix(const matrix& ref) : n(ref.n), m(ref.m)	//Copy Constructor
{
	this->data = new vector<double>[ref.n];

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i].push_back(ref.data[i][j]);
		}
	}
}

matrix::matrix(vector<double> v) : n(1), m(v.size())
{
	this->data = new vector<double>[1];
	data[0] = v;
	matrix tmp = this->T();
	*this = tmp;
}

matrix::~matrix() //Destructor
{
	delete[] data;
	data = nullptr;	//needed for some functions
	n = 0;
	m = 0;
}

int matrix::getn() const
{
	return n;
}

int matrix::getm() const
{
	return m;
}

vector<double>* matrix::getData() const
{
	return data;
}

bool matrix::fill(int n, int m, vector<double> data)	//Array to matrix filler
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}	//Avoiding memory leak

	//Creating new matrix
	this->data = new vector<double>[n];

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

bool matrix::fill(const int n, const int m, vector<double>* Data)	//2 dimension array to matrix filler
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}	//Avoiding memory leak

	//Creating new matrix
	vector<double>* dat = new vector<double>[n];
	this->data = dat;

	//Filling matrix with given values
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i].push_back(Data[i][j]);
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
	this->data = new vector<double>[n];

	//Filling matrix with given value
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			this->data[i].push_back(value);
		}
	}
	this->n = n;
	this->m = m;
	return true;
}

bool matrix::null()	//erase values from matrix, fills it with 0
{
	this->fill(this->n, this->m, 0.0);
	return true;
}

bool matrix::null(int n, int m)	//fills matrix with zeros if the matrix has no values yet
{
	this->fill(n, m, 0.0);
	return true;
}

matrix matrix::del_row(int ezt) const	//returns this matrix without the selected row
{
	vector<double>* dat = new vector<double>[this->n - 1];
	for (int i = 0; i < n - 1;i++)
	{
		for (int j = 0; j < m; j++)
		{

			dat[i].push_back(this->data[i + int(i >= ezt)][(j)]);

		}

	}
	return matrix((this->n) - 1, this->m, dat);
}

matrix matrix::del_col(int ezt) const	//returns this matrix without the selected column
{
	vector<double>* dat = new vector<double>[this->n];
	for (int i = 0; i < n;i++)
	{
		for (int j = 0; j < (m - 1); j++)
		{

			dat[i].push_back(this->data[i][(j + int(j >= ezt))]);

		}

	}
	return matrix(n, m - 1, dat);
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
			out << data[i][j] << ",\t";
		}
		out << std::endl;
	}
	out << std::endl;
	return;
}

double matrix::gauss()
{
	double ret = 1.0;
	double tmp;
	int j = 0;
	matrix temp;
	for (size_t i = 0; i < n; i++)
	{	
		while ((this->data[i][i]) == 0.0)
		{
			temp = this->del_col(0);
			for (size_t i = 0; i < n; i++)
			{
				(temp.data[i]).push_back(this->data[i][0]);
			}
			temp.m++;
			j++;
			if (j == n+1) 
				return 0.0;
			ret *= pow(-1, n + 1);
			this->fill(n, m, temp.data);
		}
		tmp = data[i][i];
		ret *= tmp;
		j = 0;
		for (size_t j = 0; j < m; j++)
		{
			data[i][j] /= tmp;
		}
		for (size_t k = (i + 1); k < n; k++)
		{
			tmp = data[k][i];
			for (size_t j = 0; j < m; j++)
			{
				data[k][j] -= tmp * data[i][j];
			}

		}
	}
	return ret;
}

matrix matrix::T() const	//returns transpose of matrix
{
	vector<double>* dat = new vector<double>[this->m];
	for (size_t i = 0; i < m; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			dat[i].push_back(this->data[j][i]);
		}
	}
	return matrix(m, n, dat);
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
		rex.~matrix();
		tmp.~matrix();
		sol += sum;
	}
	return sol;
}

double matrix::qdeterminant() const
{
	if (n < 3) return this->determinant();
	matrix tmp(*this);
	double d = tmp.gauss();
	tmp.~matrix();
	return d;
}

matrix matrix::inverse() const	//returns inverse matrix of this
{
	//Inv(A) = Transpose(A*)  
	try
	{
		double deter = this->qdeterminant();
		if (deter == 0.0)
		{
			throw (string)"Math Error: Zero Determinant";
		}
	double det = (1 / (deter));
		if (n == 1)
		{
			vector<double>* temp = new vector<double>[1];
			temp[0].resize(1);
			temp[0][0] = (det);
			return matrix(n, m, temp);
		}
		vector<double>* dat = new vector<double>[this->n];//adjoint matrix
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				int k = pow(-1, i + j);
				matrix tmp = this->del_row(i);
				matrix rex = tmp.del_col(j);
				dat[i].push_back(rex.qdeterminant() * k);
				tmp.~matrix();
				rex.~matrix();
			}
		}	//adjoint matrix


		matrix tmp(n, m, dat);
		tmp = tmp.T();
		vector<double>* ret = new vector<double>[tmp.n];
		for (size_t i = 0; i < n; i++)
		{
			for (size_t j = 0; j < m; j++)
			{
				ret[i].push_back(tmp.data[i][j]*det);
			}
		}

		return matrix(n, m, ret);
	}
	catch (string s)
	{
		cout << s;
	}
	return matrix();
}

void matrix::plusat(const double d, const unsigned i, const unsigned j)
{
	this->data[i][j] += d;
}



matrix matrix::operator+(const matrix& theother) const	//addition of matrices
{
	vector<double>* dat;
	if (this->n != theother.n || this->m != theother.m)
	{
		return matrix();
	}
	dat = new vector<double>[this->n];
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			dat[i].push_back(theother.data[i][j] + this->data[i][j]);
		}
	}
	return matrix(n, m, dat);
}

matrix matrix::operator*(const matrix& theother) const 	//multiplication of matrices
{
	if (this->m != theother.n)
	{
		return matrix();
	}
	vector<double>* dat = new vector<double>[this->n];
	double tmp;
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < theother.m; j++)
		{
			tmp = 0;
			for (size_t k = 0; k < this->m; k++)
			{
				tmp += this->data[i][k] * theother.data[k][j];
			}
			dat[i].push_back(tmp);
		}
	}
	return matrix(this->n, theother.m, dat);
}

matrix matrix::operator*(const vector<double>& theother) const
{
	matrix tmp(theother);
	return *this*tmp;
}

matrix matrix::operator*(const double scalar) const 	//multiplication of matrices with scalar
{
	vector<double >* dat = new vector<double>[this->n];
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			dat[i].push_back(scalar * this->data[i][j]);
		}
	}
	return matrix(n, m, dat);
}

void matrix::operator=(const matrix& theother)
{
	if (this->data != nullptr)
	{
		this->~matrix();
	}
	this->n = theother.n;
	this->m = theother.m;
	this->data = new vector<double>[this->n];
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < m; j++)
		{
			this->data[i].push_back(theother.data[i][j]);
		}
	}
}

vector<double> matrix::operator[](const unsigned i) const
{
	return data[i];
}



matrix matrix::operator&(const matrix& theother) const	//copies another matrix right nex to this
{
	vector<double>* dat = new vector<double>[this->n];
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < this->m; j++)
		{
			dat[i].push_back(this->data[i][j]);
		}
		for (size_t j = 0; j < theother.m; j++)
		{
			dat[i].push_back(theother.data[i][j]);
		}
	}
	return matrix(this->n, this->m + theother.m, dat);
}

ostream& operator<<(ostream& out, const matrix& op)
{
	if ((op.m == 0) || (op.n == 0)) return out;
	out << "row:\t" << op.n << std::endl;
	out << "column:\t" << op.m << std::endl << std::endl;
	if (op.data == nullptr)
	{
		return out;
	}
	for (int i = 0; i < op.n; i++)
	{
		for (int j = 0; j < op.m; j++)
		{
			out << op.data[i][j] << ", ";
		}
		out << endl;
	}
	out << endl;
	return out;
}
