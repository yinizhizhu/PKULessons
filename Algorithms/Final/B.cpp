#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define N 1001

bool tag;

typedef struct node {
	int x, y;
	double h, t;
	node(int a, int b, int d) {
		x = a;
		y = b;
		if (d < b) tag = false;
		else {
			double del = sqrt(d*d - b*b);
			h = x - del;
			t = x + del;
		}
	}
}NODE;

bool cmp(NODE& a, NODE& b) {
	return a.t < b.t;
}

int main() {
	int n, d, index = 1;
	while (scanf("%d %d", &n, &d) && n) {
		int ans = 0;
		int i, x, y;
		tag = true;
		vector<NODE> store;
		for (i = 0; i < n; i++) {
			scanf("%d %d", &x, &y);
			store.push_back(NODE(x, y, d));
		}
		printf("Case %d: ", index);
		if (tag) {
			sort(store.begin(), store.end(), cmp);
			double h = store[n - 1].h;
			ans = 1;
			for (i = n - 2; i >= 0; i--) {
				if (store[i].t < h) {
					h = store[i].h;
					ans++;
				}
				else {
					if (store[i].h > h)
						h = store[i].h;
				}
			}
			printf("%d\n", ans);
		}
		else
			printf("-1\n");
		index++;
	}
	return 0;
}