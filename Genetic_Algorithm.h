#pragma once

#include "Formul.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <random>
#include <ctime>

//std::default_random_engine engine((unsigned int)time(nullptr));
//std::uniform_int_distribution<> dis(1, 10000);

struct Element
{
	vector<int> var;
	int num_var;
	Element(int v)
	{
		num_var = v;
		var.resize(v);
		for (auto & e : var)
		{
			e = rand() % 2;
		}

	}
	Element(const Element &E)
	{
		num_var = E.num_var;
		var.resize(E.num_var);
		for (int i = 0; i < E.num_var; ++i)
			var[i] = E.var[i];

	}


};
class Genetic_Algorithm
{
private:
	Formula formula;
	vector<int>  ans;

public:
	Genetic_Algorithm(Formula &f);
	//Genetic_Algorithms();
	void solve();
	int fitness(Element *E);

	void result(bool flag);
	~Genetic_Algorithm();
};

