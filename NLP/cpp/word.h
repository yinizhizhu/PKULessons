#pragma once
#ifndef WORD_H

#define WORD_H

#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class word {
private:
	char *store;//store the word
	char *attr;	//part of speech
	char *tag;	//tag for Arg
public:
	word();
	~word();
	void setWordTrain(string& str);
	void setWordTest(string& str);
	char *getWord();
	char *getAttr();
	char *getTag();
	void demo();
};

#endif // !WORD_H
