#pragma once

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

typedef struct node {
	string attr, word;
	node* parent;
	vector<node*> childs;
	node(string& a, string& str) {
		parent = NULL;
		attr = a;
		word = str;
	}
}NODE, *PNODE;

class tree {
private:
	PNODE root;
public:
	tree();
	~tree();
	PNODE insert(PNODE r, string&a, string word);
	void showTree(PNODE r, int deep);
	void showTree(ofstream& out, PNODE r, int deep);
	void showH(int deep);
	void showH(ofstream& out, int deep);
	void delNode(PNODE r);
	void freeNode(PNODE r);
	void demo();
};


#endif // !TREE_H
