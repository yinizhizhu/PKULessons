#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <algorithm>

using namespace std;

#define N 102

int tree[N][3];

int leftMost(int a) {
	for (; tree[a][1] + 1;)
		a = tree[a][1];
	return a;
}

void exchange(int a, int b) {
	int ia = 2, ib = 2;
	int pa = tree[a][0], pb = tree[b][0];
	if (pa == -1 || pb == -1) {
		cout << "Freak!" << endl;
		return;
	}
	if (tree[pa][1] == a) ia = 1;
	if (tree[pb][1] == b) ib = 1;
	tree[pa][ia] = b;
	tree[b][0] = pa;
	tree[pb][ib] = a;
	tree[a][0] = pb;
}

int main() {
	int x, y, z;
	int i, j, t, n, m;
	scanf("%d", &t);
	for (; t; t--) {
		scanf("%d %d", &n, &m);
		for (i = 0; i < n; i++)
			for (j = 0; j < 3; j++)
				tree[i][j] = -1;
		for (; n; n--) {
			scanf("%d %d %d", &x, &y, &z);
			tree[x][1] = y;
			tree[x][2] = z;
			if (y + 1)
				tree[y][0] = x;
			if (z + 1)
				tree[z][0] = x;
		}
		for (; m; m--) {
			scanf("%d %d", &x, &y);
			if (x == 2)
				printf("%d\n", leftMost(y));
			else {
				scanf("%d", &z);
				exchange(y, z);
			}
		}
	}
	return 0;
}