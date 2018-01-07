#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <limits.h>
#include <unordered_map>

using namespace std;

#define N 31
#define INF 1e20

typedef struct e {
	int x, y;
	double ex;
	e(int a, int b, double c) : x(a), y(b), ex(c) {}
}E;

vector<E> edges;
double dis[N];
int n, m;

bool Dijkstra() {
	int i, j;
	for (i = 1; i < n; i++)
		dis[i] = INF;
	dis[0] = 0;
	for (i = 1; i < n; i++)
		for (j = 0; j < m; j++)
			if (dis[edges[j].x] > dis[edges[j].y] + edges[j].ex)
				dis[edges[j].x] = dis[edges[j].y] + edges[j].ex;
	for (j = 0; j < m; j++)
		if (dis[edges[j].x] > dis[edges[j].y] + edges[j].ex)
			return true;
	return false;
}

int main() {
	double ex;
	int i, step;
	string str1, str2;
	for (scanf("%d", &n), step = 1; n; scanf("%d", &n), step++) {
		unordered_map<string, int> index;
		for (i = 0; i < n; i++) {
			cin >> str1;
			index[str1] = i;
		}
		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			cin >> str1 >> ex >> str2;
			edges.push_back(E(index[str1], index[str2], -log(ex)));
		}
		printf("Case %d: ", step);
		if (Dijkstra())
			printf("Yes\n");
		else
			printf("No\n");
		edges.clear();
	}
	return 0;
}


#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <limits.h>
#include <unordered_map>

using namespace std;

#define N 31
#define INF 1e20

typedef struct e {
	int x, y;
	double ex;
	e(int a, int b, double c) : x(a), y(b), ex(c) {}
}E;

vector<E> edges;
double dis[N];
int n, m;

bool Dijkstra() {
	int i, j;
	for (i = 1; i < n; i++)
		dis[i] = INF;
	dis[0] = 0;
	for (i = 1; i < n; i++)
		for (j = 0; j < m; j++)
			if (dis[edges[j].x] > dis[edges[j].y] + edges[j].ex)
				dis[edges[j].x] = dis[edges[j].y] + edges[j].ex;
	for (j = 0; j < m; j++)
		if (dis[edges[j].x] > dis[edges[j].y] + edges[j].ex)
			return true;
	return false;
}

int main() {
	double ex;
	int i, step;
	char t1[99], t2[99];
	for (scanf("%d", &n), step = 1; n; scanf("%d", &n), step++) {
		unordered_map<string, int> index;
		for (i = 0; i < n; i++) {
			scanf("%s", t1);
			index[t1] = i;
		}
		scanf("%d", &m);
		for (i = 0; i < m; i++) {
			scanf("%s %lf %s", t1, &ex, t2);
			edges.push_back(E(index[t1], index[t2], -log(ex)));
		}
		printf("Case %d: ", step);
		if (Dijkstra())
			printf("Yes\n");
		else
			printf("No\n");
		edges.clear();
	}
	return 0;
}