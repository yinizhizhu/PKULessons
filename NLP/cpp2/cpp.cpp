#include <iostream>
#include <stdio.h>
#include <Python.h>
#include "tree.h"

#define SELECT_METHOD

using namespace std;

void seperateData(char *filename, char *outname, char *outAttr) {
	ifstream in(filename);
	ofstream out(outname);
	ofstream outA(outAttr);

	cout << filename << "\n   " << outname << endl;
	cout << "---> Clean data..." << endl;

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
				w = line.substr(pre, cur - pre);
				tmp.setWordTrain(w);
				out << tmp.getWord();
				outA << tmp.getAttr();
				if (cur < len - 1) {
					out << " ";
					outA << " ";
				}
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur - pre);
			counter++;
			tmp.setWordTrain(w);
			char *tmp_w = tmp.getWord();
			out << tmp_w;
			outA << tmp.getAttr();
		}
		out << endl;
		outA << endl;
	}
	out2 << counter << endl;
	out2.close();

	outA.close();
	out.close();
	in.close();
}

void cleanData(char *filename, char *outname, char *outAttr, int tag) {
	ifstream in(filename);
	ofstream out(outname);
	ofstream outA(outAttr);

	cout << filename << "\n   " << outname << endl;
	if (tag)
		cout << "---> Clean data... " << endl;
	else
		cout << "---> Clean data..." << endl;

	ifstream inE("end.txt");
	/*
	end1 - store the full stop '¡£'
	end2 - store the '¡·'
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
				w = line.substr(pre, cur - pre);
				if (tag)
					tmp.setWordTrain(w);
				else {
					if (w.find(end1) != -1) {
						out2 << index << ": " << line << endl;
						out2 << pre << ", " << cur << ": " << w << endl;
						counter++;
					}
					tmp.setWordTest(w);
				}
				out << tmp.getWord();
				outA << tmp.getAttr();
				if (cur < len - 1) {
					out << " ";
					outA << " ";
				}
				pre = cur + 1;
			}
		}
		if (pre < cur) {
			w = line.substr(pre, cur - pre);
			counter++;
			if (tag)
				tmp.setWordTrain(w);
			else
				tmp.setWordTest(w);
			char *tmp_w = tmp.getWord();
			out << tmp_w;
			outA << tmp.getAttr();
			if (w[w.length() - 1] != 'U' || w[w.length() - 2] != 'P') {
				out << " " << end1;
				outA << " " << endl;
			}
			else {
				if (strcmp(tmp_w, end2) == 0) {
					out << " " << end1;
					outA << " " << end1;
				}
			}
		}
		out << endl;
		outA << endl;
	}
	out2 << counter << endl;
	out2.close();

	outA.close();
	out.close();
	in.close();
}

void clean() {
	char train[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtrain.txt";
	char outTrain[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\train.txt";
	char outTrainAttr[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\trainAttr.txt";
	seperateData(train, outTrain, outTrainAttr);

	char dev[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbdev.txt";
	char outDev[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\dev.txt";
	char outDevAttr[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\devAttr.txt";
	seperateData(dev, outDev, outDevAttr);

	char test[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\cpbtest.txt";
	char outTest[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\test.txt";
	char outTestAttr[100] = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\data\\testAttr.txt";
	seperateData(test, outTest, outTestAttr);
}

int main() {
#ifdef SELECT_METHOD
	system("python SGD.py");

	tree t;
	//t.firstTry();
	t.getTrainData();

	char cmd[100];
	string classifierName[9] = { "SGDBinary", "decisionTree", "knn", "gaussianNB", "svm_",
		"bagging_", "randomforest", "adaboost", "adaboost_" };
	string indexTag[9] = { "0", "1", "2", "3", "4", "5", "6", "7", "8" };
	string labelFile = "C:\\Users\\codinglee\\Desktop\\NLP\\Project_coding\\cpp\\cpp\\label\\demoFeatureDevLabel";
	string outFile = "label\\demoFeatureDevLabelSentence";
	string check = "python calc_f1.py";
	for (int i = 8; i < 9; i++) {
		if (i != 7)
			for (int j = 0; j < 1; j++) {
				string tmpLabel = labelFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
				string tmpOut = outFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
				string tmpCheck = check + " " + indexTag[i] + " " + indexTag[j];
				cout << tmpLabel << " " << tmpOut << " " << tmpCheck << endl;
				t.secondTry(tmpLabel, tmpOut);
				strcpy(cmd, tmpCheck.c_str());
				cout << classifierName[i] << " * " << classifierName[j] << ": ";
				system(cmd);
			}
	}


#else
#ifndef NEW_OUTPUT
	system("python SGD_.py");
#endif // NEW_OUTPUT
#endif // SELECT_METHOD
    return 0;
}
