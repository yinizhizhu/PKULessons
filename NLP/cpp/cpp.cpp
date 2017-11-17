#include <iostream>
#include <stdio.h>
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
	/*
	end1 - store the full stop '。'
	end2 - store the '》'
	*/
	string end1;
	char end2[10];
	inE >> end1 >> end2;
	inE.close();

	ofstream out2("checkEnd.txt");

	/*
	pre - store the head index of the 'word' which looks just like 'word/attr/tag'
	cur - store the tail index of the 'word' which is same with pre
	counter - counter the number of completed sentence
	index - index the completed sentence

	line - get a line of text file
	w - store the 'word' which is same with pre

	tmp - a class which is used to split the 'word' into word, attr and tag,
		and supply a api to get the each content of the 'word'
		(You can get the details in the two files: 'word.cpp' and 'word.h')
	*/
	int pre, cur, len, counter = 0, index = 1;
	string line, w;
	word tmp;
	for (; getline(in, line); index++) {
		len = line.size();
		for (pre = 0, cur = 0; cur < len; cur++) {
			if (line[cur] == ' ') {
				w = line.substr(pre, cur-pre);
				if (tag)
					tmp.setWordTrain(w);
				else {
					if (w.find(end1) != -1) {
						out2 << index << ": " << line << endl;
						out2 << pre<<", "<<cur<<": "<< w << endl;
						counter++;
					}
					tmp.setWordTest(w);
				}
				out << tmp.getWord();
				if (cur < len - 1)
					out << " ";
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur-pre);
			counter++;
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
	out2 << counter << endl;
	out2.close();
	out.close();
	in.close();
}

void clean() {
	char train[100] = "data\\cpbtrain.txt";
	char outTrain[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\train.txt";
	cleanData(train, outTrain, 1);

	char dev[100] = "data\\cpbdev.txt";
	char outDev[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\dev.txt";
	cleanData(dev, outDev, 1);

	char test[100] = "data\\cpbtest.txt";
	char outTest[100] = "C:\\Users\\codinglee\\Desktop\\自然语言\\Project_coding\\parser\\src\\data\\test.txt";
	cleanData(test, outTest, 0);
}

int main() {
	//clean();

	tree t;
	t.demo();

    return 0;
}
