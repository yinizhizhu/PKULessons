#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <stack>
#include <unordered_map>
#include "data.h"

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

//typedef unordered_map<string, string> PRED;
//typedef PRED::iterator ITER;

typedef unordered_map<string, int> STR_INT;
typedef STR_INT::iterator SIter;
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

	int		verb_c;
	STR_INT verb_int;	//for the verb

	int		head_c;
	STR_INT head_int;	//for the head word

	int		hpos_c;
	STR_INT hpos_int;	//for the pos of head word

	int		ptype_c;
	STR_INT ptype_int;	//for the prase type

	int		path_c;
	STR_INT path_int;	//for the path

	int		left_c;
	STR_INT left_int;	//for the left node of the current node at the same level

	int		right_c;
	STR_INT right_int;	//for the left node

	int		vpos_c;
	STR_INT vpos_int;	//for the POS of verb

	int		ppath_c;
	STR_INT	ppath_int;	//for the partial path between the current node and the predicate node
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

	//void	outputPred(void);
	//void	addPred(word& w);
	//void	addDatabase(char *filename);
	//void	getPred(void);	//get the predicates labeled with 'arg' tag

	void	outputFeatureW(vector<string>& con, char *filename);
	void	featureW(vector<string>& con, char *filename, char *outName);
	void	addFeatureW(void);
	bool	inFeatureW(vector<string>& con, string& str);

	void	label(int l);
	bool	noVV(PNODE r);
	string	getLeafW(PNODE r);
	string	getLeafA(PNODE r);
	void	getVerbs(void);
	PNODE	getVNode(PNODE r, string verb);
	PNODE	getVV(int l);
	void	firstTry(void); //label

	void	secondTry(string labelFile, string outFile, char* cmd);
	void	pruing(vector<PNODE>& leaves);

	void	getTrainData();

	Pair	getLeftRight(PNODE r);
	HWPair	getHeadWord(PNODE r, vector<string>& headWords);
	void	getRelMid(PNODE step);
	int		getPosition(PNODE a, PNODE v);
	PNODE	getComP(PNODE a, PNODE b);
	void	getNode(PNODE& a, PNODE& b, Data& d, Pair& p);
	void	showPath(vector<PNODE>& path);

	void	reachRoot(PNODE r, vector<PNODE>& path);
	Path	getPath(vector<PNODE>& path, string& ppath);
	void	getCandidates(PNODE r);

};


#endif // !TREE_H
