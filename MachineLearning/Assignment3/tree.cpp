#include "tree.h"

FPTree::FPTree() {
	root = new NODE();
}

FPTree::~FPTree() {
	delNode(root);
}

void FPTree::delNode(PNODE r) {
	if (r) {
		int i = r->childs.size()-1;
		for (; i >= 0; i--)
			delNode(r->childs[i]);
		delete[]r;
	}
}

bool FPTree::isLeaf(PNODE r) {
	if (r) {
		cout << "The PNODE is NULL!!!" << endl;
		return false;
	}
	if (r->childs.size()) return true;
	return false;
}

string FPTree::getCItem(PNODE r, int i) {
	return r->childs[i]->item.item;
}

int FPTree::getCCounter(PNODE r, int i) {
	return r->childs[i]->item.counter;
}

void FPTree::insert(vector<string>& items) {
	string tmp;
	PNODE step = root;
	int i, j, len = items.size();
	for (i = 0; i < len; i++) {
		tmp = items[i];
		ITER iter = dict.find(tmp);
		if (iter == dict.end())
			dict[tmp] = 1;
		else
			iter->second++;

		for (j = step->childs.size() - 1; j >= 0; j--) {
			if (getCItem(step, i) == tmp) {
				step = step->childs[i];
				step->item.counter++;
				break;
			}
		}

		if (j < 0) {
			PNODE newone = new NODE(tmp);
			step->childs.push_back(newone);
			step = newone;
		}
	}
}

void FPTree::travel(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		cout << r->item.item << ": " << r->item.counter << endl;
		for (; i < len; i++)
			travel(r->childs[i]);
	}
}

void FPTree::permutateComtinate(vector<string>& conSubTree, vector<vector<string>>& container) {

}