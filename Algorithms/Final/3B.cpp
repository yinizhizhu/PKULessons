#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define INF 1e20

typedef struct node {
	int x, y;
	node(int a, int b) : x(a), y(b) {}
} NODE;
vector<NODE> stations, agents;

bool cmpxy(NODE& a, NODE& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.y < b.y;
}

bool cmpys(int a, int b) {
	return stations[a].y < stations[b].y;
}

bool cmpya(int a, int b) {
	return agents[a].y < agents[b].y;
}

int t, n;
double dis(NODE& a, NODE& b) {
	double delx = a.x - b.x;
	double dely = a.y - b.y;
	return sqrt(delx*delx + dely*dely);
}

double distance(int i, int j) {
	return dis(stations[i], agents[j]);
}

double minD(double a, double b) {
	if (a > b) return b;
	return a;
}

double closest(int head, int tail) {
	int lenI = tail - head;
	if (1 == lenI)
		return distance(head, head);
	else if (lenI == 2) {
		double ans = distance(head, head), tmp;
		tmp = distance(head, head + 1);
		if (ans > tmp) ans = tmp;
		tmp = distance(head + 1, head);
		if (ans > tmp) ans = tmp;
		tmp = distance(head + 1, head + 1);
		if (ans > tmp) ans = tmp;
		return ans;
	}
	int mid = (head + tail) / 2, i, j, lenJ;
	double d1 = closest(head, mid);
	double d2 = closest(mid, tail);
	double d = minD(d1, d2);
	vector<int> indexS, indexA;
	for (i = head; i < tail; i++)
		if (fabs(agents[mid].x - stations[i].x) <= d)
			indexS.push_back(i);
	sort(indexS.begin(), indexS.end(), cmpys);
	for (i = head; i < tail; i++)
		if (fabs(stations[mid].x - agents[i].x) <= d)
			indexA.push_back(i);
	sort(indexA.begin(), indexA.end(), cmpya);
	lenI = indexS.size();
	lenJ = indexA.size();
	for (i = 0; i < lenI; i++)
		for (j = 0; j < lenJ; j++)
			if (fabs(stations[indexS[i]].y - agents[indexA[j]].y) <= d) {
				double d3 = distance(indexS[i], indexA[j]);
				if (d3 < d) d = d3;
			}
	return d;
}

int main() {
	int i, x, y;
	scanf("%d", &t);
	for (; t; t--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			stations.push_back(NODE(x, y));
		}
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			agents.push_back(NODE(x, y));
		}
		sort(stations.begin(), stations.end(), cmpxy);
		sort(agents.begin(), agents.end(), cmpxy);
		printf("%.3lf\n", closest(0, n));
		stations.clear();
		agents.clear();
	}
	return 0;
}