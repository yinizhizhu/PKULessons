3 2
John 0 1
Rose 1
Mary 1
5 4
ACM 1 2 3
ICPC 0 1
Asian 0 2 3
Regional 1 2
ShangHai 0 2
6 2
a 0 1
b 0
c 1
d 0
e 0
f 1
0 0

#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <assert.h>
#include <queue>
#include <algorithm>

using namespace std;

#define N 1600
#define M 504000

typedef long long LL;

int length(int n) {
	if (n) return int(log10(n) + 1);
	return 1;
}

struct edge {
	int v, cap, next;
};
edge e[M];

int head[N], level[N], cur[N];
int num_of_edges;

int add_edge(int u, int v, int c1, int c2) {
	int& i = num_of_edges;

	assert(c1 >= 0 && c2 >= 0 && c1 + c2 >= 0); // check for possibility of overflow
	e[i].v = v;
	e[i].cap = c1;
	e[i].next = head[u];
	head[u] = i++;

	e[i].v = u;
	e[i].cap = c2;
	e[i].next = head[v];
	head[v] = i++;
	return i;
}

void dinic_init(int n, int m, int ans) {
	num_of_edges = 0;
	memset(head, -1, sizeof(head));
	int t = n + m + 1, i;
	for (i = 1; i <= n; i++)
		add_edge(0, i, 1, 0);
	for (i = 1; i <= m; i++)
		add_edge(n + i, t, ans, 0);
}

int dfs(int u, int t, int bn) {
	if (u == t) return bn;
	int left = bn;
	for (int &i = cur[u]; i >= 0; i = e[i].next) {
		int v = e[i].v;
		int c = e[i].cap;
		if (c > 0 && level[u] + 1 == level[v]) {
			int flow = dfs(v, t, min(left, c));
			if (flow > 0) {
				e[i].cap -= flow;
				e[i ^ 1].cap += flow;
				cur[u] = i;
				left -= flow;
				if (!left) break;
			}
		}
	}
	if (left > 0) level[u] = 0;
	return bn - left;
}

bool bfs(int s, int t) {
	memset(level, 0, sizeof(level));
	level[s] = 1;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		if (u == t) return true;
		for (int i = head[u]; i >= 0; i = e[i].next) {
			int v = e[i].v;
			if (!level[v] && e[i].cap > 0) {
				level[v] = level[u] + 1;
				q.push(v);
			}
		}
	}
	return false;
}

LL dinic(int s, int t) {
	LL max_flow = 0;
	while (bfs(s, t)) {
		memcpy(cur, head, sizeof(head));
		max_flow += dfs(s, t, INT_MAX);
	}
	return max_flow;
}

int main() {
	vector< vector<int> > list;
	char name[18], line[3000];
	int i, j, bel, n, m, len, t, flow;
	for (scanf("%d %d", &n, &m); n; scanf("%d %d", &n, &m)) {
		getchar();
		t = m + n + 1;
		int low, mid, up=n;
		for (i = 0; i < n; i++) {
			gets(line);
			vector<int> tmp;
			sscanf(line, "%s", name);
			len = strlen(line);
			for (j = strlen(name) + 1; j < len; j += length(bel) + 1) {
				sscanf(line + j, "%d", &bel);
				tmp.push_back(bel + 1 + n);
			}
			list.push_back(tmp);
		}
		for (low = 1; low < up;) {
			mid = (low + up) / 2;
			dinic_init(n, m, mid);
			for (i = 0; i < n; i++) {
				len = list[i].size();
				for (j = 0; j < len; j++)
					add_edge(i + 1, list[i][j], 1, 0);
			}
			flow = dinic(0, t);
			if (flow >= n)
				up = mid;
			else
				low = mid + 1;
		}
		printf("%d\n", up);
		list.clear();
	}
	return 0;
}
