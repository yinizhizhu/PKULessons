#pragma once

#ifndef READTEXT_H
#define READTEXT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <vector>
#include <fstream>

using namespace std;

class reader {
private:
	ifstream	in;
public:
	string		year;
	string		title;
	string		conference;
	vector<string>	authors;

	reader();
	~reader();
	bool readTrans();
	void divide(string& line, string& left, string& right);
};

#endif