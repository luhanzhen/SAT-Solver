#include "Genetic_Algorithm.h"
#include "Formul.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cmath>




Genetic_Algorithm::Genetic_Algorithm(Formula & f)
{
	formula = f;
	srand((unsigned int)time(0));
	
}

//Genetic_Algorithms::Genetic_Algorithms()
//{
//
//}

void Genetic_Algorithm::solve()
{
	
	
	int popsize = 20000;
	int gennum = 20;
	vector<Element*> population;
	population.resize(popsize);
	for (auto &e : population)
		e = new Element((int)formula.literals.size());
	for (int i = 0; i < gennum; ++i)
	{
	//	cout << "i = " << i << endl;
		vector<Element*> mate;
		mate.resize(popsize);
		for (int j = 0; j < popsize; ++j)
		{
			Element *i1 = population[rand() % popsize];
			Element *i2 = population[rand() % popsize];
			
			
			if (fitness(i1) > fitness(i2))
				mate[j] = new Element(*i1);
			else
				mate[j] = new Element(*i2);
		}
		vector<Element*> offspring;
		offspring.resize(popsize);
		for (int j = 0; j < popsize; j = j + 2)
		{
			Element *parrent1 = mate[rand() % popsize];
			Element *parrent2 = mate[rand() % popsize];
			Element offspring1(*parrent1);
			Element offspring2(*parrent2);
			
			if ((double)(rand() % RAND_MAX / (double)RAND_MAX) < 0.7)
			{
				unsigned int p1 = (rand() % (formula.literals.size()-1)) + 1;
				unsigned int p2 = (rand() % (formula.literals.size()-1)) + 1;
				
				if (p1 == p2)
				{
					p2++;
					if (p2 == formula.literals.size())
						p2 = 1;
				}
				if (p1 > p2)
				{
					unsigned int t = p1;
					p1 = p2;
					p2 = t;
				}
				for (unsigned int k = p1; k < p2; k++)
				{
					offspring1.var[k] = parrent1->var[k];
					offspring2.var[k] = parrent2->var[k];
				}
			}
			offspring[j] = new Element(offspring1);
			offspring[j+1] = new Element(offspring2);
		}
		for (int j = 0; j < popsize; ++j)
		{
			for (unsigned int k = 0; k < formula.literals.size(); ++k)
			{
				if ((double)(rand() % RAND_MAX / (double)RAND_MAX) < (1.0 / (double)formula.literals.size())) {
					int t = offspring[j]->var[k];
					offspring[j]->var[k] = !t;
				}

			}
		}

		int best = 0, worst = 0;
		for (int j = 0; j < popsize; j++) {
			int t = fitness(population[j]);
			if ( t > fitness(population[best])) {
				best = j;
			}
			if (t < fitness(population[worst])) {
				worst = j;
			}
		}
		Element e(*population[best]);
		
		
		for (int j = 0; j < popsize; j++) {
			delete population[j];
			if (j == worst) {
				
				population[j] = new Element(e);
			}
			else {
				population[j] = new Element(*offspring[j]);
			}
		}
		
		for (auto &e : mate)
			delete e;
		for (auto &e : offspring)
			delete e;
		for (int j = 0; j < popsize; j++) {
			if (fitness(population[j]) == (int)formula.clauses.size()) {
				ans =  population[j]->var;
				break;
			}
		}
		if (ans.size() != 0)
			break;
	}


	for (auto &e : population)
		delete e;


}


int Genetic_Algorithm::fitness(Element * E)
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
				if (E->var[tt-1] == 1)
				{
					s = false;
					break;
				}
			}
			else {
				tt = -((t + 1) / 2);
				if (E->var[-tt-1] == 0)
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
	return formula.clauses.size() - num;
}

//Genetic_Algorithms:

void Genetic_Algorithm::result(bool flag)
{
	if (ans.size() != 0) {
		cout << "SATISFIABLE" << endl;
		if (flag)
		{
			for (unsigned int i = 0; i < ans.size(); ++i)
			{
				if (ans[i] > 0)
				{
					cout << "x" << i+1 << " = true" << "  ";
				}
				else
				{
					cout << "x" << i+1 << " = false" << "  ";
				}
			}
			cout << endl;
		}
	}
	else {
		cout << "UNSATISFIABLE" << endl;
	}
}
Genetic_Algorithm::~Genetic_Algorithm()
{

}
