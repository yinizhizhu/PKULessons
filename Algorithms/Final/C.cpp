#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define N 1001

int n, uions[N*N], container[N][N];

int index(int x, int y) {
	return ((x - 1)*n + y);
}

int findRoot(int s) {
	int pre = uions[s];
	if (pre == -1) return s;
	for (; uions[pre] != -1;) pre = uions[pre];
	uions[s] = pre;
	return pre;
}

void merge(int cur, int root) {
	if (cur == root) return;
	if (cur < root) uions[root] = cur;
	else uions[cur] = root;
}

int main() {
	int cur, c;
	int t, m, i, j;
	scanf("%d", &t);
	for (; t; t--) {
		scanf("%d %d", &n, &m);
		for (i = 0, j = n*n; i <= j; i++) uions[i] = -1;
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				container[i][j] = 0;
		vector<int> down;
		for (c = 1; m; m--, c++) {
			scanf("%d %d", &i, &j);
			container[i][j] = 1;
			cur = index(i, j);
			if (i == 1)
				uions[cur] = 0;
			else {
				if (container[i - 1][j])
					merge(findRoot(cur), findRoot(index(i - 1, j)));
			}
			if (j > 1) {
				if (container[i][j - 1])
					merge(findRoot(cur), findRoot(index(i, j - 1)));
			}
			if (j < n) {
				if (container[i][j + 1])
					merge(findRoot(cur), findRoot(index(i, j + 1)));
			}
			if (i < n) {
				if (container[i + 1][j])
					merge(findRoot(cur), findRoot(index(i + 1, j)));
			}
			else
				down.push_back(cur);
			for (i = down.size() - 1; i >= 0; i--)
				if (findRoot(down[i]) == 0)
					break;
			if (i >= 0) {
				for (i = 1; i < m; i++)
					scanf("%d %d", &cur, &j);
				printf("%d\n", c);
				break;
			}
		}
		if (m == 0)
			printf("-1\n");
	}
	return 0;
}