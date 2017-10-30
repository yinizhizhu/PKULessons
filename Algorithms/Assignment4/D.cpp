#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

#define N 1001

int max_lee(int a, int b) {
	return (a > b ? a : b);
}

int divide_conquer(string& a, string& b) {
	int i, j, na = a.size(), nb = b.size();
	vector< vector<int> > store(na, vector<int>(nb));
	for (i = 0; i < na; i++) {
		if (a[i] == b[0]) {
			store[i][0] = 1;
			break;
		}
		store[i][0] = 0;
	}
	for (; i < na; i++) store[i][0] = 1;
	for (i = 0; i < nb; i++) {
		if (a[0] == b[i]) {
			store[0][i] = 1;
			break;
		}
		store[0][i] = 0;
	}
	for (; i < nb; i++) store[0][i] = 1;
	for (i = 1; i < na; i++) {
		for (j = 1; j < nb; j++) {
			if (a[i] == b[j])
				store[i][j] = store[i - 1][j - 1] + 1;
			else
				store[i][j] = max_lee(store[i - 1][j], store[i][j - 1]);
		}
	}
	return store[na - 1][nb - 1];
}

int main() {
	string a, b;
	for (; cin >> a >> b;)
		cout << divide_conquer(a, b) << endl;
	return 0;
}
