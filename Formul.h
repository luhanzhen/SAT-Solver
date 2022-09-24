#pragma once


#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

class Formula {
public:

	vector<int> literals;
	vector<int> frequency;

	vector<int> polarity;
	vector<vector<int>> clauses;

	Formula(string name) { Read_File(name); }
	Formula() {};
	void Read_File(string name);
	void show();

	Formula(const Formula &f) {
		literals = f.literals;
		clauses = f.clauses;
		frequency = f.frequency;
		polarity = f.polarity;
	}

};

