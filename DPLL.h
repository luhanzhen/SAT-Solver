#pragma once

#include "Formul.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

constexpr auto satisfied = 1;
constexpr auto unsatisfied = 2;
constexpr auto normally = 3;
constexpr auto completed = 4;



class SATDPLL {
private:
	Formula formula;                           
	int propagate(Formula &); 
	int dpll(Formula);           
	int transform(Formula &,	int); 
	void generate_result(Formula &, int); 
	vector<int> ans;
public:
	SATDPLL(Formula &f) 
	{ 
		formula = f; 
	};
	
	void solve();      
	void result(bool flag);


};

