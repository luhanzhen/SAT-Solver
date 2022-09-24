#include "Formul.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>

void Formula::Read_File(string name)
{
	char c;   
	string s;
	ifstream in(name);
	while (true) {
		in >> c;
		if (c == 'c') 
		{
			getline(in, s); 
		}
		else           
		{
			in >> s; 
			break;
		}
	}
	int literal_count, clause_count;
	in >> literal_count;
	in >> clause_count;


	literals.clear();
	literals.resize(literal_count, -1);
	clauses.clear();
	clauses.resize(clause_count);
	frequency.clear();
	frequency.resize(literal_count, 0);
	polarity.clear();
	polarity.resize(literal_count, 0);

	int literal; 
	
	for (int i = 0; i < clause_count; i++) {
		while (true) 
		{
			in >> literal;
			if (literal > 0) 
			{
				clauses[i].push_back(2 *
					(literal - 1)); 
				frequency[literal - 1]++;
				polarity[literal - 1]++;
			}
			else if (literal < 0) 
			{
				clauses[i].push_back(2 * ((-1) * literal - 1) +1); 
				frequency[-1 - literal]++;
				polarity[-1 - literal]--;
			}
			else {
				break; 
			}
		}
	}
	in.close();


}

void Formula::show()
{
	std::cout << "literals:"<< std::endl;
	for (auto &a : literals)
	{
		std::cout << a << "  ";
		
	}
	std::cout << std::endl << "clauses:" << std::endl;;
	for (auto &a : clauses)
	{
		for (auto &b : a)
			std::cout << b << "  ";
		std::cout << std::endl;
	}
}

