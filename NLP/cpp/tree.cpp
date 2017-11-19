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

PNODE tree::insert(PNODE r, string& attr, string word = "") {
	PNODE newone = new NODE(attr, word);
	if (r) {
		r->childs.push_back(newone);
		newone->parent = r;
	}
	else
		root = newone;
	return newone;
}

bool tree::isLeaf(PNODE r) {
	if (r->word.size()) return true;
	return false;
}

void tree::showTree(PNODE r, int deep = 0) {
	if (r) {
		int i, len = r->childs.size();
		cout << endl;
		showH(deep);
		cout << "(" << r->attr;
		if (isLeaf(r))
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
		if (isLeaf(r))
			out << " " << r->word;
		for (i = 0; i < len; i++)
			showTree(out, r->childs[i], deep + 2);
		out << ")";
	}
}

void tree::showSentence(ofstream& out, PNODE r) {
	if (r) {
		if (isLeaf(r))
			out << r->word << "/" << r->attr << "/" << r->tag << " ";
		else {
			int i, n = r->childs.size();
			for (i = 0; i < n; i++)
				showSentence(out, r->childs[i]);
		}
	}
}

void tree::outputPred() {
	cout << "Finally, the number of predicates: " << predicates.size() << endl;
	ofstream out("predicates.txt");
	ITER step = predicates.begin();
	for (; step != predicates.end(); step++)
		out << step->first << " " << step->second << endl;
	out.close();
}

void tree::addPred(word& w) {
	string word, attr, tag;
	word = w.getWord();
	attr = w.getAttr();
	tag = w.getTag();
	ITER iter = predicates.find(word);
	if (iter == predicates.end())
		predicates[word] = tag;
	else {
		if (iter->second.find(tag) == -1)
			iter->second += ' ' + tag;
	}
}

//add words which are labeled and used to get the predicates
void tree::addDatabase(char *filename) {
	cout << "Get the predicates in file " << filename << "...\n";
	ifstream in(filename);

	/*
	pre - store the head index of the 'word' which looks just like 'word/attr/tag'
	cur - store the tail index of the 'word' which is same with pre

	line - get a line of text file
	w - store the 'word' which is same with pre

	tmp - a class which is used to split the 'word' into word, attr and tag,
	and supply a api to get the each content of the 'word'
	(You can get the details in those two files: 'word.cpp' and 'word.h')
	*/
	char noTag[10] = "O";
	int pre, cur, len;
	string line, w;
	word tmp;
	for (; getline(in, line);) {
		len = line.size();
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				w = line.substr(pre, cur - pre);
				tmp.setWordTrain(w);

				if (strcmp(noTag, tmp.getTag()))
					addPred(tmp);

				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur - pre);
			tmp.setWordTrain(w);

			if (strcmp(noTag, tmp.getTag()))
				addPred(tmp);
		}
	}
	in.close();
	cout << "Now, the number of predicates: " << predicates.size() << endl;
}

void tree::getPred() {
	//add words in training data
	char train[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\data\\cpbtrain.txt";
	addDatabase(train);

	//add words in developing data
	char dev[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\data\\cpbdev.txt";
	addDatabase(dev);
}

void tree::demo() {
	//getPred();
	//outputPred();

	ifstream in("C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\data\\demo.txt");
	ofstream out("demoTree.txt");
	ofstream out2("demoSentence.txt");

	int i, len, process = 0;
	vector<PNODE> leaves;
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
				leaves.push_back(step);
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
				cout << "Output the original tree" << endl;
				showTree(out, root, 0);
				out << endl;

				showSentence(out2, root);
				out2 << endl;
#else
				showTree(root, 0);
				cout << endl;
#endif
				/*
				Start Senmantic Roles Labeling (SRL)
				*/
				pruing();
				label();

				cout << "Free the tree" << endl;
				freeNode(root);
				root = NULL;
				step = NULL;
				leaves.clear();
			}
		}
		part = "";
	}
	out2.close();
	out.close();
	in.close();
}



void tree::pruing() {
	/*
	Pruing hexuritic
	*/
}

void tree::label() {
	/*
	ARG0, ARG1 (Exchange position of ARG0 and ARG1 while the SB\LB appears)
	REL
	ARGM - LOC, TMP, ADV, CND, PRP, BNF, MNR, DIR, DIS, FRQ, EXT, TPC(ADV)
	*/
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
		for (; parent->childs.size() == 0;)
			delNode(parent);
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
