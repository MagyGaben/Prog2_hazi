#include "graph.h"

graph::graph(unsigned n) :n(n), E(nullptr), l(0), b(0)	//constructor for a graph
{
	Verticle* a = new Verticle;
	for (int i = 0; i < n; i++)
	{
		V.push_back(a);
	}
}

graph::graph(graph& other) :n(other.n), b(other.b), l(other.b)	//copy constructor for a graph
{
	for (size_t i = 0; i < n; i++)
	{
		this->V[i] = other.V[i];
	}
	for (size_t i = 0; i < b; i++)
	{
		this->E[i] = other.E[i];
	}
}

graph::~graph()	//Destructor for a graph
{
	if(n != 0)
	{
	for (size_t i = 0; i < n; i++)
	{
		delete V[i];
	}
	}
	if(b != 0)
	{
	for (size_t i = 0; i < b; i++)
	{
		delete E[i];
	}
		delete[] E;
		E = nullptr;
	}
}

bool graph::addv(Verticle* v)	//adds a new verticle
{
	n++;
	V.push_back(v);
	setl();
	return true;
}

bool graph::adde(Edge* e)	//adds a new edge
{
	try
	{
		if ((isverticle(e->geta()) < n) && (isverticle(e->getb()) < n))
		{
			this->b++;
			Edge** tmp = new Edge * [this->b];
			for (size_t i = 0; i < this->b-1; i++)
			{
				tmp[i] = E[i];
			}
			tmp[this->b-1] = e;
			if (E != nullptr)
			delete[] E;
			E = tmp;
			return true;
		}
		throw (string)"Invalid verticle";
	}
	catch (string s)
	{
		cout << s << endl;
		return false;
	}
		setl();
		return true;
}

void graph::deledge(unsigned i)
{
	if (E == nullptr) return;
	b--;
	Edge** tmp = new Edge*[(this->b)];
	for (size_t j = 0; j < b; j++)
	{
		if (j<i)
		{
			tmp[j] = this->E[j];
		}
		else 
		{
			tmp[j] = this->E[j + 1];
		}
	}
	delete[] E;
	E = tmp;
	setl();
}

void graph::setl()	//refresh the number of loops
{
	l = b - n + 1;
}

 unsigned graph::getn() const	//getter for verticle number
{
	return n;
}

 unsigned graph::getb() const	//getter for branch number
{
	return b;
}

 unsigned graph::getl()	//getter for loop number
{
	this->setl();
	return l;
}

 Verticle* graph::getv(unsigned i) const	//getter for the verticle in index
{
	return V[i];
}

 Edge* graph::getedge(unsigned i) const	//getter for the edge in index
{
	return E[i];
}

unsigned graph::isverticle(Verticle* v)	//returns if the verticle is part of the graph
{
	for (size_t i = 0; i < n; i++)
	{
		if (this->V[i] == v) return i;
	}
	return n;
}

unsigned graph::isedge(Edge* e)
{
	for (size_t i = 0; i < b; i++)
	{
		if (this->E[i] == e) return i;
	}
	return b;
}

