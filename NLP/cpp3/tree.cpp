#include "tree.h"

//#define SHOW_DIVIDE
//#define OUT

// output the prase type of verb
#define SHOWVVPT

/*
    DEV - label the cpbdev.txt
    OUTFEATURE - refresh the features in the text file
*/
//#define DEV
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

void tree::showStr(ofstream& out, vector<string>& str) {
	int len = str.size() - 1, i;
	for (i = 0; i < len; i++)
		out << str[i] << "-";
	out << str[i] << " ";
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

void tree::divideWord(vector<string>& word, string words) {
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
	ifstream inData("data/cpbtrain.txt");
	Data d;
	vector<string> word;
	int i, len, lines = 1, process = 0, counter;

	while (d.getNextLine2(inData)) {
		//if (lines < 1) {
		//	lines++;
		//	continue;
		//}
		//if (lines == 1) {
		//	FILE* out("debug.txt");
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
#ifdef DEV
	ifstream in("data/cpbdev.txt");
#else
	ifstream in("data/cpbtest.txt");
#endif // DEV
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

	ifstream inT("data/trainTree.txt");
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
	ifstream in("data/trainTree.txt");
	ifstream inData("data/cpbtrain.txt");
	Data d;
#ifdef OUTFEATURE
	FILE* outFeature = fopen("trainMulti.txt", "w"); //for the multi-classifier
	FILE* outFeature2 = fopen("trainBinary.txt", "w"); //for the binary classifier
	ofstream Feature("Feature.txt"); //for the multi-classifier
	ofstream Feature2("Feature2.txt"); //for the binary classifier
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
					//vector<string> fusion1;
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
#ifdef OUTFEATURE
						str.clear();
						divideWord(str, d.v());
						index = coderWord.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//predicate
						fprintf(outFeature2, "%.15f ", index);	//predicate
						showStr(Feature, str);
						showStr(Feature2, str);

						fprintf(outFeature, "%d ", lsb);	//voice
						fprintf(outFeature2, "%d ", lsb);	//voice

						fprintf(outFeature, "%d ", getPosition(c, step));	//position
						fprintf(outFeature2, "%d ", getPosition(c, step));	//position

						str.clear();
						divideWord(str, d.w(iHW));
						index = coderWord.getIndex(str);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, str);
						showStr(Feature2, str);

						str.clear();
						str.push_back(d.a(iHW));
						index = coderPos.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//head word & POS of head word
						fprintf(outFeature2, "%.15f ", index);	//head word & POS of head word
						showStr(Feature, str);
						showStr(Feature2, str);

						str.clear();
						str.push_back(c->attr);
						index = coderType.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//phrase type
						fprintf(outFeature2, "%.15f ", index);	//phrase type
						showStr(Feature, str);
						showStr(Feature2, str);

						index = coderType.getIndex(ppath);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, ppath);
						showStr(Feature2, ppath);

						str.clear();
						str.push_back(step->attr);
						index = coderPos.getIndex(str);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, str);
						showStr(Feature2, str);

						index = coderType.getIndex(rpath);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, rpath);
						showStr(Feature2, rpath);

						index = coderType.getIndex(verbf);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, verbf);
						showStr(Feature2, verbf);

						//word = d.v() + d.w(iHW);
						//divideWord(fusion1, word);
						//index = coderWord.getIndex(fusion1);
						//fprintf(outFeature, "%.15f ", index);
						//fprintf(outFeature2, "%.15f ", index);
						//showStr(Feature, fusion1);
						//showStr(Feature2, fusion1);

						index = coderWord.getIndex(firstw);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, firstw);
						showStr(Feature2, firstw);

						index = coderWord.getIndex(lastw);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);
						showStr(Feature, lastw);
						showStr(Feature2, lastw);
						Feature << '\n';
						Feature2 << '\n';
#endif // OUTFEATURE
						word = d.tags[x].substr(2, d.tags[x].size() - 2);
						if (str_int.find(word) == str_int.end()) {
							str_int[word] = arg_c;
							int_str[arg_c] = word;
							arg_c++;
						}
#ifdef OUTFEATURE
						//multi
						fprintf(outFeature, "%d\n", str_int[word]);

						//binary: tag 1, which means the current node is a candidate
						fprintf(outFeature2, "%d\n", 1);
