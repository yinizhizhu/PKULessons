#include <iostream>
#include <stdio.h>
#include "word.h"
#include "tree.h"

using namespace std;

void cleanData() {
	ifstream in("data\\cpbtrain.txt");
	ofstream out("train.txt");

	ifstream inE("end.txt");
	char end[6];
	inE >> end;
	inE.close();

	string str;
	for (; !in.eof();) {
		in >> str;
		if (str.size()) {
			word tmp;
			tmp.setWord(str);
			if (strcmp(end, tmp.getWord()) == 0)
				out << tmp.getWord() << endl;
			else
				out << tmp.getWord() << " ";
		}
		str = "";
	}
	out.close();
	in.close();
}

int main() {
	cleanData();

	tree t;
	t.demo();
    return 0;
}
