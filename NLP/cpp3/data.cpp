#include "data.h"

Data::Data() { addHeadWords(); }

Data::~Data() {}

bool Data::getNextLine(ifstream& in) {
	step = 0;
	clear();
	int pre, cur, len, tag = 1;
	string line = "", w;
	char rel[4] = "rel", *strTag;
	word tmp;
	if (getline(in, line)) {
		len = line.size();
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				w = line.substr(pre, cur - pre);
				tmp.setWordTrain(w);
				strTag = tmp.getTag();
				if (strTag && strlen(strTag) > 1) {
					if (tag && strcmp(strTag, rel) == 0) {
						verb = tmp.getWord();
						tag = 0;
					}
					else
						push(tmp);
				}
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur - pre);
			tmp.setWordTrain(w);
			strTag = tmp.getTag();
			if (strTag && strlen(strTag) > 1) {
				if (tag && strcmp(strTag, rel) == 0) {
					verb = tmp.getWord();
					tag = 0;
				}
				else
					push(tmp);
			}
		}
		return true;
	}
	return false;
}

bool Data::getNextLine2(ifstream& in) {
	step = 0;
	clear();
	int pre, cur, len, tag = 1;
	string line = "", w;
	word tmp;
	if (getline(in, line) && line.size()) {
		len = line.size();
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				w = line.substr(pre, cur - pre);
				tmp.setWordTrain(w);
				push(tmp);
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur - pre);
			tmp.setWordTrain(w);
			push(tmp);
		}
		return true;
	}
	return false;
}

Pair Data::getNext() {
	unsigned int i = step;
	if (i < tags.size() && tags[i][0] == 'S') {
		step++;
		findHeadWord(i, i);
		return Pair(i, i);
	}
	for (++i; i < tags.size(); i++) {
		if (tags[i][0] == 'E') {
			int h = step;
			step = i + 1;
			findHeadWord(h, i);
			return Pair(h, i);
		}
	}
	return Pair(-1, -1);
}

void Data::push(word& w) {
	words.push_back(w.getWord());
	attrs.push_back(w.getAttr());
	tags.push_back(w.getTag());
}

void Data::clear() {
	words.clear();
	attrs.clear();
	tags.clear();
}

void Data::show() {
	for (unsigned int i = 0; i < words.size(); i++)
		cout << words[i] << " " << attrs[i] << " " << tags[i] << endl;
	cout << verb << endl;
	cout << endl;
}

void Data::demo() {
	char filename[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpblee.txt";
	ifstream in(filename);
	for (; getNextLine(in);) {
		Pair p;
		do {
			p = getNext();
			cout << p.first << " " << p.second << endl;
		} while (p.first != -1);
		show();
	}
	in.close();
}

int Data::getHeadWordIndex() {
	return indexHeadWord;
}

void Data::findHeadWord(int h, int t) {
	if (h != t) {
		for (int j = h; j <= t; j++)
			for (int i = 0; i < headWords.size(); i++)
				if (headWords[i] == words[j]) {
					indexHeadWord = j;
					return;
				}
	}
	indexHeadWord = h;
}

void Data::addHeadWords() {
	ifstream in("headWords.txt");
	string str;
	for (; in >> str;)
		headWords.push_back(str);
	in.close();
}

#ifdef STRING_LEE
string Data::v() {
	return verb;
}

string Data::w(int i) {
	return words[i];
}

string Data::a(int i) {
	return attrs[i];
}
#else
long long Data::v() {
	long long ans = 0;
	for (int i = 0; i < verb.size(); i++)
		ans += (ans << 8) + verb[i];
	return ans;
}

long long Data::w(int i) {
	long long ans = 0;
	for (int j = 0; j < words[i].size(); j++)
		ans += (ans << 8) + words[i][j];
	return ans;
}

long long Data::a(int i) {
	long long ans = 0;
	for (int j = 0; j < attrs[i].size(); j++)
		ans += (ans << 8) + attrs[i][j];
	return ans;
}

#endif // STRING_LEE

string Data::t(int i) {
	return tags[i];
}
