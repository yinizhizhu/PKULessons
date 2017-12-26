#pragma once

#ifndef TREE_H
#define TREE_H

#include "readText.h"

typedef unordered_map<string, int> item_int;
typedef item_int::iterator ITER;

struct ITEM {
	int		counter;
	string	item;
	ITEM() : counter(0), item("") {}
	ITEM(int c, string& i) : counter(c), item(i) {}
	ITEM(ITEM& i) : counter(i.counter), item(i.item) {}
};

typedef vector<string> PAIR;

typedef struct node {
	ITEM			item;
	vector<node*>	childs;
	node			*pre, *next;
	vector<PAIR>	con_title_year;
	node() : pre(NULL), next(NULL) {}
	node(string& i, int c) {
		item.counter = c;
		item.item = i;
		pre = NULL;
		next = NULL;
	}
	node(ITEM& i) : item(i), pre(NULL), next(NULL) {}
} NODE, *PNODE;

typedef struct content {
	string author;
	vector<string> year;
	content(string& au, vector<string>& y) {
		author = au;
		int i = y.size() - 1;
		for (; i >= 0; i--)
			year.push_back(y[i]);
	}
} CONTENT;

typedef unordered_map<string, vector<CONTENT>> TASK;
typedef TASK::iterator TASK_ITER;

typedef unordered_map<string, vector<PNODE>> T_Y;
typedef T_Y::iterator T_Y_ITER;

class FPTree {
private:
	/*
		root - the root fo FPTree
		target - help to get the link list
		header - header list
		dict - dictionary for counting
		threshold - for frequent items
		frequent - store the frequent items
	*/
	PNODE			root, target;
	vector<PNODE>	header;
	item_int		dict;
	int				threshold;
	vector<vector<ITEM>>	frequent;

	TASK	task;
public:
	FPTree();
	~FPTree();
	void	task1();
	void	task2();
	void	addStr(string& a);
	void	addHeader();
	void	showFre(vector<ITEM>& fre);
	void	showHeader();
	void	addLink();
	void	addHeaderLink(PNODE r);
	void	showLink(PNODE r);
	bool	isLeaf(PNODE r);
	void	travel(PNODE r);
	void	firstS();
	string	getCItem(PNODE r, int i);
	int		getCCounter(PNODE r, int i);
	void	insert(vector<ITEM>& items, string& con, string& title, string& year);
	void	miningFre();
	void	outT_Y(string& item, vector<PNODE>& part, ofstream& out, ofstream& out2);
	void	deepT_Y(PNODE r, vector<PAIR>& t_y);
	void	miningSubFre(T_Y& container, PNODE step);
	void	miningStep(vector<string>& str, vector<PNODE>& part, T_Y& container);
	void	showFreStr(vector<string>& str);
	void	combinatePath(vector<int>& visit, vector<PNODE>& backup, T_Y& container, int h, int n);
	void	delNode(PNODE r);
};

#endif