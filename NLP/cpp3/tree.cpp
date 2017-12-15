#include "tree.h"

//#define SHOW_DIVIDE
//#define OUT

// output the prase type of verb
#define SHOWVVPT
#define DEV
//#define OUTFEATURE

tree::tree() {
	root = NULL;
	lsb = false;
	arg_c = 1;

	getCoder();
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
		if (leaves[i] == r) break;
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
bool tree::inFeatureW(vector<string>& con, string str) {
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
PNODE tree::getVNode(PNODE r, string& verb, vector<string>& verbf) {
	if (r) {
		if (isLeaf(r)) {
			if (r->attr[0] == 'V' && r->word == verb) {
				PNODE p = r->parent;
				verbf.clear();
				verbf.push_back(p->attr);
				for (int i = 0; i < p->childs.size(); i++)
					verbf.push_back(p->childs[i]->attr);
				return r;
			}
		}
		else {
			PNODE ans = NULL;
			for (int i = 0; i < r->childs.size(); i++) {
				ans = getVNode(r->childs[i], verb, verbf);
				if (ans)
					return ans;
			}
		}
	}
	return NULL;
}

// deep
void tree::showH(int deep) {
	for (; deep; deep--) cout << ' ';
}

// show depth
void tree::showH(ofstream& out, int deep) {
	for (; deep; deep--) out << ' ';
}

bool tree::check(char c) {
	if (c >= '0' && c <= '9')
		return true;
	if (c >= 'a' && c <= 'z')
		return true;
	if (c >= 'A' && c <= 'Z')
		return true;
	if (c == '`' || c == '-')
		return true;
	return false;
}

void tree::divideWord(vector<string>& word, string& words) {
	int j, lenw = words.size();
	for (j = 0; j < lenw;) {
		for (; j < lenw && check(words[j]); j++) {
			string tmp = "";
			tmp += words[j];
			word.push_back(tmp);
		}
		if (j < lenw) {
			if (j == words.find(freak1, j) || j == words.find(freak2, j)) {
				string tmp = "";
				tmp += words[j];
				tmp += words[j + 1];
				word.push_back(tmp);
				j += 2;
			}
			if (j < lenw) {
				string tmp = "";
				tmp += words[j];
				tmp += words[j + 1];
				tmp += words[j + 2];
				j += 3;
				word.push_back(tmp);
			}
		}
	}
}

void tree::getCoder() {
	ifstream inFreak("freak.txt");
	inFreak >> freak1 >> freak2;
	inFreak.close();

	cout << "Initial..." << endl;
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtrain.txt");
	Data d;
	vector<string> word;
	int i, len, lines = 1, process = 0, counter;

	while (d.getNextLine2(inData)) {
		//if (lines < 1) {
		//	lines++;
		//	continue;
		//}
		//if (lines == 1) {
		//	ofstream out("debug.txt");
		//	len = d.words.size();
		//	out << len << endl;
		//	for (i = 0; i < len; i++) {
		//		out << d.words[i] << " " << d.words[i].size() << endl;
		//	}
		//	out.close();
		//	return;
		//}
		word.clear();
		len = d.words.size();
		for (i = 0; i < len; i++)
			divideWord(word, d.words[i]);
		coderWord.insert(word);
		coderPos.insert(d.attrs);
		lines++;
	}
	inData.close();
	cout << "Train Data is done!" << endl;

	lines = 1;
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt");
	while (d.getNextLine2(in)) {
		word.clear();
		len = d.words.size();
		for (i = 0; i < len; i++)
			divideWord(word, d.words[i]);
		coderWord.insert(word);
		coderPos.insert(d.attrs);
		lines++;
	}
	in.close();
	cout << "Dev Data is done!" << endl;

	ifstream inT("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\trainTree.txt");
	string part, attr;
	word.clear();
	for (; !inT.eof();) {
		inT >> part;
		len = part.size();
		if (len) {
			if (part[0] == '(') {
				process++;
				attr = part.substr(1, len);
				word.push_back(attr);
			}
			else {
				for (i = 0; i < len; i++)
					if (part[i] == ')')
						break;
				process -= len - i;
			}
			if (process == 0) {
				inT >> counter;
				coderType.insert(word);
				word.clear();
			}
		}
		part = "";
	}
	inT.close();
	cout << "Tree Data is done!" << endl;

	coderWord.show("words.txt");
	coderPos.show("pos.txt");
	coderType.show("type.txt");
	cout << "Done initial!" << endl;
}

// loading the data into map, and computing the features
void tree::getTrainData() {
	cout << "Training..." << endl;
	ifstream in("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\trainTree.txt");
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtrain.txt");
	Data d;
#ifdef OUTFEATURE
	ofstream outFeature("demoFeature.txt"); //for the multi-classifier
	ofstream outFeature2("demoFeature2.txt"); //for the binary classifier
#endif // OUTFEATURE
	double index;
	int i, len, process = 0, counter;
	string part, attr, word;
	vector<string> str;
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
				if (d.getNextLine(inData)) {
					vector<string> verbf;
					step = getVNode(root, d.verb, verbf); // the node of predicate in the parse tree
					reachRoot(step, vPath); //get the path of current node to the root
					getRelMid(step);

					vector<string> ppath, rpath;
					//vector<string> fusion1, fusion2;
					vector<string> firstw, lastw;
					Pair p;
					PNODE a, b, c;
					vector<PNODE> pathC;
					unordered_map<PNODE, int> hasIt;//store the pnode with tagging
					for (p = d.getNext(); p.first != -1; p = d.getNext()) {
						int x = p.first, y = p.second;

						int iHW = d.getHeadWordIndex();
						getNode(a, b, d, p);

						if (a == NULL)
							cout << "Freak!!!" << endl;

						firstw.clear();
						divideWord(firstw, a->word);
						if (x != y) {
							lastw.clear();
							divideWord(lastw, b->word);
							c = getComP(a, b);
						}
						else {
							lastw.clear();
							divideWord(lastw, a->word);
							for (c = a; c->parent->childs.size() == 1; c = c->parent);
						}
						hasIt[c] = 1;
						reachRoot(c, pathC);
						getPath(pathC, ppath, rpath);
						//multi
						//fusion1 = d.v() + d.w(iHW);
						//fusion2 = d.v() + c->attr;
#ifdef OUTFEATURE
						str.clear();
						divideWord(str, d.v());
						index = coderWord.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//predicate
						outFeature2 << setprecision(9) << index << " ";	//predicate

						outFeature << lsb << " ";	//voice
						outFeature2 << lsb << " ";	//voice

						outFeature << getPosition(c, step) << " ";	//position
						outFeature2 << getPosition(c, step) << " ";	//position

						str.clear();
						divideWord(str, d.w(iHW));
						index = coderWord.getIndex(str);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						str.clear();
						str.push_back(d.a(iHW));
						index = coderPos.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//head word & POS of head word
						outFeature2 << setprecision(9) << index << " ";	//head word & POS of head word

						str.clear();
						str.push_back(c->attr);
						index = coderType.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//phrase type
						outFeature2 << setprecision(9) << index << " ";	//phrase type

						index = coderType.getIndex(ppath);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						str.clear();
						str.push_back(step->attr);
						index = coderPos.getIndex(str);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						index = coderType.getIndex(rpath);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						index = coderType.getIndex(verbf);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";
						//outFeature <<setprecision(9)<< fusionf_int[fusion1] << " ";
						//outFeature <<setprecision(9)<< fusions_int[fusion2] << " ";
						index = coderWord.getIndex(firstw);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";
						index = coderWord.getIndex(lastw);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";
#endif // OUTFEATURE
						word = d.tags[x].substr(2, d.tags[x].size() - 2);
						if (str_int.find(word) == str_int.end()) {
							str_int[word] = arg_c;
							int_str[arg_c] = word;
							arg_c++;
						}
#ifdef OUTFEATURE
						//multi
						outFeature << setprecision(9) << str_int[word] << endl;

						//binary: tag 1, which means the current node is a candidate
						outFeature2 << setprecision(9) << 1 << endl;
#endif // OUTFEATURE
					}

					getCandidates(step);

					for (i = 0; i < candidates.size(); i++) {
						c = candidates[i];
						if (hasIt.find(c) == hasIt.end()) {
							HWPair headWord = getHeadWord(c, d.headWords, firstw, lastw);
							reachRoot(c, pathC);
							getPath(pathC, ppath, rpath);

							//fusion1 = d.v() + headWord.first;
							//fusion2 = d.v() + c->attr;
#ifdef OUTFEATURE
							str.clear();
							divideWord(str, d.v());
							outFeature2 << setprecision(9) << coderWord.getIndex(str) << " ";	//predicate

							outFeature2 << lsb << " ";	//voice
							outFeature2 << getPosition(c, step) << " ";	//position

							str.clear();
							divideWord(str, headWord.first);
							outFeature2 << setprecision(9) << coderWord.getIndex(str) << " ";

							str.clear();
							str.push_back(headWord.second);
							outFeature2 << setprecision(9) << coderPos.getIndex(str) << " ";	//head word & POS of head word

							str.clear();
							str.push_back(c->attr);
							outFeature2 << setprecision(9) << coderType.getIndex(str) << " ";	//phrase type

							outFeature2 << setprecision(9) << coderType.getIndex(ppath) << " ";

							str.clear();
							str.push_back(step->attr);
							outFeature2 << setprecision(9) << coderPos.getIndex(str) << " ";

							outFeature2 << setprecision(9) << coderType.getIndex(rpath) << " ";
							outFeature2 << setprecision(9) << coderType.getIndex(verbf) << " ";
							outFeature2 << setprecision(9) << coderWord.getIndex(firstw) << " ";
							outFeature2 << setprecision(9) << coderWord.getIndex(lastw) << " 0" << endl;

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

HWPair tree::getHeadWord(PNODE r, vector<string>& headWords, vector<string>& firstw, vector<string>& lastw) {
	PNODE left, right;
	for (left = r; !isLeaf(left); left = left->childs[0]);
	for (right = r; !isLeaf(right); right = right->childs[right->childs.size() - 1]);
	firstw.clear();
	divideWord(firstw, left->word);
	lastw.clear();
	divideWord(lastw, right->word);
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
	int i = leaves.size() - 1, ans = 1;
	for (; i >= 0; i--) {
		if (leaves[i] == a) {
			ans = -1;
			break;
		}
		if (leaves[i] == v)
			break;
	}
	return ans;
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

void tree::getPath(vector<PNODE>& path, vector<string>& ppath, vector<string>& rpath) {
	string ans = "";
	int iv = vPath.size() - 1, i = path.size() - 1, j;
	for (; iv >= 0 && i >= 0 && vPath[iv] == path[i]; iv--, i--);
	ppath.clear();
	for (j = 0; j <= i; j++)
		ppath.push_back(path[j]->attr);
	ppath.push_back(path[j]->attr);
	rpath.clear();
	for (; iv > 0; iv--)
		rpath.push_back(vPath[iv]->attr);
	rpath.push_back(vPath[iv]->attr);
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
	ifstream inData("C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt");
#endif // !DEV
	ifstream inLabel(labelFile);
	Data d;
#ifndef DEV
	ofstream outFeature("demoFeatureTest.txt");
#else
#ifdef OUTFEATURE
	ofstream outFeature("demoFeatureDev.txt");
	ofstream outFeature2("demoFeatureDev2.txt");
#endif // OUTFEATURE
	//ofstream out2("label\\demoFeatureDevLabelSentence.txt");
	ofstream out2(outFile);
#endif // !DEV
	double index;
	int i, len, process = 0, counter, label;
	string part, attr, word;
	vector<string> str;
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
					vector<string> verbf;
					step = getVNode(root, d.verb, verbf); // the node of predicate in the parse tree
					step->tag = "rel";
					reachRoot(step, vPath); //get the path of current node to the root
					getRelMid(step);

					getCandidates(step);

					vector<string> ppath, rpath;
					//vector<string> fusion1, fusion2;
					vector<string> firstw, lastw;
					PNODE c;
					vector<PNODE> pathC;
					for (i = 0; i < candidates.size(); i++) {
						c = candidates[i];
						HWPair headWord = getHeadWord(c, d.headWords, firstw, lastw);
						inLabel >> label;
						//cout << label << " ";
						if (label) {
							//cout << int_str[label] << " ";
							c->tag = int_str[label];
						}
						reachRoot(c, pathC);
						getPath(pathC, ppath, rpath);


						//fusion1 = d.v() + headWord.first;
						//fusion2 = d.v() + c->attr;
#ifdef OUTFEATURE
						str.clear();
						divideWord(str, d.v());
						index = coderWord.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//predicate
						outFeature2 << setprecision(9) << index << " ";	//predicate

						outFeature << lsb << " ";	//voice
						outFeature2 << lsb << " ";	//voice
						outFeature << getPosition(c, step) << " ";	//position
						outFeature2 << getPosition(c, step) << " ";	//position

						str.clear();
						divideWord(str, headWord.first);
						index = coderWord.getIndex(str);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						str.clear();
						str.push_back(headWord.second);
						index = coderPos.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//head word & POS of head word
						outFeature2 << setprecision(9) << index << " ";	//head word & POS of head word

						str.clear();
						str.push_back(c->attr);
						index = coderType.getIndex(str);
						outFeature << setprecision(9) << index << " ";	//phrase type
						outFeature2 << setprecision(9) << index << " ";	//phrase type

						index = coderType.getIndex(ppath);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						str.clear();
						str.push_back(step->attr);
						index = coderPos.getIndex(str);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						index = coderType.getIndex(rpath);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";

						index = coderType.getIndex(verbf);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";
						//outFeature <<setprecision(9)<< fusionf_int[fusion1] << " ";
						//outFeature <<setprecision(9)<< fusions_int[fusion2] << " ";
						index = coderWord.getIndex(firstw);
						outFeature << setprecision(9) << index << " ";
						outFeature2 << setprecision(9) << index << " ";
						index = coderWord.getIndex(lastw);
						outFeature << setprecision(9) << index << endl;
						outFeature2 << setprecision(9) << index << endl;
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
	outFeature2.close();
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