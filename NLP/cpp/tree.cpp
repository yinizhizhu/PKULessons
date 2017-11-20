#include "tree.h"

//#define SHOW_DIVIDE
//#define OUT

tree::tree() {
	root = NULL;
	lsb = false;

	preLex.push_back("PP");
	preLex.push_back("IP");
	preLex.push_back("NP");
	preLex.push_back("QP");
	preLex.push_back("LCP");
	preLex.push_back("DVP");
	preLex.push_back("CP");
	preLex.push_back("ADVP");
}

tree::~tree() {
	if (root)
		freeNode(root);
}

PNODE tree::insert(PNODE r, string& attr, string word = "") {
	PNODE newone = new NODE(attr, word);
	if (!lsb && (attr == "LB" || attr == "SB")) lsb = true;
	if (r) {
		r->childs.push_back(newone);
		newone->parent = r;
	}
	else root = newone;
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
		cout << "(" << r->attr << r->tag;
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
		out << "(" << r->attr << r->tag;
		if (isLeaf(r))
			out << " " << r->word << r->tag;
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

void tree::labelSentence(ofstream& out, PNODE r) {
	if (r) {
		if (isLeaf(r))
			label(out, r);
		else {
			string tag = r->tag;
			if (tag.size()) {
				vector<PNODE> leaves, store;
				store.push_back(r);
				int i, n = store.size(), len;
				for (; n;) {
					for (; n; n--) {
						r = store[0];
						store.erase(store.begin());
						if (isLeaf(r))
							leaves.push_back(r);
						else {
							len = r->childs.size();
							for (i = 0; i < len; i++)
								store.push_back(r->childs[i]);
						}
					}
					n = store.size();
				}
				n = leaves.size();
				if (n == 1) {
					r = leaves[0];
					r->tag = "S-" + tag;
					label(out, r);
				}
				else {
					r = leaves[0];
					r->tag = "B-" + tag;
					label(out, r);
					for (i = 1; i < n - 1; i++) {
						leaves[i]->tag = "I-" + tag;
						label(out, leaves[i]);
					}
					leaves[i]->tag = "E-" + tag;
					label(out, leaves[i]);
				}
			}
			else {
				int i, n = r->childs.size();
				for (i = 0; i < n; i++)
					labelSentence(out, r->childs[i]);
			}
		}
	}
}

void tree::label(ofstream& out, PNODE r) {
	out << r->word << "/" << r->attr << "/";
	if (r->tag.size())
		out << r->tag << " ";
	else
		out << "O ";
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

void tree::outputFeatureW(vector<string>& con, char *filename) {
	ofstream out(filename);
	for (unsigned int i = 0; i < con.size(); i++)
		out << con[i] << endl;
	out.close();
}

void tree::featureW(vector<string>& con, char *filename, char *outName) {
	string str;
	ifstream in(filename);
	for (; !in.eof(); ) {
		in >> str;
		if (str.size())
			con.push_back(str);
		str = "";
	}
	in.close();
	outputFeatureW(con, outName);
}

void tree::addFeatureW() {
	char BNF[FN] = "label\\BNF.txt", outBNF[FN] = "label\\bnf_.txt";
	featureW(bnf, BNF, outBNF);

	char DIR[FN] = "label\\DIR.txt", outDIR[FN] = "label\\dir_.txt";
	featureW(dir, DIR, outDIR);

	char DIS[FN] = "label\\DIS.txt", outDIS[FN] = "label\\dis_.txt";
	featureW(dis, DIS, outDIS);

	char EXT[FN] = "label\\EXT.txt", outEXT[FN] = "label\\ext_.txt";
	featureW(ext, EXT, outEXT);

	char FRQ[FN] = "label\\FRQ.txt", outFRQ[FN] = "label\\frq_.txt";
	featureW(frq, FRQ, outFRQ);

	char LOC[FN] = "label\\LOC.txt", outLOC[FN] = "label\\loc_.txt";
	featureW(loc, LOC, outLOC);

	char MNR[FN] = "label\\MNR.txt", outMNR[FN] = "label\\mnr_.txt";
	featureW(mnr, MNR, outMNR);

	char PRP[FN] = "label\\PRP.txt", outPRP[FN] = "label\\prp_.txt";
	featureW(prp, PRP, outPRP);

	char TMP[FN] = "label\\TMP.txt", outTMP[FN] = "label\\tmp_.txt";
	featureW(tmp, TMP, outTMP);
}

bool tree::inFeatureW(vector<string>& con, string& str) {
	for (unsigned int i = 0; i < con.size(); i++)
		if (con[i].find(str) != -1) //Only if str is in any uint of str can indicate the class str should be tagged with
			return true;
	return false;
}

void tree::demo() {
	//getPred();
	//outputPred();
	addFeatureW();

	//ifstream in("C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\data\\demo.txt");
	ifstream in("tree\\testTree.txt");
	ofstream out("demoTree.txt");
	ofstream out2("demoSentence.txt");

	int i, len, process = 0, counter = 1;
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
#endif
				cout << counter << "th is moving on..." << endl;
				/*
				Start Senmantic Roles Labeling (SRL)
				*/
				//pruing(leaves);
				label();

				labelSentence(out2, root);
				out2 << endl;

#ifdef OUT
				cout << "Output the prued tree" << endl;
				showTree(out, root, 0);
				out << endl;
#endif
				cout << "Done parseing! Free the tree..." << endl;
				freeNode(root);
				counter++;
				root = NULL;
				step = NULL;
				lsb = false;
				leaves.clear();
			}
		}
		part = "";
	}
	out2.close();
	out.close();
	in.close();
}

