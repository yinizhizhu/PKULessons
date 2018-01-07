7 5
1 3 3
1 5 8
2 3 2
2 4 3
2 5 1
3 4 3
3 5 2

5 5
1 2 20
2 3 30
3 4 20
4 5 20
1 5 100

1 2
1 2 1

3 3
1 2 1
2 3 2
1 3 3 

5 5
1 2 20
2 3 20
3 4 20
2 4 20
4 5 20


#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits.h>
#include <string>
#include <algorithm>

using namespace std;

#define N 1001

typedef struct e {
	int x, w;
	e(int a, int b) : x(a), w(b) {}
}E;

int n, visit[N], con[N];
vector< vector<E> > edges;

void init() {
	int i, len;
	for (i = 1; i < n; i++) {
		visit[i] = 1;
		con[i] = INT_MAX;
	}
	visit[n] = 0;
	len = edges[n].size();
	for (i = 0; i < len; i++)
		con[edges[n][i].x] = edges[n][i].w;
}

int index() {
	int ans, m = INT_MAX;
	for (int i = 1; i < n; i++)
		if (visit[i] && con[i] < m) {
			ans = i;
			m = con[i];
		}
	return ans;
}

void Dijkstra() {
	init();
	int i, j, len;
	for (i = n - 1; i; i--) {
		j = index();
		visit[j] = 0;
		len = edges[j].size();
		for (int k = 0; k < len; k++) {
			int x = edges[j][k].x;
			int w = edges[j][k].w;
			if (visit[x] && con[j] + w < con[x])
				con[x] = con[j] + w;
		}
	}
}

int main() {
	int t, x, y, w;
	scanf("%d %d", &t, &n);
	for (edges.resize(n + 1); t; t--) {
		scanf("%d %d %d", &x, &y, &w);
		edges[x].push_back(E(y, w));
		edges[y].push_back(E(x, w));
	}
	Dijkstra();
	printf("%d\n", con[1]);
	return 0;
}


#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <limits.h>
#include <string>
#include <algorithm>

using namespace std;

#define N 1001

typedef struct e {
	int x, w;
	e(int a, int b) : x(a), w(b) {}
}E;

int n, visit[N], dis[N];
int container[N][N];

void Dijkstra() {
	int i, j;
	for (i = 1; i < n; i++) {
		visit[i] = 1;
		dis[i] = container[n][i];
	}
	dis[n] = 0;
	visit[n] = 0;
	for (i = 2; i <= n; i++) {
		int k = n, tmp = INT_MAX;
		for (j = 1; j <= n; j++) {
			if (visit[j] && dis[j] < tmp) {
				k = j;
				tmp = dis[j];
			}
		}
		visit[k] = 0;
		for (j = 1; j <= n; j++) {
			if (visit[j] && container[k][j] != INT_MAX && container[k][j] + tmp < dis[j])
				dis[j] = container[k][j] + tmp;
		}
	}
	printf("%d\n", dis[1]);
}

int main() {
	int t, x, y, w;
	scanf("%d %d", &t, &n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			container[i][j] = INT_MAX;
	for (; t; t--) {
		scanf("%d %d %d", &x, &y, &w);
		if (container[x][y] > w)	//Not only one edge with two landmarks
			container[x][y] = container[y][x] = w;
	}
	Dijkstra();
	return 0;
}