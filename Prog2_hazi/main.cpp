#include "menu.h"


int main(void)
{
	
	string s1 = "input-LINNDIN.txt";
	string s2 = "output.txt";
	ifstream in(s1);
	ofstream out(s2);
	if (!(in.is_open())) {
		cerr << "Error opening file: " << s1 << endl;
		return 1;
	}
	if (!(out.is_open())) {
		cerr << "Error opening file: " << s2 << endl;
		return 1;
	}

	menu file_in(in, out);
	file_in.start();
	file_in.Run();
	
	menu manual_in;
	manual_in.start();
	manual_in.Run();
	//Graph_Test();
	//Matrix_Test();
	return 0;
}