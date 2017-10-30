#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_LEE 2147483647
#define N 1001

struct node {
	double x, y;
	node(int a, int b) : x(a), y(b) {}
	double gap(node& t) {
		double ans = 0, deltax, deltay;
		deltax = x - t.x;
		deltay = y - t.y;
		return sqrt(deltax*deltax + deltay*deltay);
	}
};

bool cmp_x(node& a, node& b) {
	return a.x < b.x;
}

bool cmp_y(node& a, node& b) {
	return a.y < b.y;
}

double closest_pair(vector<node> stations, vector<node> agents, int n) {
	double ans = stations[0].gap(agents[0]), tmp;
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			tmp = stations[i].gap(agents[j]);
			if (tmp < ans) ans = tmp;
		}
	}
	return ans;
}

int main() {
	int i, t, n, x, y;
	scanf("%d", &t);
	for (; t; t--) {
		scanf("%d", &n);
		vector<node> stations;
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			stations.push_back(node(x, y));
		}
		vector<node> agents;
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			agents.push_back(node(x, y));
		}
		sort(stations.begin(), stations.end(), cmp_x);
		sort(agents.begin(), agents.end(), cmp_x);
		printf("%.3lf\n", closest_pair(stations, agents, n));
	}
	return 0;
}
