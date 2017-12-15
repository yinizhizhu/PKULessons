#pragma once

#ifndef FEATURE_H

#define FEATURE_H

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <fstream>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, int> STR_INT;
typedef STR_INT::iterator SIter;

class coder {
private:
	int size;
	STR_INT container;
public:
	coder();
	~coder();
	void	insert(vector<string>& str);
	double	getIndex(vector<string>& str);
	double	getIndex2(vector<string>& str);
	void	show(string outF);
};

#endif