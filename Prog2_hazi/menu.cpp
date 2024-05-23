#include "menu.h"

using namespace std;

menu::~menu() // destructor of the menu
{

	delete G;
	if (mode == READFROMFILE)
	{
		((ofstream *)out)->close();
		((ifstream *)in)->close();
	}
	if (Createdanewifofstreamsocodeleaks)	// manual file input
	{
		delete in;
		delete out;
	}
}

void menu::start() // starting menu
{
	*out << "Welcome to Systems and Signals Solver!" << endl
		 << endl;
	if (mode != READFROMFILE)
		this->Mode();
	if (mode == DEFAULT)
		return;
	this->Func();
}

void menu::Mode() // In this menu you can select your mode
{
	*out << "Choose from the following modes:" << endl
		 << endl;

	*out << "\t" << DEFAULT << ". Exit" << endl;
	*out << "\t" << READFROMFILE << ". Read from File" << endl;
	*out << "\t" << USER_IN_OUTPUT << ". Interactive Problem Solver" << endl;
	/*3. Test Mode*/

	try
	{
		unsigned inpt = 255;
		*in >> inpt;
		if (inpt == 0)
			return;
		if (inpt > TEST)
			throw 1;
		this->mode = inpt;
	}
	catch (...)
	{
		*out << "Invalid input, use an integer between " << DEFAULT << " and " << USER_IN_OUTPUT << endl
			 << endl;
		this->Mode();
	}
	if (mode == READFROMFILE)
	{
		string ofs;
		string ifs;
		*out << "Name of the input file:";
		*in >> ifs;
		*out << "Name of the output file:";
		*in >> ofs;
		if (ifs == ofs)
		{
			cerr << "Invalid filename" << ifs << endl;
			mode = DEFAULT;
			return;
		}
		this->in = new ifstream(ifs);
		this->out = new ofstream(ofs);
		Createdanewifofstreamsocodeleaks = true;
		if (!(((ifstream*)(this->in))->is_open()))
		{
			cerr << "Error opening file: " << ifs << endl;
			mode = DEFAULT;
			return;
		}
		if (!(((ofstream*)(this->out))->is_open()))
		{
			cerr << "Error opening file: " << ofs << endl;
			mode = DEFAULT;
			return;
		}
	}
}

void menu::Func() // functions menu
{
	if (mode == TEST)
	{
		Function = 1;
		return;
	}
	*out << "Choose from the following functions:" << endl
		 << endl;

	*out << "\t" << NONFUNC << ". Exit" << endl;
	*out << "\t" << MATRIXCALCULATOR << ". Matrix Calculator" << endl;
	*out << "\t" << RESISTENCECALCULATOR << ". Resistence Calculator" << endl;
	*out << "\t" << LINNDIN << ". Lin-NDin Solver" << endl;
	try
	{
		if (mode == READFROMFILE)
			getline(*in, dump);
		unsigned inpt = 255;
		*in >> inpt;
		if (inpt > LINNDIN)
			throw 1;
		this->Function = inpt;
	}
	catch (...)
	{
		cout << "Invalid input, use an integer between " << NONFUNC << " and " << LINNDIN << endl
			 << endl;
	}
	*out << endl
		 << endl
		 << endl;
}