void tree::pruing(vector<PNODE>& leaves) {
	/*
	Pruing hexuritic
	*/
	int i, len = leaves.size();
	for (i = 0; i < len; i++) {
		if (leaves[i]->attr == "PU") {
			delNode(leaves[i]);
			leaves.erase(leaves.begin() + i);
			i--;
			len--;
		}
	}
}

bool tree::noVV(PNODE r) {
	bool ans = true;
	if (r) {
		if (r->attr == "VV") return false;
		for (int i = r->childs.size() - 1; i >= 0; i--)
			if (!noVV(r->childs[i])) {
				ans = false;
				break;
			}
	}
	return ans;
}

void tree::label() {
	/*
	ARG0, ARG1 (Exchange position of ARG0 and ARG1 while the SB\LB appears)
	REL
	ARGM - LOC, TMP, ADV, CND, PRP, BNF, MNR, DIR, DIS, FRQ, EXT, TPC(ADV)
	*/
	PNODE vv = getVV();
	if (vv) {
		PNODE p = vv->parent;
		string left = "ARG0", right = "ARG1", attr;
		if (lsb) {
			left = "ARG1";
			right = "ARG0";
		}
		int h, mid = -1, t = p->childs.size();
		for (h = 0; h < t; h++) {
			PNODE c = p->childs[h];
			attr = c->tag;
			if (attr == "PP") {
				attr = c->childs[1]->attr;
				if (attr == "LCP") {
					if (inFeatureW(loc, getLeafW(c->childs[1]->childs[1])))
						c->tag = "ARGM-LOC";
					else if (inFeatureW(tmp, getLeafW(c->childs[1]->childs[1])))
						c->tag = "ARGM-TMP";
					else
						c->tag = "ARGM-ADV";
				}
				else if (attr == "IP")
					c->tag = "ARGM-TPC";
				else if (attr == "NP") {
					if (inFeatureW(bnf, getLeafW(c->childs[0]))) {
						if (noVV(c->childs[0]))
							c->tag = "ARGM-BNF";
						else
							c->tag = "ARGM-PRP";
					}
					else if (inFeatureW(prp, getLeafW(c->childs[0])))
						c->tag = "ARGM-PRP";
					else if (inFeatureW(mnr, getLeafW(c->childs[0])))
						c->tag = "ARGM-MNR";
					else if (inFeatureW(dir, getLeafW(c->childs[0])))
						c->tag = "ARGM-DIR";
					else
						c->tag = "ARGM-ADV";
				}
				else
					c->tag = "ARGM-ADV";
			}
			else if (attr == "DVP" || attr == "LCP")
				c->tag = "ARGM-LOC";
			else if (attr == "CP")
				c->tag = "ARGM-CND";
			else if (attr == "QP") {
				c->tag = "ARGM-FRQ";
				c->tag = "ARGM-EXT";
			}
		}
		for (h = 0; h < mid; h++)
			if (p->childs[h]->attr == "NP") {
				p->childs[h]->tag = left;
				break;
			}
		for (++mid; mid<t; mid++)
			if (p->childs[mid]->attr == "NP") {
				p->childs[mid]->tag = right;
				break;
			}
	}
	else
		cout << "***Something is wrong!***" << endl;
}

string tree::getLeafW(PNODE r) {
	for (; !isLeaf(r);)
		r = r->childs[0];
	return r->word;
}

string tree::getLeafA(PNODE r) {
	for (; !isLeaf(r);)
		r = r->childs[0];
	return r->attr;
}

PNODE tree::getVV() {
	vector<PNODE> store;
	store.push_back(root);
	int n = store.size();
	for (; n;) {
		for (; n; n--) {
			PNODE step = store[0];
			store.erase(store.begin());
			if (isLeaf(step)) {
				if (step->attr == "VV") {
					step->tag = "rel";
					for (; step->parent->attr == "VP";) {
						step = step->parent;
						for (int i = step->childs.size() - 1; i >= 0; i--) {
							string tmp = step->childs[i]->attr;
							if (tmp == "ADVP") {
								tmp = getLeafW(step->childs[i]);
								if (inFeatureW(dis, tmp))
									step->childs[i]->tag = "ARGM-DIS";
								else
									step->childs[i]->tag = "ARGM-ADV";
							}
							else if (tmp == "LCP")
								step->childs[i]->tag = "ARGM-ADV";
							else if (tmp == "NP") {
								tmp = getLeafA(step->childs[i]);
								if (tmp == "NT")
									step->childs[i]->tag = "ARGM-TMP";
							}
						}
					}
					return step;
				}
			}
			else {
				int i, len = step->childs.size();
				for (i = 0; i < len; i++) {
					string tmp = step->childs[i]->attr;
					if (tmp == "IP" || tmp[0] == 'V')
						store.push_back(step->childs[i]);
				}
			}
		}
		n = store.size();
	}
	return NULL;
}

void tree::showH(int deep) {
	for (; deep; deep--) cout << ' ';
}

void tree::showH(ofstream& out, int deep) {
	for (; deep; deep--) out << ' ';
}

void tree::delNode(PNODE r) {
	PNODE parent = r->parent;
	int i = parent->childs.size() - 1;
	for (; i >= 0; i--)
		if (parent->childs[i] == r)break;
	parent->childs.erase(parent->childs.begin() + i);
	freeNode(r);
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
