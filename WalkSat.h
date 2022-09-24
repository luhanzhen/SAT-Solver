#pragma once

#include "Formul.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;




class WalkSat
{
private:
	Formula formula;
	vector<int> ans;
	int Satisfies_Formula(vector<int> &var);
	void Flip(vector<int> &var, int c_id);

	int Get_Random_Clause(vector<int> &var);
	void Climb(vector<int> &var, int c_id, int n);
public:
	WalkSat(Formula& f);
	~WalkSat();
	void solve();
	void result(bool flag);
};

