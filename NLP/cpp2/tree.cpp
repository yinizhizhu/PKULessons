#include "tree.h"

//#define SHOW_DIVIDE
//#define OUT

// output the prase type of verb
#define SHOWVVPT
#define DEV

#ifdef NEW_OUTPUT
#define OUTFEATURE
#endif // NEW_OUTPUT

tree::tree() {
	root = NULL;
	lsb = false;
	arg_c = 1;

	verb_c = 1;
	head_c = 1;
	hpos_c = 1;
	ptype_c = 1;
	path_c = 1;

	left_c = 1;
	right_c = 1;
	vpos_c = 1;
	ppath_c = 1;
}

tree::~tree() {
	if (root)
		freeNode(root);
}

//add a node with attr and word
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

//judge whether the current node is leaf or not
bool tree::isLeaf(PNODE r) {
	if (r->childs.size() == 0) return true;
	return false;
}

//show the tree with preorder
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

//output the tree into a text file
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

// output the sentence with sturcture of tree into a text file
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

// get the Index 
int tree::getI(PNODE r) {
	int i = leaves.size() - 1;
	for (; i >= 0; i--)
		if (leaves[i] == r)
			return i;
}

//get the leaf node head and tail of the node r
Pair tree::getHT(PNODE r) {
	int h, t;
	PNODE step = r;
	for (; !isLeaf(step);)
		step = step->childs[0];
	h = getI(step);

	step = r;
	for (; !isLeaf(step);)
		step = step->childs[step->childs.size() - 1];
	t = getI(step);
	return Pair(h, t);
}

