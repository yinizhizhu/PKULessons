#include "tree.h"

bool cmpItem(ITEM& a, ITEM& b) {
	if (a.counter == b.counter)
		return a.item < b.item;
	return a.counter > b.counter;
}

bool cmpNode(PNODE a, PNODE b) {
	if (a->item.counter == b->item.counter)
		return a->item.item < b->item.item;
	return a->item.counter > b->item.counter;
}

FPTree::FPTree() {
	root = new NODE();
	threshold = 3;

	addData();
	addHeader();
	addLink();
}

FPTree::~FPTree() {
	//cout << "In free..." << endl;
	delNode(root);
	//cout << "Out free..." << endl;
}

void FPTree::addData() {
	ifstream in("trans.txt");
	int i, j, len, n;
	string a;
	vector<string> line;
	vector<vector<string>>	container;
	while (in >> len) {
		for (i = 0; i < len; i++) {
			in >> a;
			addStr(a);
			line.push_back(a);
		}
		container.push_back(line);
		line.clear();
	}

	vector<ITEM> fre;
	n = container.size();
	for (i = 0; i < n; i++) {
		len = container[i].size();
		for (j = 0; j < len; j++) {
			a = container[i][j];
			if (dict[a] >= threshold)
				fre.push_back(ITEM(dict[a], a));
		}

		sort(fre.begin(), fre.end(), cmpItem);
		frequent.push_back(fre);
		showFre(fre); //show the current transaction's frequent items

		insert(fre);

		fre.clear();
	}
	firstS(); //show the FPTree
	in.close();
}

void FPTree::addStr(string& a) {
	ITER iter = dict.find(a);
	if (iter == dict.end())
		dict[a] = 1;
	else
		iter->second++;
}

void FPTree::addHeader() {
	ITER step = dict.begin();
	for (; step != dict.end(); step++) {
		if (step->second >= threshold) {
			PNODE tmp = new NODE(string(step->first), step->second);
			header.push_back(tmp);
		}
	}
	showHeader(); //show thee header
	sort(header.begin(), header.end(), cmpNode);
	showHeader(); //show the header
}

void FPTree::showFre(vector<ITEM>& fre) {
	int i = 0, len = fre.size() - 1;
	for (; i < len; i++)
		cout << fre[i].item << ": " << fre[i].counter << ", ";
	cout << fre[i].item << ": " << fre[i].counter << endl;
}

void FPTree::showHeader() {
	int i, len = header.size()-1;
	for (i = 0; i < len; i++)
		cout << header[i]->item.item << ": " << header[i]->item.counter << ", ";
	cout << header[i]->item.item << ": " << header[i]->item.counter << endl;
}

void FPTree::delNode(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			delNode(r->childs[i]);
		//cout << r->item.item << ": " << r->item.counter << endl;
		r->childs.clear();
		delete r;
		r = NULL;
	}
}

void FPTree::addLink() {
	int i, len = header.size();
	for (i = 0; i < len; i++) {
		//cout << "In addLink: "; //show add process
		target = header[i];
		addHeaderLink(root);
		//cout << ". Out addLink!" << endl; //show the process
		showLink(header[i]); //show current node link
	}
}

void FPTree::addHeaderLink(PNODE r) {
	if (r) {
		if (r->item.item == target->item.item) {
			//cout << target->item.item << "-" << target->item.counter << "->"; //show r
			target->next = r;
			target = r;
			//cout << target->item.item << "-" << target->item.counter << " "; //show next r
		}
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			addHeaderLink(r->childs[i]);
	}
}

void FPTree::showLink(PNODE r) {
	while (r->next) {
		cout << r->item.item << ": " << r->item.counter << ", ";
		r = r->next;
	}
	cout << r->item.item << ": " << r->item.counter << endl;
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

void FPTree::insert(vector<ITEM>& items) {
	string tmp;
	PNODE step = root;
	int i, j, len = items.size();
	for (i = 0; i < len; i++) {
		tmp = items[i].item;
		for (j = step->childs.size() - 1; j >= 0; j--) {
			if (getCItem(step, j) == tmp) {
				step = step->childs[j];
				step->item.counter++;
				break;
			}
		}
		if (j < 0) {
			PNODE newone = new NODE(tmp, 1);
			step->childs.push_back(newone);
			newone->pre = step;
			step = newone;
		}
	}
	//cout << step->item.item << ": " << step->item.counter << endl;
}

void FPTree::firstS() {
	travel(root);
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