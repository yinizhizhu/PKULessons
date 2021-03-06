#include <iostream>
#include <math.h>
#include <vector>
#include <stdio.h>

using namespace std;

#define N 203
#define INT_LEE 1e30

bool vis[N];
double dist[N];
double cost[N][N];

struct node {
	int x, y;
	node(int a, int b) : x(a), y(b) {}
};

double distance(node& a, node& b, double v) {
	double deltax, deltay;
	deltax = a.x - b.x;
	deltay = a.y - b.y;
	return sqrt(deltax*deltax + deltay*deltay) / v;
}

void init() {
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			cost[i][j] = INT_LEE;
}

void Dijkstra(int v0, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		dist[i] = cost[v0][i];
		vis[i] = true;
	}
	dist[v0] = 0;
	vis[v0] = false;
	for (i = 0; i < n; i++) {
		double tmp = INT_LEE;
		int u = v0;
		for (j = 0; j < n; j++)
			if (vis[j] && dist[j]<tmp) {
				u = j;
				tmp = dist[j];
			}
		if (u == v0) break;
		vis[u] = false;
		for (j = 0; j < n; j++)
			if (vis[j] && cost[u][j] < INT_LEE && tmp + cost[u][j] < dist[j])
				dist[j] = tmp + cost[u][j];
	}
}

double min_(double a, double b) { return (a < b ? a : b); }

int main() {
	init();
	int x, y, n, i, j, k;
	vector<node> stops;
	scanf("%d %d", &x, &y);
	stops.push_back(node(x, y));	//0 - home
	scanf("%d %d", &x, &y);
	stops.push_back(node(x, y));	//1 - school
	double v1 = 10000.0 / 60.0, v2 = 40000.0 / 60.0;
	for (i = j = 2; scanf("%d %d", &x, &y) != EOF; ) {
		if (x == -1) {
			for (k = i + 1; k < j; k++)
				cost[k - 1][k] = cost[k][k - 1] = min_(distance(stops[k - 1], stops[k], v2), cost[k - 1][k]);
			i = j;
			continue;
		}
		stops.push_back(node(x, y));
		j++;
	}
	n = j;
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (cost[i][j] == INT_LEE)
				cost[i][j] = cost[j][i] = min_(distance(stops[i], stops[j], v1), cost[i][j]);
	Dijkstra(0, n);
	printf("%.0lf\n", dist[1]);
	return 0;
}