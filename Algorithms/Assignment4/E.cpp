#include <stdio.h>  
#include <string.h>  
#include <algorithm>  

using namespace std;

int store[100001];

int max_lee(int a, int b) { return (a > b ? a : b); }

int main() {
	int n, m;
	int sum, maxn, i, s, cnt, mid;
	for (; scanf("%d%d", &n, &m) != EOF; ) {
		sum = 0, maxn = 0;
		for (i = 0; i < n; i++) {
			scanf("%d", &store[i]);
			sum += store[i];
			maxn = max_lee(maxn, store[i]);
		}
		for (; maxn < sum; ) {
			mid = (sum + maxn) / 2;
			printf("sum=%d, mid=%d, maxn=%d -> ", sum, mid, maxn);
			s = 0, cnt = 0;
			for (i = 0; i < n; i++) {
				s += store[i];
				if (s > mid) {
					s = store[i];
					cnt++;
				}
			}
			if (cnt < m) sum = mid;
			else maxn = mid + 1;
			printf("sum=%d, mid=%d, maxn=%d\n", sum, mid, maxn);
		}
		printf("%d\n", maxn);
	}
	return 0;
}

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

#define MAX_LEE 2147483647
#define N 100001

int store[N];
int index[N];
int ans;

void calc(int n) {
	int tmp, step = 0;
	int i, h = 0;
	for (i = 1; i < n; i++) {
		if (index[i]) {
			if (step) {
				tmp = store[i - 1] - store[h];
				if (tmp > step)
					step = tmp;
				h = i - 1;
			}
			else {
				h = i - 1;
				step = store[h];
			}
		}
	}
	tmp = store[n - 1] - store[h];
	if (tmp > step)	step = tmp;
	if (step < ans)	ans = step;
}

void show(int n, int tag = 0) {
	for (int i = 0; i < n; i++) {
		if (tag)
			cout << store[i] << " ";
		else
			cout << index[i] << " ";
	}
	cout << endl;
}

void dfs(int n, int m, int h) {
	if (m == 0) {
		//show(n);
		calc(n);
		return;
	}
	for (int i = h; i < n && (i + m - 1) < n; i++) {
		index[i] = 1;
		dfs(n, m - 1, i + 1);
		index[i] = 0;
	}
}

int main() {
	int n, m, i, sum = 0, tmp;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%d", &tmp);
		sum += tmp;
		store[i] = sum;
		index[i] = 0;
	}
	ans = MAX_LEE;
	dfs(n, m - 1, 1);
	printf("%d\n", ans);
	return 0;
}
