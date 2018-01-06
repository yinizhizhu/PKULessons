#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

#define N 1001

string a, b;
vector< vector<int> > container;

int maxI(int a, int b) {
	if (a > b) return a;
	return b;
}

int dp() {
	int i, j;
	int lenA = a.size(), lenB = b.size();
	for (i = 0; i <= lenA; i++) {
		vector<int> tmp;
		tmp.push_back(0);
		container.push_back(tmp);
	}
	for (i = 1; i <= lenB; i++)
		container[0].push_back(0);
	for (i = 1; i <= lenA; i++) {
		for (j = 1; j <= lenB; j++) {
			if (a[i - 1] == b[j - 1])
				container[i].push_back(container[i - 1][j - 1] + 1);
			else
				container[i].push_back(maxI(container[i - 1][j], container[i][j - 1]));
		}
	}
	return container[lenA][lenB];
}

int main() {
	for (; cin >> a >> b;) {
		container.clear();
		printf("%d\n", dp());
	}
	return 0;
}