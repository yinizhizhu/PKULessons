#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits.h>
#include <string>
#include <algorithm>

using namespace std;

#define N 101

typedef struct w {
	int P, L;
	w() :P(0), L(0) {}
	w(int p, int l) :P(p), L(l) {}
}W;

vector<W> woods;
int dis[N], visit[N];
int container[N][N];

int m, n, low, up;

bool check(int i) {
	if (woods[i].L >= low && woods[i].L <= up)
		return true;
	return false;
}

int Dijkstra() {
	int i, j, k, tmp;
	for (i = 1; i <= n; i++) {
		dis[i] = woods[i].P;
		if (check(i))
			visit[i] = 1;
		else
			visit[i] = 0;
	}
	for (i = 1; i <= n; i++) {
		k = n, tmp = INT_MAX;
		for (j = 1; j <= n; j++)
			if (visit[j] && tmp > dis[j]) {
				k = j;
				tmp = dis[j];
			}
		visit[k] = 0;
		if (k == 1)
			break;
		for (j = 1; j <= n; j++)
			if (visit[j] && container[k][j] != INT_MAX && container[k][j] + tmp < dis[j])
				dis[j] = container[k][j] + tmp;
	}
	return dis[1];
}

int main() {
	int i, j, p, l, x;
	woods.push_back(W());
	scanf("%d %d", &m, &n);
	for (i = 1; i <= n; i++)
		for (j = 1; j <= n; j++)
			container[i][j] = INT_MAX;
	for (i = 1; i <= n; i++) {
		scanf("%d %d %d", &p, &l, &x);
		woods.push_back(W(p, l));
		for (j = 0; j < x; j++) {
			scanf("%d %d", &p, &l);
			if (container[p][i] > l)
				container[p][i] = l;
		}
	}
	int ans = woods[1].P;
	for (i = 0; i <= m; i++) {
		up = woods[1].L + i;
		low = up - m;
		x = Dijkstra();
		if (x < ans) ans = x;
	}
	printf("%d\n", ans);
	return 0;
}