#endif // OUTFEATURE
					}

					getCandidates(step);

					for (i = 0; i < candidates.size(); i++) {
						c = candidates[i];
						if (hasIt.find(c) == hasIt.end()) {
							HWPair headWord = getHeadWord(c, d.headWords, firstw, lastw);
							reachRoot(c, pathC);
							getPath(pathC, ppath, rpath);
#ifdef OUTFEATURE
							str.clear();
							divideWord(str, d.v());
							fprintf(outFeature2, "%.15f ", coderWord.getIndex(str));	//predicate
							showStr(Feature2, str);

							fprintf(outFeature2, "%d ", lsb);	//voice
							fprintf(outFeature2, "%d ", getPosition(c, step));	//position

							str.clear();
							divideWord(str, headWord.first);
							fprintf(outFeature2, "%.15f ", coderWord.getIndex(str));
							showStr(Feature2, str);

							str.clear();
							str.push_back(headWord.second);
							fprintf(outFeature2, "%.15f ", coderPos.getIndex(str));	//head word & POS of head word
							showStr(Feature2, str);

							str.clear();
							str.push_back(c->attr);
							fprintf(outFeature2, "%.15f ", coderType.getIndex(str));	//phrase type
							showStr(Feature2, str);

							fprintf(outFeature2, "%.15f ", coderType.getIndex(ppath));
							showStr(Feature2, ppath);

							str.clear();
							str.push_back(step->attr);
							fprintf(outFeature2, "%.15f ", coderPos.getIndex(str));
							showStr(Feature2, str);

							fprintf(outFeature2, "%.15f ", coderType.getIndex(rpath));
							showStr(Feature2, rpath);
							fprintf(outFeature2, "%.15f ", coderType.getIndex(verbf));
							showStr(Feature2, verbf);

				/*			word = d.v() + headWord.first;
							divideWord(fusion1, word);
							index = coderWord.getIndex(fusion1);
							fprintf(outFeature2, "%.15f ", index);
							showStr(Feature2, str);*/

							fprintf(outFeature2, "%.15f ", coderWord.getIndex(firstw));
							showStr(Feature2, firstw);

							fprintf(outFeature2, "%.15f 0\n", coderWord.getIndex(lastw));
							showStr(Feature2, lastw);
							Feature2 << '\n';
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
	Feature2.close();
	Feature.close();
	fclose(outFeature2);
	fclose(outFeature);
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
	while (!isLeaf(a)) a = a->childs[0];
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
#ifndef OUTFEATURE
	cout << "Labeling..." << endl;
#endif
#ifdef DEV
	ifstream in("data/devTree.txt");
	ifstream inData("data/cpbdev.txt");
#else
	ifstream in("data/testTree.txt");
	ifstream inData("data/cpbtest.txt");
#endif // !DEV

#ifdef OUTFEATURE
#ifdef DEV
	FILE* outFeature = fopen("devFeatureM.txt", "w");
	FILE* outFeature2 = fopen("devFeatureB.txt", "w");
#else
	FILE* outFeature = fopen("testFeatureM.txt", "w");
	FILE* outFeature2 = fopen("testFeatureB.txt", "w");
#endif // !DEV
#else
	ofstream out2(outFile);
#endif // OUTFEATURE

	ifstream inLabel(labelFile);
	Data d;


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
					//vector<string> fusion1;
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
#ifdef OUTFEATURE
						str.clear();
						divideWord(str, d.v());
						index = coderWord.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//predicate
						fprintf(outFeature2, "%.15f ", index);	//predicate

						fprintf(outFeature, "%d ", lsb);	//voice
						fprintf(outFeature2, "%d ", lsb);	//voice
						fprintf(outFeature, "%d ", getPosition(c, step));	//position
						fprintf(outFeature2, "%d ", getPosition(c, step));	//position

						str.clear();
						divideWord(str, headWord.first);
						index = coderWord.getIndex(str);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						str.clear();
						str.push_back(headWord.second);
						index = coderPos.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//head word & POS of head word
						fprintf(outFeature2, "%.15f ", index);	//head word & POS of head word

						str.clear();
						str.push_back(c->attr);
						index = coderType.getIndex(str);
						fprintf(outFeature, "%.15f ", index);	//phrase type
						fprintf(outFeature2, "%.15f ", index);	//phrase type

						index = coderType.getIndex(ppath);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						str.clear();
						str.push_back(step->attr);
						index = coderPos.getIndex(str);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						index = coderType.getIndex(rpath);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						index = coderType.getIndex(verbf);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						//word = d.v() + headWord.first;
						//divideWord(fusion1, word);
						//index = coderWord.getIndex(fusion1);
						//fprintf(outFeature, "%.15f ", index);
						//fprintf(outFeature2, "%.15f ", index);

						index = coderWord.getIndex(firstw);
						fprintf(outFeature, "%.15f ", index);
						fprintf(outFeature2, "%.15f ", index);

						index = coderWord.getIndex(lastw);
						fprintf(outFeature, "%.15f\n", index);
						fprintf(outFeature2, "%.15f\n", index);
#endif // OUTFEATURE
					}
#ifndef OUTFEATURE
					labelSentence(out2, root);
					out2 << endl;
#endif
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
#ifdef OUTFEATURE
	fclose(outFeature);
	fclose(outFeature2);
#else
	out2.close();
#endif // OUTFEATURE
	inData.close();
	inLabel.close();
	in.close();
#ifndef OUTFEATURE
	cout << "Finish the labeling!" << endl;
#endif
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
