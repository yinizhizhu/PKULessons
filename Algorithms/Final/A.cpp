#include <iostream>
#include <vector>
#include <stdio.h>

#define N 1005
#define INT_MAX 2147483647

using namespace std;

int main() {
	double dp[N], ver, step, tmp;
	int i, j, r, b, l, n, w[N], v[N];
	dp[0] = 0;
	for (scanf("%d %d %d", &b, &l, &n); n; scanf("%d %d %d", &b, &l, &n)) {
		l = l * 60;
		for (i = 1; i <= n; i++) {
			scanf("%d %d", w + i, v + i);
			ver = v[i];
			step = dp[i - 1] + (l / ver);
			for (j = i - 1, r = b - w[i]; j >= 1 && r >= w[j]; r -= w[j--]) {
				if (ver > v[j]) ver = v[j];
				tmp = dp[j - 1] + (l / ver);
				if (step > tmp) step = tmp;
			}
			dp[i] = step;
		}
		printf("%.1f\n", dp[n]);
	}
	return 0;
}