void menu::Run() // runs the function and mode of this menu
{
	if (mode == DEFAULT || Function == NONFUNC)
	{
		return;
	}
	unsigned vol_ncur;	//used in LINNDIN function, and can be used for more in the future
	if (this->mode == TEST)
		this->Tester();
	else
		switch (this->Function)
		{
		case MATRIXCALCULATOR:
			this->matrixcalc();
			break;
		case RESISTENCECALCULATOR:
			/*I calculate the resultant resistance with a dummy source
			UPGRADE IDEA: DFS solver*/
			this->Build();
			this->G->adde(new I_src(this->G->getv(this->G->getn()-1), this->G->getv(0), 1.0));
			if (mode == READFROMFILE)
			{
				getline(*in, dump);
				getline(*in, dump);
			}
			if (G->solve(*out, *in))
				*out << "The Resultant Resistence:\t" << (this->G->getedge(this->G->getb() - 1)->getU())/ (this->G->getedge(this->G->getb() - 1)->getI());
			break;
		case LINNDIN:
			this->Build();
			vol_ncur;
			*out << "Choose from the following answers:" << endl
				 << "\t 0.Current" << "\t 1. Voltage" << endl;
			if (mode == READFROMFILE)
			{
				getline(*in, dump);
				getline(*in, dump);
			}
			try
			{
				*in >> vol_ncur;
				if (vol_ncur > 1)
					throw 1;
				if (mode == READFROMFILE)
				{
					getline(*in, dump);
					getline(*in, dump);
				}
				if (G->solve(*out, *in))
				{
					if (vol_ncur == 1)
					{
						*out << "The index of the edge, with the voltage in question:" << endl;
						int a;
						if (mode == READFROMFILE)
						{
							getline(*in, dump);
							getline(*in, dump);
						}
						*in >> a;
						if (a >= G->getb())
							throw 2;
						*out << "The voltage in question:\t" << (double)((G->getedge(a))->getU());
					}
					else
					{
						*out << "The index of the edge, with the current in question:" << endl;
						int a;
						*in >> a;
						if (a >= G->getb())
							throw 2;
						*out << "The current in question:\t" << (double)((G->getedge(a))->getI()) << endl;
					}
				}
			}
			catch (int x)
			{
				if (x == 1)
					*out << "Invalid input, use 0 or 1 as an input!" << endl
						 << endl;
				if (x == 2)
					*out << "Invalid index" << endl
						 << endl;

				this->Run();
			}
			break;
		default:
			cerr << "something went wrong :(";
			break;
		}
	return;
}

void menu::matrixcalc() // matrix calculator menu
{
	*out << "Warning! The following function is only able to work with 3 matrices" << endl
		<< "use T for transpose G for Gauss elimination, D for determinant" << 
		endl << "and i for inverse:\t(only affecting Matrix2)" << endl
		 << "Press E to return, any to continue" << endl;
	matrix A;
	matrix B;
	matrix C;
	char c = 0;
	while ((c != EOF) && (c != 'E'))
	{
		*in >> c;
		if ((c == EOF) || (c == 'E'))
			break;
		*out << "Matrix3: f(Matrix1,matrix2)" << endl
			 << endl;
		int n, m;
		*out << "Matrix1: (n), (m), (data)" << endl
			 << endl;
		*in >> n >> m;
		A.fill(n, m, 0.0);	//constructing A
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				*in >> A.getData()[j][i];
			}
		}
		*out << A << endl;
		*out << "Matrix2: (n), (m), (data)" << endl
			 << endl;
		*in >> n >> m;
		B.fill(n, m, 0.0);	//constructing B
		for (size_t i = 0; i < m; i++)
		{
			for (size_t j = 0; j < n; j++)
			{
				*in >> (B.getData()[j])[i];
			}
		}
		*out << B << endl;
		*out << "Now what should we do with them? Remember:" << endl
			<< "use T for transpose and i for inverse(only affecting Matrix2)" << endl;
		*in >> c;
		switch (c)
		{
		case 'i':
			C = B.inverse();
			break;
		case '+':
			C = A + B;
			break;
		case '-':
			C = B.operator*(-1.0);
			C = A + B;
			break;
		case '*':
			C = A * B;
			break;
		case 'T':
			C = B.T();
			break;
		case 'G':
			C.fill(0,0,0.0);
			*out << B.gauss() << endl 
				<< endl 
				<< B << endl
				<< endl;
			break;
		case 'D':
			C.fill(0, 0, 0.0);
			*out << B.determinant() << endl
				<< endl;
			break;
		case 't':
			C = B.T();
			break;
		case 'g':
			C.fill(0, 0, 0.0);
			*out << B.gauss() << endl
				<< endl
				<< B << endl
				<< endl;
			break;
		case 'd':
			C.fill(0, 0, 0.0);
			*out << B.determinant() << endl
				<< endl;
			break;
		default:
			*out << "Invalid syntax" << endl
				 << endl;
			break;
		}
		if ((C.getm() != 0) && (C.getn() != 0))
		*out << "Solution:" << endl
			 << endl;
		*out << C;
	}
}

