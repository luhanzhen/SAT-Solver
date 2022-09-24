#include "WalkSat.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>
#include <cstdlib>

WalkSat::WalkSat(Formula& f)
{
	formula = f;
}


int WalkSat::Satisfies_Formula(vector<int> &var)
{
	int num = 0;
	bool s = true;
	for (unsigned int i = 0; i < formula.clauses.size(); ++i)
	{
		s = true;
		for (unsigned int j = 0; j < formula.clauses[i].size(); ++j)
		{
			int t = formula.clauses[i][j];
			int tt;
			if (t % 2 == 0) {

				tt = (t / 2) + 1;
				if (var[tt - 1] == 1)
				{
					s = false;
					break;
				}
			}
			else {
				tt = -((t + 1) / 2);
				if (var[-tt - 1] == 0)
				{
					s = false;
					break;
				}
			}


		}
		if (s)
			num++;

	}
	//cout << formula.literals.size() - num << endl;
	return (int)formula.clauses.size() - num;

}


void WalkSat::solve()
{

	vector<int> vars;
	vars.resize(formula.literals.size());

	for (int i = 0; i < 20000; i++)
	{
		//cout << i << " iteration" << endl;
	 int true_num = Satisfies_Formula(vars);

		if (true_num == (int)formula.clauses.size())
		{
			ans = vars;
			break;
		}
		else
		{
			int clause = Get_Random_Clause(vars);

			if ((double)(rand() % RAND_MAX / (double)RAND_MAX) < 0.5) {
				//cout << i << " iteration" << endl;
				Flip(vars, clause);
			}
			else 
				Climb(vars,clause, true_num);
		}
	}

}

int WalkSat::Get_Random_Clause(vector<int> &var)
{
	
	vector<int> notsat;
	for (unsigned int i = 0; i < formula.clauses.size(); ++i)
	{
		bool s = true;
		for (unsigned int j = 0; j < formula.clauses[i].size(); ++j)
		{
			int t = formula.clauses[i][j];
			int tt;
			if (t % 2 == 0) {

				tt = (t / 2) + 1;
				if (var[tt - 1] == 1)
				{
					s = false;
					break;
				}
			}
			else {
				tt = -((t + 1) / 2);
				if (var[-tt - 1] == 0)
				{
					s = false;
					break;
				}
			}


		}
		if (s)
			notsat.push_back(i);

	}
	return notsat[rand()%notsat.size()];
	
}

void WalkSat::Flip(vector<int> &var,int c_id)
{
	auto& t = formula.clauses[c_id];
	int tt = t[rand() % t.size()];
	if (tt % 2 == 0) {
		int ttt = (tt / 2) + 1;
		var[ttt - 1] = (var[ttt - 1] + 1) % 2;

	}
	else {
	
		int ttt = -((tt + 1) / 2);
		var[-ttt - 1] = (var[-ttt - 1] + 1) % 2;
	}

}
void WalkSat::Climb(vector<int> &var,int c_id, int n)
{
	auto& t = formula.clauses[c_id];
	int f = -1;
	for (int tt : t)
	{
		//int tt = i%2? -((i + 1) / 2) : (i / 2) + 1;
		if (tt % 2 == 0) {
			int ttt = (tt / 2) + 1;
			var[ttt - 1] = (var[ttt - 1] + 1) % 2;

		}
		else {
			int ttt = -((tt + 1) / 2);
			var[-ttt - 1] = (var[-ttt - 1] + 1) % 2;
		}
		int m = Satisfies_Formula(var);
		if (tt % 2 == 0) {
			int ttt = (tt / 2) + 1;
			var[ttt - 1] = (var[ttt - 1] + 1) % 2;

		}
		else {
			int ttt = -((tt + 1) / 2);
			var[-ttt - 1] = (var[-ttt - 1] + 1) % 2;
		}
		if (m > n)
		{
			n = m;
			f = tt;
		}

		
	}
	if (f != -1)
	{
		if (f % 2 == 0) {
			int ttt = (f / 2) + 1;
			var[ttt - 1] = (var[ttt - 1] + 1) % 2;

		}
		else {
			int ttt = -((f + 1) / 2);
			var[-ttt - 1] = (var[-ttt - 1] + 1) % 2;
		}
	}


}

void WalkSat::result(bool flag)
{
	if (ans.size() != 0) {
		cout << "SATISFIABLE" << endl;
		if (flag)
		{
			for (unsigned int i = 0; i < ans.size(); ++i)
			{
				if (ans[i] > 0)
				{
					cout << "x" << i + 1 << " = true" << "  ";
				}
				else
				{
					cout << "x" << i + 1 << " = false" << "  ";
				}
			}
			cout << endl;
		}
	}
	else {
		cout << "UNSATISFIABLE" << endl;
	}
}

WalkSat::~WalkSat()
{
}
