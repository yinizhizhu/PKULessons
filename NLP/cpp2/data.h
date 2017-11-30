#pragma once

#ifndef DATA_H

#define DATA_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "word.h"

using namespace std;

typedef pair<int, int> Pair;

class Data {
public:
	int step;
	string verb;
	vector<string> words;
	vector<string> attrs;
	vector<string> tags;
	vector<pair<int, int>> index;

	Data();
	~Data();
	bool	getNextLine(ifstream& i);
	Pair	getNext();
	void	push(word& w);
	void	clear();
	void	show();
	void	demo();

	string	v();
	string	w(int i);
	string	a(int i);
	string	t(int i);
};

#endif