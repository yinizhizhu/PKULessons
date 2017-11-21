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

#define	FN 100

using namespace std;

typedef pair<int, int> headT;

typedef struct node {
	string			attr, word, tag;
	node			*parent;
	vector<node*>	childs;
	node(string& a, string& str) {
		parent = NULL;
		attr = a;
		word = str;
		tag = "";
	}
}NODE, *PNODE;

typedef unordered_map<string, string> PRED;
typedef PRED::iterator ITER;

class tree {
private:
	PNODE	root;
	PRED	predicates;
	bool	lsb;

	vector<string>	bnf;
	vector<string>	dir;
	vector<string>	dis;
	vector<string>	ext;
	vector<string>	frq;
	vector<string>	loc;
	vector<string>	mnr;
	vector<string>	prp;
	vector<string>	tmp;

	vector<string>	preLex;

	vector<PNODE> leaves;
public:
	tree();
	~tree();
	PNODE	insert(PNODE r, string&a, string word);
	bool	isLeaf(PNODE r);

	void	showTree(PNODE r, int deep);
	void	showTree(ofstream& out, PNODE r, int deep);

	int		getI(PNODE r);
	headT	getHT(PNODE r);
	void	showSentence(ofstream& out, PNODE r);
	void	labelSentence(ofstream& out, PNODE r);
	void	label(ofstream& out, PNODE r);

	void	showH(int deep);
	void	showH(ofstream& out, int deep);

	void	delNode(PNODE r);
	void	freeNode(PNODE r);

	void	outputPred();
	void	addPred(word& w);
	void	addDatabase(char *filename);
	void	getPred();	//get the predicates labeled with 'arg' tag

	void	outputFeatureW(vector<string>& con, char *filename);
	void	featureW(vector<string>& con, char *filename, char *outName);
	void	addFeatureW();
	bool	inFeatureW(vector<string>& con, string& str);

	void	demo();

	void	pruing(vector<PNODE>& leaves);
	void	label();
	bool	noVV(PNODE r);
	string	getLeafW(PNODE r);
	string	getLeafA(PNODE r);
	PNODE	getVV();
};


#endif // !TREE_H
