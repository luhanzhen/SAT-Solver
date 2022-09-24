
#include "DPLL.h"

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;


int SATDPLL::propagate(Formula &f) {
	
	if (f.clauses.size() == 0) 
	{
		return satisfied; 
	}
	bool unit_clause_flag = false;
	do {
		unit_clause_flag = false;
	
		for (unsigned int i = 0; i < f.clauses.size(); i++) {
			if (f.clauses[i].size() ==
				1) 
			{
				unit_clause_flag = true;
				f.literals[f.clauses[i][0] / 2] = f.clauses[i][0] % 2; 
				f.frequency[f.clauses[i][0] / 2] = -1; 
				int result = transform(f, f.clauses[i][0] / 2); 
				if (result == satisfied || result == unsatisfied) {
					return result;
				}
				break; 
			}
			else if (f.clauses[i].size() == 0) 
			{
				return unsatisfied; 
			}
		}
	} while (unit_clause_flag);

	return normally; 
}


int SATDPLL::transform(Formula &f, int literal) {
	int value = f.literals[literal]; 
	for (unsigned int i = 0; i < f.clauses.size(); i++) {
		for (unsigned int j = 0; j < f.clauses[i].size(); j++) {
			if ((2 * literal + value) == f.clauses[i][j]) {
				f.clauses.erase(f.clauses.begin() + i--);           
				if (f.clauses.size() == 0) 
				{
					return satisfied;
				}
				break; 
			}
			else if (f.clauses[i][j] / 2 == literal) 
			{
				f.clauses[i].erase(f.clauses[i].begin() + j--);
				if (f.clauses[i].size() == 0) 
				{
					return unsatisfied;
				}
				break; 
			}
		}
	}
	
	return normally;
}


int SATDPLL::dpll(Formula f) {
	int result = propagate(f); 
	if (result == satisfied) 
	{
		generate_result(f, result);
		return completed;
	}
	else if (result == unsatisfied) 
	{
		return normally;
	}
	
	int dis = (int)distance(f.frequency.begin(),max_element(f.frequency.begin(), f.frequency.end()));
	
	for (int j = 0; j < 2; j++) {
		Formula new_f = f; 
		if (new_f.polarity[dis] >
			0) 
		{
			new_f.literals[dis] = j; 
		}
		else                
		{
			new_f.literals[dis] = (j + 1) % 2; 
		}
		new_f.frequency[dis] = -1;
		int transform_result = transform(new_f, dis);
		if (transform_result == satisfied)
		{
			generate_result(new_f, transform_result);
			return completed;
		}
		else if (transform_result == unsatisfied) 		
		{
			continue;
		}
		int dpll_result = dpll(new_f); 
		if (dpll_result == completed) // propagate
		{
			return dpll_result;
		}
	}
	return normally;
}


void SATDPLL::generate_result(Formula &f, int result) {			//genetate result
	if (result == satisfied) 
	{
		for (unsigned int i = 0; i < f.literals.size(); i++) {
			if (f.literals[i] != -1) {
				
				ans.push_back((int)pow(-1, f.literals[i]) * (i + 1));
			}
			else 
			{
	
				ans.push_back(i + 1);
			}
		}
		

	}
	
}


void SATDPLL::solve() {			 // main entrance
	int result = dpll(formula); 
	if (result == normally) {
		generate_result(formula, unsatisfied); 
	}
}

void SATDPLL::result(bool flag) //显示结果  flag-true 打印结果 false不打印
{
	if (ans.size() != 0) {
		cout << "SATISFIABLE" << endl;
		if (flag)
		{
			for (unsigned int i = 0;i < ans.size();++i)
			{
				if (ans[i] > 0)
				{
					cout << "x" << ans[i] << " = true" << "  ";
				}
				else
				{
					cout << "x" << -ans[i] << " = false" << "  ";
				}
			}
			cout << endl;
		}
	}
	else {
		cout << "UNSATISFIABLE" << endl;
	}

}
