#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 102

typedef struct edge {
	int x, y, w;
	edge() : x(0), y(0), w(0) {}
	edge(int a, int b, int c) : x(a), y(b), w(c) {}
} E;

bool cmp(E& a, E& b) {
	return a.w < b.w;
}

int	uions[N];
int	n, m;

void init() {
	for (int i = 1; i <= n; i++)
		uions[i] = -1;
}

int findRoot(int a) {
	if (uions[a] == -1) return a;
	int ans = uions[a];
	for (; uions[ans] != -1; ans = uions[ans]);
	uions[a] = ans;
	return ans;
}

void merge(int a, int b) {
	uions[b] = a;
}

int prime(vector<E>& e) {
	int ans = e[0].w, w = e[0].w;
	int p = e[0].x, pre = e[0].y;
	int a, b, pa, pb;
	merge(p, pre);
	for (int i = 1; i < m; i++) {
		a = e[i].x, b = e[i].y;
		pa = findRoot(a), pb = findRoot(b);
		if (pa == pb) {
			if (w == e[i].w && (a == pre || b == pre))
				return -1;
			continue;
		}
		if (pa == p) {
			merge(p, pb);
			pre = pb;
		}
		if (pb == p) {
			merge(p, pa);
			pre = pa;
		}
		w = e[i].w;
		ans += w;
	}
	return ans;
}

int main() {
	int t, ans;
	int i, x, y, w;
	scanf("%d", &t);
	for (; t; t--) {
		scanf("%d %d", &n, &m);
		if (n == 1) {
			printf("0\n");
			continue;
		}
		init();
		vector<E> e;
		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &w);
			e.push_back(E(x, y, w));
		}
		sort(e.begin(), e.end(), cmp);
		ans = prime(e);
		if (ans == -1)
			printf("Not Unique!\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}