// output the sentence labeled with structure of tree into a text file
void tree::labelSentence(ofstream& out, PNODE r) {
	if (r) {
		if (isLeaf(r))
			label(out, r);
		else {
			string tag = r->tag;
			if (tag.size()) {
				Pair h_t = getHT(r);
				int h = h_t.first, t = h_t.second;
				int n = t - h + 1, i;
				if (n == 1) {
					r = leaves[h];
					r->tag = "S-" + tag;
					label(out, r);
				}
				else {
					r = leaves[h];
					r->tag = "B-" + tag;
					label(out, r);
					for (i = h + 1; i < t; i++) {
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

// help labelSentence to label each leaf node
void tree::label(ofstream& out, PNODE r) {
	out << r->word << "/" << r->attr << "/";
	if (r->tag.size())
		out << r->tag << " ";
	else
		out << "O ";
}

//// get all the arguments and save with a text file
//void tree::outputPred() {
//	cout << "Finally, the number of predicates: " << predicates.size() << endl;
//	ofstream out("predicates.txt");
//	ITER step = predicates.begin();
//	for (; step != predicates.end(); step++)
//		out << step->first << " " << step->second << endl;
//	out.close();
//}
//
////add the argument into predicates
//void tree::addPred(word& w) {
//	string word, attr, tag;
//	word = w.getWord();
//	attr = w.getAttr();
//	tag = w.getTag();
//	ITER iter = predicates.find(word);
//	if (iter == predicates.end())
//		predicates[word] = tag;
//	else {
//		if (iter->second.find(tag) == -1)
//			iter->second += ' ' + tag;
//	}
//}
//
////add words which are labeled and used to get the predicates
//void tree::addDatabase(char *filename) {
//	cout << "Get the predicates in file " << filename << "...\n";
//	ifstream in(filename);
//
//	/*
//	pre - store the head index of the 'word' which looks just like 'word/attr/tag'
//	cur - store the tail index of the 'word' which is same with pre
//
//	line - get a line of text file
//	w - store the 'word' which is same with pre
//
//	tmp - a class which is used to split the 'word' into word, attr and tag,
//	and supply a api to get the each content of the 'word'
//	(You can get the details in those two files: 'word.cpp' and 'word.h')
//	*/
//	char noTag[10] = "O";
//	int pre, cur, len;
//	string line, w;
//	word tmp;
//	for (; getline(in, line);) {
//		len = line.size();
//		for (pre = 0, cur = 0; cur < len; cur++) {
//			if (line[cur] == ' ') {
//				w = line.substr(pre, cur - pre);
//				tmp.setWordTrain(w);
//
//				if (strcmp(noTag, tmp.getTag()))
//					addPred(tmp);
//
//				pre = cur + 1;
//			}
//		}
//		if (pre < cur) {
//			w = line.substr(pre, cur - pre);
//			tmp.setWordTrain(w);
//
//			if (strcmp(noTag, tmp.getTag()))
//				addPred(tmp);
//		}
//	}
//	in.close();
//	cout << "Now, the number of predicates: " << predicates.size() << endl;
//}
//
//void tree::getPred() {
//	//add words in training data
//	char train[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtrain.txt";
//	addDatabase(train);
//
//	//add words in developing data
//	char dev[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt";
//	addDatabase(dev);
//}

// debugging for feature
void tree::outputFeatureW(vector<string>& con, char *filename) {
	ofstream out(filename);
	for (int i = 0; i < con.size(); i++)
		out << con[i] << endl;
	out.close();
}

// get the feature words
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

//add all the feature for each argument
void tree::addFeatureW() {
	char BNF[FN] = "feature\\BNF.txt", outBNF[FN] = "feature\\bnf_.txt";
	featureW(bnf, BNF, outBNF);

	char DIR[FN] = "feature\\DIR.txt", outDIR[FN] = "feature\\dir_.txt";
	featureW(dir, DIR, outDIR);

	char DIS[FN] = "feature\\DIS.txt", outDIS[FN] = "feature\\dis_.txt";
	featureW(dis, DIS, outDIS);

	char EXT[FN] = "feature\\EXT.txt", outEXT[FN] = "feature\\ext_.txt";
	featureW(ext, EXT, outEXT);

	char FRQ[FN] = "feature\\FRQ.txt", outFRQ[FN] = "feature\\frq_.txt";
	featureW(frq, FRQ, outFRQ);

	char LOC[FN] = "feature\\LOC.txt", outLOC[FN] = "feature\\loc_.txt";
	featureW(loc, LOC, outLOC);

	char MNR[FN] = "feature\\MNR.txt", outMNR[FN] = "feature\\mnr_.txt";
	featureW(mnr, MNR, outMNR);

	char PRP[FN] = "feature\\PRP.txt", outPRP[FN] = "feature\\prp_.txt";
	featureW(prp, PRP, outPRP);

	char TMP[FN] = "feature\\TMP.txt", outTMP[FN] = "feature\\tmp_.txt";
	featureW(tmp, TMP, outTMP);
}

//check whether the word is in feature or not
bool tree::inFeatureW(vector<string>& con, string& str) {
	for (int i = 0; i < con.size(); i++)
		if (con[i].find(str) != -1) //Only if str is in any uint of str can indicate the class str should be tagged with
			return true;
	return false;
}

// check whether the current subtree has a verb or not
bool tree::noVV(PNODE r) {
	bool ans = true;
	if (r) {
		if (r->attr[0] == 'V') return false;
		for (int i = r->childs.size() - 1; i >= 0; i--)
			if (!noVV(r->childs[i])) {
				ans = false;
				break;
			}
	}
	return ans;
}

// label
void tree::label(int l) {
	/*
	ARG0, ARG1 (Exchange position of ARG0 and ARG1 while the SB\LB appears)
	REL
	ARGM - LOC, TMP, ADV, CND, PRP, BNF, MNR, DIR, DIS, FRQ, EXT, TPC(ADV)
	*/
	PNODE vv = getVV(l);
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
			if (mid == -1 && c == vv) mid = h;
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

// get the leftest leaf node word
string tree::getLeafW(PNODE r) {
	for (; !isLeaf(r);)
		r = r->childs[0];
	return r->word;
}

// get the leftest leaf node attr
string tree::getLeafA(PNODE r) {
	for (; !isLeaf(r);)
		r = r->childs[0];
	return r->attr;
}

// get the predicates
void tree::getVerbs() {
#ifndef DEV
	char filename[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtest.txt";
#else
	char filename[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt";
#endif // !DEV

	ifstream in(filename);
	ofstream out("rel.txt");
#ifdef SHOWVVPT
	unordered_map<string, int> lookUp;
	typedef unordered_map<string, int>::iterator lookIter;
#endif // SHOWVVPT

	int pre, cur, len, tag;
	string line, w;
	word tmp;
	char tagS[10] = "rel";
	for (; getline(in, line); ) {
		len = line.size();
		tag = 1;
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				w = line.substr(pre, cur - pre);
				tmp.setWordTrain(w);
				if (tmp.getTag() && strcmp(tmp.getTag(), tagS) == 0) {
					tag = 0;
					break;
				}
				pre = cur + 1;
			}
		}
		if (tag && pre < cur)
			tmp.setWordTrain(line.substr(pre, cur - pre));
		verbs.push_back(tmp.getWord());
#ifdef SHOWVVPT
		lookIter lookTmp = lookUp.find(tmp.getAttr());
		if (lookTmp == lookUp.end())
			lookUp[tmp.getAttr()] = 1;
#endif // SHOWVVPT
	}
	for (int i = 0; i < verbs.size(); i++)
		out << verbs[i] << endl;
#ifdef SHOWVVPT
	for (lookIter lookTmp = lookUp.begin(); lookTmp != lookUp.end(); lookTmp++)
		out << lookTmp->first << endl;
	out.close();
#endif // SHOWVVPT
	in.close();
}

// get the VP node: starting node
PNODE tree::getVNode(PNODE r, string verb) {
	if (r) {
		if (isLeaf(r)) {
			if (r->attr[0] == 'V' && r->word == verb) {
				if (vpos_int.find(r->attr) == vpos_int.end()) {
					vpos_int[r->attr] = vpos_c;
					vpos_c++;
				}
				return r;
			}
		}
		else {
			PNODE ans = NULL;
			for (int i = 0; i < r->childs.size(); i++) {
				ans = getVNode(r->childs[i], verb);
				if (ans)
					return ans;
			}
		}
	}
	return NULL;
}

// label the nodes near the starting node, and return the Starting node
PNODE tree::getVV(int l) {
	cout << "In getVNode: " << verbs[l] << endl;
	PNODE step = getVNode(root, verbs[l]);
	cout << "Out getVNode!" << endl;
	if (step) {
		cout << step->attr << endl;
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
	}
	else
		cout << "What's up? Freak!" << endl;
	return step;
}

// deep
void tree::showH(int deep) {
	for (; deep; deep--) cout << ' ';
}

// show depth
void tree::showH(ofstream& out, int deep) {
	for (; deep; deep--) out << ' ';
}

// do main job: labeling
void tree::firstTry() {
	//getPred();
	//outputPred();
	addFeatureW();
	getVerbs();
#ifndef DEV
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\testTree.txt");
#else
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\devTree.txt");
#endif // !DEV

	Data d;

	ofstream out("demoTree.txt");
	ofstream out2("demoSentence.txt");

	int i, len, process = 0, counter;
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
				for (i = 0; i < len; i++)
					if (part[i] == ')')
						break;
				word = part.substr(0, i);
				step->word = word;
				leaves.push_back(step);
				process -= len - i;
				for (; i < len; i++)
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
				in >> counter;

				//Deal with the data which is shaped into tree
				//
#ifdef OUT
				cout << "Output the original tree" << endl;
				showTree(out, root, 0);
				out << endl;

				showSentence(out2, root);
				out2 << endl;
#endif
				//showSentence(out2, root);
				//out2 << endl;
				//cout << counter << "th is moving on..." << endl;
				/*
				Start Senmantic Roles Labeling (SRL)
				*/
				//pruing(leaves);
				label(counter - 1);
				labelSentence(out2, root);
				out2 << endl;


#ifdef OUT
				cout << "Output the prued tree" << endl;
				showTree(out, root, 0);
				out << endl;
#endif
				//cout << "Done parseing! Free the tree..." << endl;
				freeNode(root);
				root = NULL;
				step = NULL;
				lsb = false;
				leaves.clear();
				vPath.clear();
				//allPath.clear();
			}
		}
		part = "";
	}
	out2.close();
	out.close();
	in.close();
}

// do main job: labeling
void tree::getTrainData() {
	cout << "Training..." << endl;
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\trainTree.txt");
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtrain.txt");
	Data d;
#ifdef OUTFEATURE
	ofstream outFeature("demoFeature.txt"); //for the multi-classifier
	ofstream outFeature2("demoFeature2.txt"); //for the binary classifier
#endif // OUTFEATURE
	int i, len, process = 0, counter;
	string part, attr, word;
	PNODE step = NULL;
	for (; !in.eof();) {
		in >> part;

		len = part.size();
		if (len) {
			if (part[0] == '(') {
				process++;
				attr = part.substr(1, len);
				step = insert(step, attr);
			}
			else {
				for (i = 0; i < len; i++)
					if (part[i] == ')')
						break;
				word = part.substr(0, i);
				step->word = word;
				leaves.push_back(step);
				process -= len - i;
				for (; i < len; i++)
					step = step->parent;
			}
			if (process == 0) {
				in >> counter;
				//cout << counter << "th is moving on..." << endl;
				/*
				Get the training data, and get the features from text file
				verb - predicate
				lsb - voice
				position - before or after predicate
				prase type - PP, NP, etc.
				head word
				POS of head word
				path - the path between candicate node and predicate node in the prase tree
				*/
				if (d.getNextLine(inData)) {
					step = getVNode(root, d.verb); // the node of predicate in the parse tree
					reachRoot(step, vPath); //get the path of current node to the root
					getRelMid(step);

					string ppath;
					Pair p, cLeftRight;
					PNODE a, b, c, up;
					vector<PNODE> pathC;
					unordered_map<PNODE, int> hasIt;//store the pnode with tagging
					for (p = d.getNext(); p.first != -1; p = d.getNext()) {
						int x = p.first, y = p.second;
						int iHW = d.getHeadWordIndex();
						getNode(a, b, d, p);
						if (a == NULL)
							cout << "Freak!!!" << endl;
						if (x != y)
							c = getComP(a, b);
						else
							for (c = a; c->parent->childs.size() == 1; c = c->parent);
						hasIt[c] = 1;
						reachRoot(c, pathC);
						cLeftRight = getLeftRight(c);
						Path path = getPath(pathC, ppath);
						//multi
						if (verb_int.find(d.v()) == verb_int.end()) {
							verb_int[d.v()] = verb_c;
							verb_c++;
						}
						if (head_int.find(d.w(iHW)) == head_int.end()) {
							head_int[d.w(iHW)] = head_c;
							head_c++;
						}
						if (hpos_int.find(d.a(iHW)) == hpos_int.end()) {
							hpos_int[d.a(iHW)] = hpos_c;
							hpos_c++;
						}
						if (ptype_int.find(c->attr) == ptype_int.end()) {
							ptype_int[c->attr] = ptype_c;
							ptype_c++;
						}
						if (path_int.find(path.first) == path_int.end()) {
							path_int[path.first] = path_c;
							path_c++;
						}
						if (ppath_int.find(ppath) == ppath_int.end()) {
							ppath_int[ppath] = ppath_c;
							ppath_c++;
						}

#ifdef OUTFEATURE
						outFeature << verb_int[d.v()] << " ";	//predicate
						outFeature << lsb << " ";	//voice
						outFeature << getPosition(c, step) << " ";	//position
						outFeature << head_int[d.w(iHW)] << " ";
						outFeature << hpos_int[d.a(iHW)] << " ";	//head word & POS of head word
						outFeature << ptype_int[c->attr] << " ";	//phrase type
						outFeature << path_int[path.first] << " ";
						outFeature << cLeftRight.first << " ";
						outFeature << cLeftRight.second << " ";
						outFeature << vpos_int[step->attr] << " ";
						outFeature << ppath_int[ppath] << " ";
						outFeature << path.second << " ";	// path

																							//binary
						outFeature2 << verb_int[d.v()] << " ";	//predicate
						outFeature2 << lsb << " ";	//voice
						outFeature2 << getPosition(c, step) << " ";	//position
						outFeature2 << head_int[d.w(iHW)] << " ";
						outFeature2 << hpos_int[d.a(iHW)] << " ";	//head word & POS of head word
						outFeature2 << ptype_int[c->attr] << " ";	//phrase type
						outFeature2 << path_int[path.first] << " ";
						outFeature2 << cLeftRight.first << " ";
						outFeature2 << cLeftRight.second << " ";
						outFeature2 << vpos_int[step->attr] << " ";
						outFeature2 << ppath_int[ppath] << " ";
						outFeature2 << path.second << " ";	// path

#endif // OUTFEATURE
						word = d.tags[x].substr(2, d.tags[x].size() - 2);
						if (str_int.find(word) == str_int.end()) {
							str_int[word] = arg_c;
							int_str[arg_c] = word;
							arg_c++;
						}

#ifdef OUTFEATURE
						//multi
						outFeature << str_int[word] << endl;

						//binary: tag 1, which means the current node is a candidate
						outFeature2 << 1 << endl;
#endif // OUTFEATURE
					}

					getCandidates(step);

					for (i = 0; i < candidates.size(); i++) {
						c = candidates[i];
						if (hasIt.find(c) == hasIt.end()) {
							HWPair headWord = getHeadWord(c, d.headWords);
							reachRoot(c, pathC);
							cLeftRight = getLeftRight(c);
							Path path = getPath(pathC, ppath);

							if (verb_int.find(d.v()) == verb_int.end()) {
								verb_int[d.v()] = verb_c;
								verb_c++;
							}
							if (head_int.find(headWord.first) == head_int.end()) {
								head_int[headWord.first] = head_c;
								head_c++;
							}
							if (hpos_int.find(headWord.second) == hpos_int.end()) {
								hpos_int[headWord.second] = hpos_c;
								hpos_c++;
							}
							if (ptype_int.find(c->attr) == ptype_int.end()) {
								ptype_int[c->attr] = ptype_c;
								ptype_c++;
							}
							if (path_int.find(path.first) == path_int.end()) {
								path_int[path.first] = path_c;
								path_c++;
							}
							if (ppath_int.find(ppath) == ppath_int.end()) {
								ppath_int[ppath] = ppath_c;
								ppath_c++;
							}
#ifdef OUTFEATURE
							outFeature2 << verb_int[d.v()] << " ";	//predicate
							outFeature2 << lsb << " ";	//voice
							outFeature2 << getPosition(c, step) << " ";	//position
							outFeature2 << head_int[headWord.first] << " ";
							outFeature2 << hpos_int[headWord.second] << " ";	//head word & POS of head word
							outFeature2 << ptype_int[c->attr] << " ";	//phrase type
							outFeature2 << path_int[path.first] << " ";
							outFeature2 << cLeftRight.first << " ";
							outFeature2 << cLeftRight.second << " ";
							outFeature2 << vpos_int[step->attr] << " ";
							outFeature2 << ppath_int[ppath] << " ";
							outFeature2 << path.second << " 0" << endl;	// path
#endif // OUTFEATURE
						}
					}
				}
				else
					cout << "Cannot read data!!!!" << endl;

				//cout << "Done parseing! Free the tree..." << endl;
				freeNode(root);
				root = NULL;
				step = NULL;
				lsb = false;
				leaves.clear();
				vPath.clear();
				//allPath.clear();
			}
		}
		part = "";
	}
	cout << "Done training!" << endl;
#ifdef OUTFEATURE
	outFeature2.close();
	outFeature.close();
#endif // OUTFEATURE
	inData.close();
	in.close();
}

Pair tree::getLeftRight(PNODE r) {
	PNODE p = r->parent;
	int left = 0, right = 0;
	int i, len = p->childs.size();
	for (i = 0; i < len; i++)
		if (p->childs[i] == r) break;
	if (i != 0) {
		if (left_int.find(p->childs[i - 1]->attr) == left_int.end()) {
			left_int[p->childs[i - 1]->attr] = left_c;
			left_c++;
		}
		left = left_int[p->childs[i - 1]->attr];
	}
	if (i != len - 1) {
		if (right_int.find(p->childs[i + 1]->attr) == right_int.end()) {
			right_int[p->childs[i + 1]->attr] = right_c;
			right_c++;
		}
		right = right_int[p->childs[i + 1]->attr];
	}
	return Pair(left, right);
}

HWPair tree::getHeadWord(PNODE r, vector<string>& headWords) {
	PNODE left, right, step;
	for (step = r; !isLeaf(step); step = step->childs[0]);
	left = step;
	for (step = r; !isLeaf(step); step = step->childs[step->childs.size() - 1]);
	right = step;
	int i, len = leaves.size();
	for (i = 0; i < len; i++)
		if (leaves[i] == left)
			break;
	for (; i < len; i++) {
		if (leaves[i] == right) len = 0;
		for (int j = 0; j < headWords.size(); j++)
			if (leaves[i]->word == headWords[j])
				return HWPair(leaves[i]->word, leaves[i]->attr);
	}
	return HWPair(left->word, left->attr);
}

void tree::getRelMid(PNODE step) {
	relMid = leaves.size() - 1;
	for (; relMid >= 0; relMid--)
		if (leaves[relMid] == step)
			return;
}

int tree::getPosition(PNODE a, PNODE v) {
	int i = leaves.size() - 1;
	for (; i >= 0; i--) {
		if (leaves[i] == a)
			return -1;
		if (leaves[i] == v)
			return 1;
	}
}

PNODE tree::getComP(PNODE a, PNODE b) {
	vector<PNODE> pathA, pathB;
	reachRoot(a, pathA);
	reachRoot(b, pathB);
	int iv = pathA.size() - 1, i = pathB.size() - 1;
	for (; pathA[iv] == pathB[i]; iv--, i--);
	return pathA[iv + 1];
}

// get the current node: starting node
void tree::getNode(PNODE& a, PNODE& b, Data& d, Pair& p) {
	int x = p.first, y = p.second;
	int i, j, len = y - x + 1;
	if (len == 1) {
		for (i = relMid - 1, j = relMid + 1; i >= 0 && j < leaves.size(); i--, j++) {
			if (leaves[i]->word == d.words[x] && leaves[i]->attr == d.attrs[x]) {
				a = leaves[i];
				return;
			}
			if (leaves[j]->word == d.words[x] && leaves[j]->attr == d.attrs[x]) {
				a = leaves[j];
				return;
			}
		}
		for (; i >= 0; i--)
			if (leaves[i]->word == d.words[x] && leaves[i]->attr == d.attrs[x]) {
				a = leaves[i];
				return;
			}
		for (; j < leaves.size(); j++)
			if (leaves[j]->word == d.words[x] && leaves[j]->attr == d.attrs[x]) {
				a = leaves[j];
				return;
			}
	}
	else {
		for (i = 0; i < leaves.size(); i++) {
			if (leaves[i]->word == d.words[x] && leaves[i]->attr == d.attrs[x]) {
				for (j = 1; j < len; j++) {
					if (leaves[i + j]->word == d.words[x + j] && leaves[i + j]->attr != d.attrs[x + j])
						break;
				}
				if (j == len) {
					a = leaves[i];
					b = leaves[i + len - 1];
					return;
				}
			}
		}
	}
}

void tree::showPath(vector<PNODE>& path) {
	int i = path.size() - 1;
	for (; i >= 0; i--)
		cout << path[i]->attr << " ";
	cout << endl;
}

void tree::reachRoot(PNODE r, vector<PNODE>& path) {
	path.clear();
	for (; r; r = r->parent)
		path.push_back(r);
}

Path tree::getPath(vector<PNODE>& path, string& ppath) {
	string ans = "";
	int len = 1;
	int iv = vPath.size() - 1, i = path.size() - 1, j;
	for (; iv >= 0 && i >= 0 && vPath[iv] == path[i]; iv--, i--);
	for (j = 0; j <= i; j++)
		ans += path[j]->attr + "-1-";
	len += i+1;
	ppath = ans + path[j]->attr;
	ans += ppath + "-0-";
	for (; iv > 0; iv--)
		ans += vPath[iv]->attr + "-0-";
	len += iv + 1;
	ans += vPath[iv]->attr;
	return Path(ans, len);
}

// eliminate the node from the tree
void tree::delNode(PNODE r) {
	PNODE parent = r->parent;
	int i = parent->childs.size() - 1;
	for (; i >= 0; i--)
		if (parent->childs[i] == r)break;
	parent->childs.erase(parent->childs.begin() + i);
	freeNode(r);
}

// free the room of subtree
void tree::freeNode(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			freeNode(r->childs[i]);
		delete r;
		r = NULL;
	}
}

// do main job: labeling
void tree::secondTry(string labelFile, string outFile) {
	cout << "Labeling..." << endl;
#ifndef DEV
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\testTree.txt");
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtest.txt");
#else
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\devTree.txt");
	//ifstream inLabel("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\cpp\\cpp\\label\\demoFeatureDevLabel.txt");
	ifstream inLabel(labelFile);
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt");
#endif // !DEV

	Data d;
#ifndef DEV
	ofstream outFeature("demoFeatureTest.txt");
#else
#ifdef OUTFEATURE
	ofstream outFeature("demoFeatureDev.txt");
#endif // OUTFEATURE
	//ofstream out2("label\\demoFeatureDevLabelSentence.txt");
	ofstream out2(outFile);
#endif // !DEV

	int i, len, process = 0, counter, label;
	string part, attr, word;
	PNODE step = NULL;
	for (; !in.eof();) {
		in >> part;

		len = part.size();
		if (len) {
			if (part[0] == '(') {
				process++;
				attr = part.substr(1, len);
				step = insert(step, attr);
			}
			else {
				for (i = 0; i < len; i++)
					if (part[i] == ')')
						break;
				word = part.substr(0, i);
				step->word = word;
				leaves.push_back(step);
				process -= len - i;
				for (; i<len; i++)
					step = step->parent;
			}
			if (process == 0) {
				in >> counter;
				//cout << counter << "th is moving on..." << endl;
				/*
				Get the training data, and get the features from text file
				verb - predicate
				lsb - voice
				position - before or after predicate
				prase type - PP, NP, etc.
				head word
				POS of head word
				path - the path between candicate node and predicate node in the prase tree
				*/
				if (d.getNextLine(inData)) {
					step = getVNode(root, d.verb); // the node of predicate in the parse tree
					step->tag = "rel";
					reachRoot(step, vPath); //get the path of current node to the root
					getRelMid(step);

					getCandidates(step);

					string ppath;
					PNODE c, up;
					Pair cLeftRight;
					vector<PNODE> pathC;
					for (i = 0; i < candidates.size(); i++) {
						c = candidates[i];
						HWPair headWord = getHeadWord(c, d.headWords);
						inLabel >> label;
						//cout << label << " ";
						if (label) {
							//cout << int_str[label] << " ";
							c->tag = int_str[label];
						}
						reachRoot(c, pathC);
						cLeftRight = getLeftRight(c);
						Path path = getPath(pathC, ppath);

						if (verb_int.find(d.v()) == verb_int.end()) {
							verb_int[d.v()] = verb_c;
							verb_c++;
						}
						if (head_int.find(headWord.first) == head_int.end()) {
							head_int[headWord.first] = head_c;
							head_c++;
						}
						if (hpos_int.find(headWord.second) == hpos_int.end()) {
							hpos_int[headWord.second] = hpos_c;
							hpos_c++;
						}
						if (ptype_int.find(c->attr) == ptype_int.end()) {
							ptype_int[c->attr] = ptype_c;
							ptype_c++;
						}
						if (path_int.find(path.first) == path_int.end()) {
							path_int[path.first] = path_c;
							path_c++;
						}
						if (ppath_int.find(ppath) == ppath_int.end()) {
							ppath_int[ppath] = ppath_c;
							ppath_c++;
						}
#ifdef OUTFEATURE
						outFeature << verb_int[d.v()] << " ";	//predicate
						outFeature << lsb << " ";	//voice
						outFeature << getPosition(c, step) << " ";	//position
						outFeature << head_int[headWord.first] << " ";
						outFeature << hpos_int[headWord.second] << " ";	//head word & POS of head word
						outFeature << ptype_int[c->attr] << " ";	//phrase type
						outFeature << path_int[path.first] << " ";
						outFeature << cLeftRight.first << " ";
						outFeature << cLeftRight.second << " ";
						outFeature << vpos_int[step->attr] << " ";
						outFeature << ppath_int[ppath] << " ";
						outFeature << path.second << endl;	// path
#endif // OUTFEATURE
					}
					labelSentence(out2, root);
					out2 << endl;
					//cout << endl;
				}
				else
					cout << "Cannot read data!!!!" << endl;

				//cout << "Done parseing! Free the tree..." << endl;
				freeNode(root);
				root = NULL;
				step = NULL;
				lsb = false;
				leaves.clear();
				vPath.clear();
			}
		}
		part = "";
	}
	out2.close();
#ifdef OUTFEATURE
	outFeature.close();
#endif // OUTFEATURE
	inData.close();
	inLabel.close();
	in.close();
	cout << "Finish the labeling!" << endl;
}

// pruing
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

void tree::getCandidates(PNODE r) {
	candidates.clear();
	PNODE pre = NULL;
	for (; r != root; ) {
		pre = r;
		r = r->parent;
		for (int i = 0; i < r->childs.size(); i++)
			if (r->childs[i] != pre)
				candidates.push_back(r->childs[i]);
	}
}