#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 20001

void swap_(int& a, int& b) {
	int tmp = b;
	b = a;
	a = tmp;
}

int inverP(int store[], int h, int t) {
	if (t - h == 1)
		return 0;
	if (t - h == 2) {
		if (store[h] > store[h + 1]) {
			swap_(store[h], store[h + 1]);
			return 1;
		}
		return 0;
	}
	int mid = h + (t - h) / 2, s, i, j;
	s = inverP(store, h, mid);
	s += inverP(store, mid, t);
	for (i = h, j = mid; i < mid && j < t;) {
		if (store[i] > store[j]) {
			s += mid - i;
			j++;
		}
		else
			i++;
	}
	vector<int> ans;
	for (i = h, j = mid; i < mid && j < t;) {
		if (store[i] > store[j]) {
			ans.push_back(store[j]);
			j++;
		}
		else if (store[i] == store[j]) {
			ans.push_back(store[i]);
			ans.push_back(store[i]);
			j++;
			i++;
		}
		else {
			ans.push_back(store[i]);
			i++;
		}
	}
	for (; i < mid; i++)
		ans.push_back(store[i]);
	for (; j < t; j++)
		ans.push_back(store[j]);
	for (i = h; i < t; i++)
		store[i] = ans[i-h];
	return s;
}

//void show(int store[], int n) {
//	for (int i = 0; i < n; i++)
//		cout << store[i] << " ";
//	cout << endl;
//}

int main() {
	int store[N], i, n;
	for (scanf("%d", &n); n; scanf("%d", &n)) {
		for (i = 0; i < n; i++)
			scanf("%d", store + i);
		printf("%d\n", inverP(store, 0, n));
		//show(store, n);
	}
	return 0;
}
