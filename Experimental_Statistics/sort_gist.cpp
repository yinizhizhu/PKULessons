#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

struct part {
	string img1, img2;
	double score;
	int i1, i2;
	part(int i, int j, string a, string b, double s) {
		i1 = i;
		i2 = j;
		img1 = a;
		img2 = b;
		score = s;
	}
};

bool cmp(part& a, part& b) {
	return a.score < b.score;
}

int main() {
	vector<part> store;
	string a, b;
	double s;
	int i, j;
	ifstream in("similar.txt");
	ofstream out("sort.txt");
	while (in >> i >> j >> s >> a >> b)
		store.push_back(part(i, j, a, b, s));
	sort(store.begin(), store.end(), cmp);
	for (int i = 0; i < store.size(); i++)
		out << store[i].score << " " << store[i].i1 << " " << store[i].img1 << " " << store[i].i2 << " " << store[i].img2 << "\n";
	out.close();
	in.close();
	return 0;
}