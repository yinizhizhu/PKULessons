#include "readText.h"

reader::reader() {
	in.open("FilteredDBLP_noun.txt");
	//in.open("FilteredDBLP.txt");
	//in.open("a.txt");
}

reader::~reader() {
	in.close();
}

bool reader::readTrans() {
	string s = "author";
	string line = "", left, right;
	if (getline(in, line)) {
		if (line[0] == '#') {
			authors.clear();
			for (;;) {
				getline(in, line);
				divide(line, left, right);
				if (left != s) {
					title = right;
					break;
				}
				authors.push_back(right);
			}
			getline(in, line);
			divide(line, left, right);
			year = right;

			getline(in, line);
			divide(line, left, right);
			conference = right;
			return true;
		}
		else {
			cout << line << endl;
			cout << "Somthing is wrong in the head or end of the transaction." << endl;
		}
	}
	cout << "Reach the end of the textfile" << endl;
	return false;
}

void reader::divide(string& line, string& left, string& right) {
	int cur, len = line.size();
	for (cur = 0; cur < len; cur++)
		if (line[cur] == 9)
			break;
	left = line.substr(0, cur);
	right = line.substr(cur+1, len - cur);
	//cout << left << ", " << right << endl;
}