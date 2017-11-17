#include <iostream>
#include <stdio.h>
#include "word.h"
#include "tree.h"

using namespace std;

void cleanData(char *filename, char *outname, int tag) {
	ifstream in(filename);
	ofstream out(outname);
	cout << filename << ", " << outname;
	if (tag)
		cout << ": Clean data for cpbtrain..." << endl;
	else
		cout << ": Clean data for cpbtest..." << endl;

	ifstream inE("end.txt");
	string end1;
	char end2[10];
	inE >> end1 >> end2;
	inE.close();

	ofstream out2("checkEnd.txt");

	int pre, cur, len;
	string line;
	word tmp;
	for (; getline(in, line);) {
		len = line.size();
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				if (tag)
					tmp.setWordTrain(line.substr(pre, cur));
				else
					tmp.setWordTest(line.substr(pre, cur));
				out << tmp.getWord();
				if (cur < len - 1)
					out << " ";
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			string w = line.substr(pre, cur);
			out2 << w << endl;
			if (tag)
				tmp.setWordTrain(w);
			else
				tmp.setWordTest(w);
			char *tmp_w = tmp.getWord();
			out << tmp_w;
			if (w[w.length() - 1] != 'U' || w[w.length() - 2] != 'P')
				out << " " << end1;
			else {
				if (strcmp(tmp_w, end2) == 0)
					out << " " << end1;
			}
		}
		out << endl;
	}
	out2.close();
	out.close();
	in.close();
}

int main() {
	char train[100] = "data\\cpbtrain.txt";
	char outTrain[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\train.txt";
	cleanData(train, outTrain, 1);

	char dev[100] = "data\\cpbdev.txt";
	char outDev[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\dev.txt";
	cleanData(dev, outDev, 1);

	char test[100] = "data\\cpbtest.txt";
	char outTest[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\test.txt";
	cleanData(test, outTest, 0);

	tree t;
	t.demo();
    return 0;
}
