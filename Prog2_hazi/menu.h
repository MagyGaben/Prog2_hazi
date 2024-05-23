#pragma once
#include "graph.h"
#include <fstream>
#include "Tester.h"
#include "memtrace.h"

using namespace std;

//mode enumeratio
enum mode
{
	DEFAULT,
	READFROMFILE,
	USER_IN_OUTPUT, //Mindenk�pp az utols� el�tti kell, hogy legyen
	TEST //Mindenk�pp az utols� kell, hogy legyen
};

//function enumeratio
enum function
{
	NONFUNC,
	MATRIXCALCULATOR,
	RESISTENCECALCULATOR,
	LINNDIN,//Mindenk�pp az utols� kell, hogy legyen
};

class menu
{
	bool Createdanewifofstreamsocodeleaks;	//true if I "creat" a new ifstream or ofstream so the program knows when it is leaking
	ostream* out;	//outstream
	istream* in;	//instream
	unsigned mode;	
	unsigned Function;
	graph* G;	//graph to be solved
	string dump;	//used when a file is read
	void Mode();	//private mode setter method
	void Func();	//private Function setter method
	void matrixcalc();	//private function
	void Build();	//private function
	void Tester();	//private function
public:
	//constructor
	menu(istream& InputConsole = std::cin, ostream& OutputConsole = std::cout) :	out(&OutputConsole), in(&InputConsole), mode(DEFAULT), Function(NONFUNC), G(), 
		Createdanewifofstreamsocodeleaks(false){}
	//constructor with files
	menu(ifstream& InputConsole, ofstream& OutputConsole) :	out(&OutputConsole), in(&InputConsole), mode(READFROMFILE), Function(NONFUNC), G(),
		Createdanewifofstreamsocodeleaks(false)
	{
		if (!((ifstream*)in)->is_open()) {
			cerr << "Error opening file: " << endl;
			mode = DEFAULT;
		}
		if (!((ofstream*)out)->is_open()) {
			cerr << "Error opening file: " << endl;
			mode = DEFAULT;
		}
	}
	//copy constructor
	menu(menu& other) :out(other.out), in(other.in), mode(other.getmode()), Function(other.getfunc()) { G = new graph(*other.G); }
	//destructor
	~menu();
	//getter of the Function attribute
	unsigned getfunc() const { return Function; }
	//getter of the mode attribute
	unsigned getmode() const { return mode; }
	//start method, used to set mode and function attributes
	void start();
	//Run method, used to navigate code with the given settings
	void Run();
};