bool graph::solve(ostream& out, istream& in)		//calculates the currents and potentials of the graph
{
	/*
	The full equations matrix : A	(mx)
	The voltages and currents vectors:	x (volcur)
	The Vectors on the right size:	y (sol)
					A*x = y
					x = inv(A) * y
	*/

	unsigned t;

	this->setl();
	matrix mx(2 * b);	//A
	mx.null();
	vector<double> sol(2 * b, 0.0);	//y

	/*Initialization done*/
	for (size_t i = 0; i < b; i++)	//Equations from charteristics
	{
		switch (this->E[i]->charteristics())
		{
		case CURRENT:
			mx.plusat( 1,i, i+b);
			sol[i] = ((I_src*)E[i])->getI();
			break;
			break;
		case VOLTAGE:
			mx.plusat(1, i, i);
			sol[i] = ((V_src*)E[i])->getV();
			break;
		case RESISTANCE:
			mx.plusat(1, i, i);
			mx.plusat((-1.0 * ((Resistance*)E[i])->getR()), i, i + b);
			break;
		case TRANSFORMER:
			mx.plusat(1, i, i);
			mx.plusat(1, i, i + b);
			t = isedge(((Transformer*)(this->E[i]))->getoth());
			mx.plusat(((Transformer*)(this->E[i]))->getn(), i, t);
			mx.plusat((-1.0) / ((Transformer*)(this->E[i]))->getn(), i, t + b);
			break;
		case GYRATOR:
			mx.plusat(-1, i, isedge(((Gyrator*)(this->E[i]))->getoth()));
			mx.plusat(((Gyrator*)(this->E[i]))->getr(), i, i + b);
			break;
		default:
			break;
		}
	}
	for (size_t i = 0; i < n-1; i++)	//Equations from verticles
	{
		if (V[i]->getd() < 2)
		{
			out << "The system is not regular";
			return false;
		}
		for (size_t j = 0; j < V[i]->getd(); j++)
		{
			Edge* edzs = (V[i]->getEdgeArray())[j];
			if (isedge(edzs) >= b)
			{
				out << "The system is not regular:\t" << "Failed with edge index" << isedge(edzs) << endl;
				return false;
			}
			if (edzs->geta() == V[i])
			{
				mx.plusat( 1,i+b, b + (isedge(edzs)));
			} else
				mx.plusat(-1, i+b, b + (isedge(edzs)));
			if (edzs->charteristics() == VOLTAGE || edzs->charteristics() == CURRENT)
				((mx.getData())[i + b])[b + isedge(edzs)] *= (-1.0);
		}
	}
	out << "n:\t" << this->n << endl;
	out << "b:\t" << this->b << endl;
	out << "l:\t" << this->l << endl;
	out << endl << endl << endl;
	out << "Give the index of edges to make " << this->l << " loops";
	out << endl << endl;
	for (size_t i = 0; i < l; i++)	//equations from loops
	{								//Upgrade idea: making this automatic
		out << "Loop " << i + 1 << ". : " << endl;
		out << "How many branches? " << endl;
		unsigned uns = 0;
		try
		{
			in >> uns;
			if (uns == 0)
			{
				throw 0;
			}
		}
		catch (int x)
		{
			out << "invalid input try again" << endl;
			i--;
		}
		unsigned a = 0;
		out << "Indexes of the branches: " << endl;
		for (size_t j = 0; j < uns; j++)
		{
			try 
			{
				in >> a;
				if (a > (2 * b)) throw (-1);
				mx.plusat(1,b + n - 1 + i, a);
			}
			catch (int x)
			{
				out << "invalid input try again" << endl;
				j--;
			}
		}
	}
	try
	{
if (mx.qdeterminant() == 0.0) 
		{
			throw (string)"The loops are not independent, or their reference direction is wrong";
		}
		matrix volcur = mx.inverse() * sol;		//x = inv(A)*y

		if (volcur.getn() != (2 * b)) throw (string)"Something went wrong";				//There must be 2*b values
		for (size_t i = 0; i < b; i++)
		{
			E[i]->setU(((volcur[i])[0]));
			E[i]->setI(((volcur[i + b])[0]));
		}

		return true;
	}
	catch(string x)
	{
		out << x << endl;
		return false;
	}







	//V[0]->setPot(0.0);
	//V[0]->setStatus(true);
	//unsigned temp;
	//matrix equations_matrix(n);
	//equations_matrix.null();
	//vector<double> inflow(n, 0);
	//vector<double> VoltVec(n, 0);
	//matrix potvec;
	//unsigned compare = n;
	//double dbl;
	//cout << "\tFirst steps done, now identify voltage matrix..." << endl;
	//for (size_t i = 1; i < n; i++)
	//{
	//	for (size_t j = 0; j < V[i]->getd(); j++)
	//	{
	//		if (V[i]->getEdgeArray()[j]->charteristics() == VOLTAGE)
	//		{
	//			dbl = ((V_src*)(V[i]->getEdgeArray()[j]))->getV();
	//			if (isverticle(((V[i]->getEdgeArray()[j]))->geta()) == 0)
	//			{
	//				VoltVec[isverticle(((V[i]->getEdgeArray()[j]))->getb())] = (-1.0) * dbl;
	//			}
	//			else
	//			{
	//				VoltVec[isverticle(((V[i]->getEdgeArray()[j]))->geta())] = dbl;
	//			}
	//		}
	//	}
	//}
	//cout << "\tMaking solution matrix..." << endl;
	//for (size_t i = 1; i < n; i++)
	//{
	//	for (size_t j = 0; j < V[i]->getd(); j++)
	//	{
	//		compare = isverticle(((V[i]->getEdgeArray()[j]))->geta()); //Ezt majd t�r�ld

	//		temp = V[i]->getEdgeArray()[j]->charteristics();
	//		switch (temp)
	//		{
	//		case CURRENT:
	//			inflow[i] = ((I_src*)(V[i]->getEdgeArray()[j]))->getI();
	//			if (compare == i) inflow[i] *= -1;
	//			break;
	//		case RESISTANCE:
	//			dbl = 1.0 / ((Resistance*)(V[i]->getEdgeArray()[j]))->getR();
	//			equations_matrix.plusat(dbl, i, i);
	//			compare = isverticle(((V[i]->getEdgeArray()[j]))->geta());
	//			if (compare == i)
	//				compare = isverticle(((V[i]->getEdgeArray()[j]))->getb());
	//			equations_matrix.plusat((-1) * dbl, i, compare);
	//				break;
	//		default:
	//			break;
	//		}

	//	}
	//}
	//cout << "\tInverse solution matrix..." << endl;
	//matrix eq = equations_matrix.del_col(0).del_row(0);
	//eq = eq.inverse();
	//inflow.erase(inflow.begin());
	//VoltVec.erase(VoltVec.begin());
	//matrix voltmx(VoltVec);
	//cout << "\tSolving right side equations..." << endl;
	//potvec = eq * inflow;
	//potvec = potvec + voltmx;
	//cout << "\tSet potentials of verticles..." << endl;
	//for (size_t i = 0; i < n-1; i++)
	//{
	//	V[i+1]->setPot(potvec.getData()[i][0]);
	//}
	//cout << "\tReturning..." << endl;
	//return true;
}
