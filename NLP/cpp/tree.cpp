#include "tree.h"

//#define SHOW_DIVIDE
#define OUT

tree::tree() {
	root = NULL;
}

tree::~tree() {
	if (root)
		freeNode(root);
}

PNODE tree::insert(PNODE r, string& a, string word = "") {
	PNODE newone = new NODE(a, word);
	if (r) {
		r->childs.push_back(newone);
		newone->parent = r;
	}
	else
		root = newone;
	return newone;
}

void tree::showTree(PNODE r, int deep = 0) {
	if (r) {
		int i, len = r->childs.size();
		cout << endl;
		showH(deep);
		cout << "(" << r->attr;
		if (r->word.size())
			cout << " " << r->word;
		for (i = 0; i < len; i++)
			showTree(r->childs[i], deep + 2);
		cout << ")";
	}
}

void tree::showTree(ofstream& out, PNODE r, int deep = 0) {
	if (r) {
		int i, len = r->childs.size();
		out << endl;
		showH(out, deep);
		out << "(" << r->attr;
		if (r->word.size())
			out << " " << r->word;
		for (i = 0; i < len; i++)
			showTree(out, r->childs[i], deep + 2);
		out << ")";
	}
}

void tree::demo() {
	ifstream in("data\\result.txt");
	ofstream out("tree.txt");

	int i, len, process = 0;
	string part, attr, word;
	PNODE step = NULL;
	for (; !in.eof();) {
		in >> part;

		len = part.size();
		if (len) {
#ifdef SHOW_DIVIDE
#ifdef OUT
			out
#else
			cout
#endif
			 << part << endl;
#endif // SHOW_DIVIDE
			if (part[0] == '(') {
				process++;
				attr = part.substr(1, len);
#ifdef SHOW_DIVIDE
#ifdef OUT
				out
#else
				cout
#endif
				 << attr << endl;
#endif // SHOW_DIVIDE
				step = insert(step, attr);
			}
			else {
				for (i=0; i < len; i++)
					if (part[i] == ')')
						break;
				word = part.substr(0, i);
				step->word = word;
				process -= len - i;
				for (; i<len; i++)
					step = step->parent;
#ifdef SHOW_DIVIDE
#ifdef OUT
				out
#else
				cout
#endif
				 << word << endl;
#endif // SHOW_DIVIDE
			}
			if (process == 0) {
				//Deal with the data which is shaped into tree
				//
#ifdef OUT
				showTree(out, root, 0);
				out << endl;
#else
				showTree(root, 0);
				cout << endl;
#endif
				freeNode(root);
				root = NULL;
				step = NULL;
			}
		}
		part = "";
	}

	out.close();
	in.close();
}

void tree::showH(int deep) {
	for (; deep; deep--) cout << ' ';
}

void tree::showH(ofstream& out, int deep) {
	for (; deep; deep--) out << ' ';
}

void tree::delNode(PNODE r) {
	if (r) {
		PNODE parent = r->parent;
		int i, len = parent->childs.size();
		for (i = 0; i < len; i++)
			if (parent->childs[i] == r)
				break;
		parent->childs.erase(parent->childs.begin() + i);
		freeNode(r);
	}
}

void tree::freeNode(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			freeNode(r->childs[i]);
		delete r;
		r = NULL;
	}
}
