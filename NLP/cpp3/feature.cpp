#include "feature.h"

coder::coder() { size = 2; }

coder::~coder() { container.clear(); }

void coder::insert(vector<string>& str) {
	int i = str.size() - 1;
	for (; i >= 0; i--)
		if (container.find(str[i]) == container.end()) {
			container[str[i]] = size;
			size++;
		}
}

double coder::getIndex2(vector<string>& str) {
	double ans = 0, basis = log(size);
	int i = str.size() - 1;

	ofstream out("debug.txt", ios::app);

	for (; i >= 0; i--) {
		if (container.find(str[i]) == container.end()) {
			out << str[i] << endl;
			cout << "Something is Wrong!" << endl;
		}
		else
			ans += log(container[str[i]]);
		ans *= basis;
	}
	out.close();
	return log(ans);
}

double coder::getIndex(vector<string>& str) {
	double ans = 0;
	int i = 0, len = str.size();
	for (; i < len; i++) {
		if (container.find(str[i]) == container.end()) {
			cout << "Something is Wrong!" << endl;
		}
		else
			ans += container[str[i]];
		ans *= size;
	}
	if (ans < 0) {
		cout << "Overflow!!!" << endl;
		return 0;
	}
	return log(ans);
}

void coder::show(string outF) {
	ofstream out(outF);
	out << size << endl;
	for (SIter iter = container.begin(); iter != container.end(); iter++)
		out << iter->first << " " << iter->second << endl;
	out.close();
}