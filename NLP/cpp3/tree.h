#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include <ctype.h>
#include <iomanip>
#include "data.h"
#include "feature.h"

#define	FN 100

using namespace std;

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

typedef pair<string, int> Path;
typedef pair<string, string> HWPair;

typedef unordered_map<int, string> INT_STR;
typedef INT_STR::iterator IIter;

class tree {
private:
	PNODE	root;
	//PRED	predicates; //store all the arguments
	bool	lsb; // false for active, true for passive

	vector<string>	bnf;
	vector<string>	dir;
	vector<string>	dis;
	vector<string>	ext;
	vector<string>	frq;
	vector<string>	loc;
	vector<string>	mnr;
	vector<string>	prp;
	vector<string>	tmp;

	vector<string>	headWords;

	int		relMid; //store the index of rel in the leaves
	vector<PNODE> leaves; // store the leaf nodes which is useful for us to label sentence
	vector<string> verbs; // store the verbs which are predicates

	vector<PNODE> vPath;
	vector<PNODE> candidates;	//store the candicates
	//vector<vector<PNODE>> allPath; // store the path corresponding to the candidate node

	int		arg_c;
	STR_INT	str_int;	//for the arguments
	INT_STR	int_str;	//remap

	string	freak1, freak2;
	coder	coderWord;
	coder	coderType;
	coder	coderPos;
public:
	tree();
	~tree();
	PNODE	insert(PNODE r, string&a, string word);
	bool	isLeaf(PNODE r);

	void	showTree(PNODE r, int deep);
	void	showTree(ofstream& out, PNODE r, int deep);

	int		getI(PNODE r);
	Pair	getHT(PNODE r);
	void	showSentence(ofstream& out, PNODE r);
	void	labelSentence(ofstream& out, PNODE r);
	void	label(ofstream& out, PNODE r);

	void	showH(int deep);
	void	showH(ofstream& out, int deep);

	void	delNode(PNODE r);
	void	freeNode(PNODE r);

	void	outputFeatureW(vector<string>& con, char *filename);
	void	featureW(vector<string>& con, char *filename, char *outName);
	void	addFeatureW(void);
	bool	inFeatureW(vector<string>& con, string str);

	bool	noVV(PNODE r);
	string	getLeafW(PNODE r);
	string	getLeafA(PNODE r);
	void	getVerbs(void);
	PNODE	getVNode(PNODE r, string& verb, vector<string>& verbf);

	void	secondTry(string labelFile, string outFile);
	void	pruing(vector<PNODE>& leaves);

	bool	check(char c);
	void	divideWord(vector<string>& word, string& words);
	void	getCoder();
	void	getTrainData();

	HWPair	getHeadWord(PNODE r, vector<string>& headWords, vector<string>& firstw, vector<string>& lastw);
	void	getRelMid(PNODE step);
	int		getPosition(PNODE a, PNODE v);
	PNODE	getComP(PNODE a, PNODE b);
	void	getNode(PNODE& a, PNODE& b, Data& d, Pair& p);
	void	showPath(vector<PNODE>& path);

	void	reachRoot(PNODE r, vector<PNODE>& path);
	void	getPath(vector<PNODE>& path, vector<string>& ppath, vector<string>& rpath);
	void	getCandidates(PNODE r);

};


#endif // !TREE_H
