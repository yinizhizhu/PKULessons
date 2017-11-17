#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <unordered_map>
#include "word.h"

using namespace std;

typedef struct node {
	string			attr, word;
	node			*parent;
	vector<node*>	childs;
	node(string& a, string& str) {
		parent = NULL;
		attr = a;
		word = str;
	}
}NODE, *PNODE;

typedef unordered_map<string, string> PRED;
typedef PRED::iterator ITER;

class tree {
private:
	PNODE	root;
	PRED	predicates;
public:
	tree();
	~tree();
	PNODE	insert(PNODE r, string&a, string word);
	bool	isLeaf(PNODE r);
	void	showTree(PNODE r, int deep);
	void	showTree(ofstream& out, PNODE r, int deep);
	void	showH(int deep);
	void	showH(ofstream& out, int deep);
	void	delNode(PNODE r);
	void	freeNode(PNODE r);
	void	outputPred();
	void	addPred(word& w);
	void	addDatabase(char *filename);
	void	getPred();
	void	demo();
};


#endif // !TREE_H
