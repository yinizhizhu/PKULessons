#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <queue>
#include <unordered_map>

using namespace std;

#define N 100
#define INF 2147483647

int n, s, t;
int d[N], p[N], c[N];
queue <int> q;
int graph[N][N];
bool vis[N];

int spfa_bfs() {
	queue <int> q;
	for (int i = 0; i < n; i++) {
		c[i] = 0;
		d[i] = INF;
		vis[i] = false;
	}
	q.push(s);
	vis[s] = true;
	c[s] = 1;
	d[s] = 0;
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		vis[x] = false;
		for (int k = 0; k < n; k++) {
			int w = graph[x][k];
			if (w != INF) {
				if (d[x] + w < d[k]) {
					d[k] = d[x] + w;
					if (!vis[k]) {
						vis[k] = true;
						c[k]++;
						q.push(k);
						if (c[k]>n)
							return 0;
					}
				}
			}
		}
	}
	return 1;
}

int main() {
	n = 4;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			graph[i][j] = INF;
	graph[0][1] = 1;
	graph[0][2] = 2;
	//graph[1][2] = 1;
	graph[2][3] = 3;
	graph[3][1] = -8;
	s = 0;
	if (spfa_bfs())
		cout << "Yeah!" << endl;
	else
		cout << "Negative circle is in this graph." << endl;
	for (int i = 0; i < n; i++)
		cout << d[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << c[i] << " ";
	cout << endl;
	for (int i = 0; i < n; i++)
		cout << vis[i] << " ";
	cout << endl;
	return 0;
}