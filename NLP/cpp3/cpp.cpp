#include <iostream>
#include <stdio.h>
#include <Python.h>
#include "tree.h"

/*
    DEV - label the cpbdev.txt
*/
//#define DEV
//#define OUTFEATURE


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
	end1 - store the full stop '��'
	end2 - store the '��'
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
	char train[100] = "data/cpbtrain.txt";
	char outTrain[100] = "data/train.txt";
	char outTrainAttr[100] = "data/trainAttr.txt";
	seperateData(train, outTrain, outTrainAttr);

	char dev[100] = "data/cpbdev.txt";
	char outDev[100] = "data/dev.txt";
	char outDevAttr[100] = "data/devAttr.txt";
	seperateData(dev, outDev, outDevAttr);

	char test[100] = "data/cpbtest.txt";
	char outTest[100] = "data/test.txt";
	char outTestAttr[100] = "data/testAttr.txt";
	seperateData(test, outTest, outTestAttr);
}

#define NUMBER_CLASSIFIER 11

void getBest() {
	double tmp, res = 0;
	vector<string> tmpv, resv;
	string str;
#ifdef DEV
	ifstream resIn("devLabel/result.txt");
#else
	ifstream resIn("final/result.txt");
#endif
	while (resIn >> str) {
		tmpv.push_back(str);
		for (int i = 0; i < 8; i++) {
			resIn >> str;
			tmpv.push_back(str);
		}
		resIn >> tmp;
		if (tmp > res) {
			res = tmp;
			resv.clear();
			for (int i = 0; i < 9; i++)
				resv.push_back(tmpv[i]);
		}
		tmpv.clear();
	}
	for (int i = 0; i < 9; i++)
		cout << resv[i] << " ";
	cout << res << endl;
	resIn.close();
}

int main() {
	int savetime = 0;

	if (savetime == 0) {
#ifdef OUTFEATURE
		int select = 10;
#else
        int select = 0;
#endif // OUTFEATURE
		if (select < 10)
#ifdef DEV
			system("python SGD.py 0 1");
#else
			system("python SGD.py 0 0");
#endif // DEV

		tree t;
		//t.firstTry();
		t.getTrainData();
		char cmd[100];
		string classifierName[NUMBER_CLASSIFIER] = { "SGDBinary", "decisionTree", "knn", "gaussianNB", "svm_",
			"bagging_", "randomforest", "svc", "adaboost_", "centroid", "maxEntropy" };
		string indexTag[NUMBER_CLASSIFIER] = { "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };
#ifdef DEV
		string labelFile = "devLabel/demoFeatureDevLabel";
		string outFile = "devLabel/demoFeatureDevLabelSentence";
		string check = "python calc_f1.py 1 ";
#else
		string labelFile = "final/testLabel";
		string outFile = "final/testLabelSentence";
		string check = "python calc_f1.py 0 ";
#endif // DEV

		for (int i = select; i < NUMBER_CLASSIFIER; i++) {
			if (i != 7)
				for (int j = select; j < NUMBER_CLASSIFIER; j++) {
					if (j != 7) {
						string tmpLabel = labelFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
						string tmpOut = outFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
						string tmpCheck = check + " " + indexTag[i] + " " + indexTag[j]
							+ " " + classifierName[i] + " " + classifierName[j] + " " + indexTag[j];
#ifndef OUTFEATURE
						cout << classifierName[i] << " * " << classifierName[j] << ": ";
						cout << tmpLabel << " " << tmpOut << " " << tmpCheck << endl;
#endif //OUTFEATURE
						t.secondTry(tmpLabel, tmpOut);
#ifndef OUTFEATURE
						strcpy(cmd, tmpCheck.c_str());
						system(cmd);
#endif // OUTFEATURE
					}
				}
		}
	}
	else if (savetime == 1) {
#ifdef OUTFEATURE
		int select = 4;
#else
        int select = 0;
#endif // OUTFEATURE
		if (select < 4)
#ifdef DEV
			system("python SGD.py 1 1");
#else
			system("python SGD.py 1 0");
#endif // DEV

		tree t;
		//t.firstTry();
		t.getTrainData();
		char cmd[100];
		string classifierName[NUMBER_CLASSIFIER] = { "decisionTree", "knn", "svm_",
			 "randomforest", "adaboost_", "svc" };
		string indexTag[NUMBER_CLASSIFIER] = { "0", "1", "2", "3", "4", "5" };
#ifdef DEV
		string labelFile = "devLabel/demoFeatureDevLabel";
		string outFile = "devLabel/demoFeatureDevLabelSentence";
		string check = "python calc_f1.py 1 ";
#else
		string labelFile = "final/testLabel";
		string outFile = "final/testLabelSentence";
		string check = "python calc_f1.py 0 ";
#endif // DEV

		for (int i = select; i < 5; i++) {
			for (int j = select; j < 5; j++) {
				string tmpLabel = labelFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
				string tmpOut = outFile + "_" + indexTag[i] + "_" + indexTag[j] + ".txt";
				string tmpCheck = check + " " + indexTag[i] + " " + indexTag[j]
					+ " " + classifierName[i] + " " + classifierName[j] + " " + indexTag[j];
#ifndef OUTFEATURE
				cout << classifierName[i] << " * " << classifierName[j] << ": ";
				cout << tmpLabel << " " << tmpOut << " " << tmpCheck << endl;
#endif
				strcpy(cmd, tmpCheck.c_str());
				t.secondTry(tmpLabel, tmpOut);
#ifndef OUTFEATURE
                system(cmd);
#endif // OUTFEATURE
			}
			cout << endl;
		}
	}
#ifndef OUTFEATURE
	getBest();
#endif // OUTFEATURE
    return 0;
}