void menu::Build() // builds a graph
{
	G = new graph();
	int verticles = 0;
	*out << "Number of Verticles:" << endl;
	if (mode == READFROMFILE)
	{
		getline(*in, dump);
		getline(*in, dump);
	}
	*in >> verticles;
	Verticle *v;
	/*adding verticles*/
	for (size_t i = 0; i < verticles; i++)
	{
		v = new Verticle;
		G->addv(v);
	}
	*out << "Now you can add the dipoles(edges), note, to first give the verticle where the" << endl;
	*out << "voltage points from to another" << endl;
	unsigned v2 = 0;
	unsigned cat = 0;
	double d;
	Edge *e;
	if (mode == READFROMFILE)
	{
		getline(*in, dump);
		getline(*in, dump);
	}
	/*adding dipoles*/
	while (true)
	{
		*out << "Index of the first verticle(from):" << endl;
		*out << "(-1 to exit)" << endl;
		try
		{
			*in >> verticles;
			if (verticles == (-1))
				break;
			if (verticles >= G->getn())
				throw(string) "invalid syntax (first verticle), try again";
			*out << "Index of the second verticle(to):" << endl;
			*in >> v2;
			if (v2 >= G->getn())
				throw(string) "invalid syntax (second verticle), try again";
			if(this->Function != RESISTENCECALCULATOR)
			{

				*out << "Cathegory:" << endl;
				*out << "\tResistance:" << RESISTANCE << endl;
				*out << "\tTransformer:" << TRANSFORMER << endl;
				*out << "\tGyrator:" << GYRATOR << endl;
				*out << "\tVoltage Source:" << VOLTAGE << endl;
				*out << "\tCurrent Source:" << CURRENT << endl;
				*in >> cat;
				if (cat > CURRENT)
					throw(string)"invalid syntax (cathegory), try again";
				switch (cat)
				{
				case RESISTANCE:
					*out << "Resistence value:" << endl;
					*in >> d;
					e = new Resistance(G->getv(verticles), G->getv(v2), d);
					G->adde(e);
					break;
				case VOLTAGE:
					*out << "Voltage value:" << endl;
					*in >> d;
					e = new V_src(G->getv(verticles), G->getv(v2), d);
					G->adde(e);
					break;
				case CURRENT:
					*out << "Current value:" << endl;
					*in >> d;
					e = new I_src(G->getv(verticles), G->getv(v2), d);
					G->adde(e);
					break;
				case TRANSFORMER:
					try
					{
						*out << "Turns ratio:" << endl;
						*in >> d;
						G->adde(new Transformer(G->getv(verticles), G->getv(v2), d));
						*out << "The index of the first verticle of the other Transformer:" << endl;
						*in >> verticles;
						if (verticles >= G->getn())
							throw(string)"invalid syntax making Transformer (first verticle), try again";
						*out << "Index of the second verticle of the other Transformer:" << endl;
						*in >> v2;
						if (v2 >= G->getn())
							throw(string)"invalid syntax making Transformer (second verticle), try again";
						G->adde(new Transformer(G->getv(verticles), G->getv(v2), (1.0) / d, (Transformer*)G->getedge((G->getb() - 1))));
						((Transformer*)G->getedge(G->getb() - 2))->setoth((Transformer*)G->getedge((G->getb() - 1)));
					}
					catch (string s) 
					{
						G->deledge(G->getb() - 1);
						*out << s;
					}
					break;
				case GYRATOR:
					try
					{
						*out << "Gyrator resistence:" << endl;
						*in >> d;
						G->adde(new Gyrator(G->getv(verticles), G->getv(v2), d));
						*out << "The index of the first verticle of the other Gyrator:" << endl;
						*in >> verticles;
						if (verticles >= G->getn())
							throw(string)"invalid syntax making Gyrator (first verticle), try again";
						*out << "Index of the second verticle of the other Gyrator:" << endl;
						*in >> v2;
						if (v2 >= G->getn())
							throw(string)"invalid syntax making Gyrator (second verticle), try again";
						G->adde(new Gyrator(G->getv(verticles), G->getv(v2), (-1.0) * d, (Gyrator*)G->getedge((G->getb() - 1))));
						((Gyrator*)G->getedge(G->getb() - 2))->setoth((Gyrator*)G->getedge((G->getb() - 1)));
					}
					catch (string s)
					{
						G->deledge(G->getb() - 1);
						*out << s;
					}
					break;
				default:
					throw(string)"Csupaszvezetek nem dipolus";
					break;
				}
			}
			else
			{
				*out << "Resistence value:" << endl;
				*in >> d;
				e = new Resistance(G->getv(verticles), G->getv(v2), d);
				G->adde(e);
			}
		}
		catch (string s)
		{
			*out << s << endl;
		}
	}
	return;
}

void menu::Tester() // calls tester menu
{
	Matrix_Test();
	Graph_Test();
}
