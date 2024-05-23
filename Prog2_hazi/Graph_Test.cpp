#include "graph.h"

int Graph_Test(void)
{
	double U = 10.0;
	double R = 2.5;
	double n = 5.0;
	double r = 30;
	cout << endl << "Graph Test began..." << endl;
	graph G;
	G.addv(new Verticle);
	G.addv(new Verticle);
	G.addv(new Verticle);
	G.adde(new V_src(G.getv(0), G.getv(2), U));
	G.adde(new Resistance(G.getv(0), G.getv(1), R));
	G.adde(new Resistance(G.getv(1), G.getv(2), 2*R));
	cout << endl;
	cout << "U0:" << ((V_src*)G.getedge(0))->getV() << endl;
	cout << "R1:" << ((Resistance*)G.getedge(1))->getR() << endl;
	cout << "R2:" << ((Resistance*)G.getedge(2))->getR() << endl << endl;
	cout << "Making solution..." << endl;
	cout << endl;
	ifstream in("GRAPHTEST.txt");
	G.solve(cout, in);
	cout << endl;
	for (size_t i = 0; i < G.getb(); i++)
	{
	cout<< G.getedge(i)->getType() << "\tI:" << G.getedge(i)->getI() << "\tU:" << G.getedge(i)->getU() <<endl;
	}
	cout << endl << endl << "Transformer Test Starts" << endl << endl;
	graph T;
	T.addv(new Verticle);
	T.addv(new Verticle);
	T.addv(new Verticle);
	T.adde(new V_src(T.getv(0), T.getv(1), U));
	T.adde(new Transformer(T.getv(1), T.getv(0), n));
	T.adde(new Transformer(T.getv(2), T.getv(0), 1/n, (Transformer*)T.getedge(1)));
	((Transformer*)T.getedge(1))->setoth((Transformer*)T.getedge(2));
	T.adde(new Resistance(T.getv(0), T.getv(2), R));
	T.solve(cout, in);
	cout << endl;
	for (size_t i = 0; i < T.getb(); i++)
	{
		cout << T.getedge(i)->getType() << "\tI:" << T.getedge(i)->getI() << "\tU:" << T.getedge(i)->getU() << endl;
	}

	cout << endl << endl << "Gyrator Test Starts" << endl << endl;
	graph Q;
	Q.addv(new Verticle);
	Q.addv(new Verticle);
	Q.addv(new Verticle);
	Q.adde(new V_src(Q.getv(0), Q.getv(1), U));
	Q.adde(new Gyrator(Q.getv(1), Q.getv(0), r));
	Q.adde(new Gyrator(Q.getv(2), Q.getv(0), (-1.0) * r, (Gyrator*)Q.getedge(1)));
	((Gyrator*)Q.getedge(1))->setoth((Gyrator*)Q.getedge(2));
	Q.adde(new Resistance(Q.getv(0), Q.getv(2), R));
	Q.solve(cout, in);
	cout << endl;
	for (size_t i = 0; i < Q.getb(); i++)
	{
		cout << Q.getedge(i)->getType() << "\tI:" << Q.getedge(i)->getI() << "\tU:" << Q.getedge(i)->getU() << endl;
	}

	cout << endl << "Graph Test ends..." << endl;
	return 0;
}