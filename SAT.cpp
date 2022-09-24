// SAT.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "Formul.h"
#include "DPLL.h"
#include "Tools.h"
#include "Genetic_Algorithm.h"
#include "WalkSat.h"
#include <iostream>

#include <fstream>

using namespace std;


void DPLL_test(Formula& F)
{
	Timer T;
	cout << "DPLL:" << endl;
	SATDPLL solver(F);
	T.reset();
	solver.solve();
	solver.result(false);  //false means no solution output
	ofstream out("CNF_SAT_OUT.csv", ios::app);
	out << "DPLL ," << T.elapsed() << ",";
	out.close();

}
void Genetic_Algorithm_test(Formula& F)
{
	Timer T;
	cout << "Genetic_Algorithm:" << endl;
	Genetic_Algorithm GA(F);
	T.reset();
	for (int i = 0; i < 10; i++) {
		cout << ".";
		GA.solve();
		GA.result(false); //false means no solution output
	}
	cout << endl;
	ofstream out("CNF_SAT_OUT.csv", ios::app);
	out << "Genetic_Algorithm ," << T.elapsed() / 10.0 << ",";
	out.close();
}
void WalkSat_test(Formula& F)
{
	Timer T;
	cout << "WalkSat:" << endl;
	WalkSat WS(F);
	T.reset();
	for (int i = 0; i < 10; i++) {
		cout << ".";
		WS.solve();
		WS.result(false); //false means no solution output
	}
	cout << endl;
	ofstream out("CNF_SAT_OUT.csv", ios::app);
	out << "WalkSat ," << T.elapsed() / 10.0 << ",";

	time_t now = time(0);    //current date and time
#ifdef _WIN32
	char dt[100];
	ctime_s(dt,100,&now);
#elif defined(__GNUC__) || defined(__GNUG__)
	char* dt = ctime(&now);
#endif
	out << dt << endl; 

	out.close();
}

int main() {

	initcsv();
	
#ifdef _WIN32
	
	const fs::path root = "HARD CNF Formulas\\";
	cout << "instance path: " << root << endl;
	vector<fs::path> files;
	getallfiles(root, files);
	
#elif defined(__GNUC__) || defined(__GNUG__)
	string path = "./CNFFormulas/";
	cout << "instance path: " << path << endl;
	vector<string> files;
	getallfiles(path, files);
#endif

	for (auto &s : files) {
		
#ifdef _WIN32
		cout << s.generic_string() << endl;
		Timer T;
		T.reset();
		Formula F(s.generic_string());
		ofstream out("CNF_SAT_OUT.csv", ios::app);
		out << s.generic_string() << ","<< T.elapsed()<<",";
		out.close();
#elif defined(__GNUC__) || defined(__GNUG__)

		cout << s << endl;
		Timer T;
		T.reset();
		Formula F(s);
		ofstream out("CNF_SAT_OUT.csv", ios::app);
		out << s << "," << T.elapsed() << ",";
		out.close();
#endif
		
		//F.show();
		DPLL_test(F);
		Genetic_Algorithm_test(F);
		WalkSat_test(F);
		
	}
	cout << "all instances have been tested." << endl;
	return 0;
}


