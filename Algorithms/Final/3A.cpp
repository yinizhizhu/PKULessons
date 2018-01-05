#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 20001

int container[N], n, ans;

void inversionP(int h, int t) {
	int len = t - h;
	if (len == 1) return;
	else if (len == 2) {
		if (container[t - 1] < container[h]) {
			int tmp = container[t - 1];
			container[t - 1] = container[h];
			container[h] = tmp;
			ans++;
		}
		return;
	}
	int mid = (t + h) / 2;
	inversionP(h, mid);
	inversionP(mid, t);
	int i, j;
	vector<int> store;
	for (i = h, j = mid; i < mid && j < t;) {
		if (container[i] <= container[j]) {
			store.push_back(container[i]);
			i++;
		}
		else {
			store.push_back(container[j]);
			ans += mid - i;
			j++;
		}
	}
	for (; i < mid; i++)
		store.push_back(container[i]);
	for (; j < t; j++)
		store.push_back(container[j]);
	for (i = h, j = 0; i < t; i++, j++)
		container[i] = store[j];
}

int main() {
	for (scanf("%d", &n); n; scanf("%d", &n)) {
		ans = 0;
		for (int i = 0; i < n; i++)
			scanf("%d", container + i);
		inversionP(0, n);
		printf("%d\n", ans);
	}
	return 0;
}