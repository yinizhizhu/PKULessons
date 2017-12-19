#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

using namespace std;

typedef unordered_map<string, int> item_int;
typedef item_int::iterator ITER;

struct ITEM {
	int		counter;
	string	item;
	ITEM() : counter(0), item("") {}
	ITEM(ITEM& i) : counter(i.counter), item(i.item) {}
};

bool cmp(ITEM& a, ITEM& b) {
	return a.counter > b.counter;
}

typedef struct node {
	ITEM			item;
	vector<node*>	childs;
	node() {}
	node(string& i) {
		item.counter = 1;
		item.item = i;
	}
	node(ITEM& i) : item(i) {}
} NODE, *PNODE;

bool cmp(PNODE a, PNODE b) {
	return a->item.counter > b->item.counter;
}

class FPTree {
private:
	PNODE			root;
	vector<PNODE>	header;
	item_int		dict;
public:
	FPTree();
	~FPTree();
	bool	isLeaf(PNODE r);
	void	travel(PNODE r);
	string	getCItem(PNODE r, int i);
	int		getCCounter(PNODE r, int i);
	void	insert(vector<string>& items);
	void	permutateComtinate(vector<string>& conSubTree, vector<vector<string>>& container);
	void	delNode(PNODE r);
};

#endif