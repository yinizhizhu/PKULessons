#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <math.h>
#include <functional>
#include <algorithm>

using namespace std;

#define N 200001

long long ans;
int store[N];

void getReverse(int head, int tail) {
	if (head == tail - 1) return;
	if (head == tail - 2) {
		if (store[head] > store[head + 1] * 2) {
			ans++;
		}
		if (store[head] > store[head + 1]) {
			int tmp = store[head];
			store[head] = store[head + 1];
			store[head + 1] = tmp;
		}
		return;
	}
	int mid = (head + tail) / 2;
	getReverse(head, mid);
	getReverse(mid, tail);
	int i, j;
	for (i = head, j = mid; j < tail && i < mid;) {
		if (store[i] > store[j] * 2) {
			ans += mid - i;
			j++;
		}
		else
			i++;
	}
	vector<int> tmp;
	for (i = head, j = mid; i < mid &&j < tail;) {
		if (store[i] < store[j])
			tmp.push_back(store[i++]);
		else
			tmp.push_back(store[j++]);
	}
	for (; i < mid; i++) tmp.push_back(store[i]);
	for (; j < tail; j++) tmp.push_back(store[j]);
	for (i = head, j = 0; i < tail; i++, j++)
		store[i] = tmp[j];
}

int main() {
	int n;
	while (scanf("%d", &n) && n) {
		int i;
		ans = 0;
		for (i = 0; i < n; i++) {
			scanf("%d", &store[i]);
		}
		getReverse(0, n);
		printf("%lld\n", ans);
	}
	return 0;
}