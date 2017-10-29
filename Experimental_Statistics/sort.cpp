#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>
#include <algorithm>

using namespace std;

#define N 101

struct info {
	double score;
	char name[N];
	info(char n[], double s) {
		strcpy(name, n);
		score = s;
	}
};

bool cmp(info& a, info& b) {
	return a.score < b.score;
}

void data(char inF[], char outF[]) {
	ifstream in(inF);
	ofstream out(outF);
	vector<info> store;
	char name[N];
	double score;
	for (; !in.eof();) {
		in >> name >> score;
		store.push_back(info(name, score));
	}
	in.close();
	sort(store.begin(), store.end(), cmp);
	int i, n = store.size();
	for (i = 0; i < n; i++)
		out << store[i].score << ' ' << store[i].name << '\n';
	out.close();
}

int main() {
	char inf[N] = "g_lee.txt", outf[N] = "g_sort.txt";
	char inf2[N] = "gx_lee.txt", outf2[N] = "gx_sort.txt";
	char inf3[N] = "gy_lee.txt", outf3[N] = "gy_sort.txt";
	data(inf, outf);
	data(inf2, outf2);
	data(inf3, outf3);
	return 0;
}
