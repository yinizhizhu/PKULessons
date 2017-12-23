#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include <vector>
#include <fstream>

using namespace std;

typedef unordered_map<string, int> item_int;
typedef item_int::iterator ITER;

struct ITEM {
	int		counter;
	string	item;
	ITEM() : counter(0), item("") {}
	ITEM(int c, string& i) : counter(c), item(i) {}
	ITEM(ITEM& i) : counter(i.counter), item(i.item) {}
};

typedef struct node {
	ITEM			item;
	vector<node*>	childs;
	node			*pre, *next;
	node() : pre(NULL), next(NULL) {}
	node(string& i, int c) {
		item.counter = c;
		item.item = i;
		pre = NULL;
		next = NULL;
	}
	node(ITEM& i) : item(i), pre(NULL), next(NULL) {}
} NODE, *PNODE;

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
public:
	FPTree();
	~FPTree();
	void	addData();
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
	void	insert(vector<ITEM>& items);
	void	miningFre();
	void	miningSubFre(vector<string>& str, PNODE step);
	void	showFreStr(vector<string>& str);
	void	combinate(vector<int>& visit, vector<string>& str, vector<string>& container, int h, int n);
	void	delNode(PNODE r);
};

#endif