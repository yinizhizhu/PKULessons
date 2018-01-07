#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <limits.h>
#include <unordered_map>

using namespace std;

#define N 101

int container[N], dp[N][N];

int main() {
	int i, j, k, l, n, tmp;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", container + i);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++) {
			if (fabs(i - j) < 2)
				dp[i][j] = 0;
			else dp[i][j] = INT_MAX;
		}
	for (l = 3; l <= n; l++) {
		for (i = 0; i <= n - l; i++) {
			j = i + l - 1;
			for (k = i + 1; k < j; k++) {
				tmp = dp[i][k] + dp[k][j] + container[i] * container[k] * container[j];
				if (tmp < dp[i][j])
					dp[i][j] = tmp;
			}
		}
	}
	printf("%d\n", dp[0][n - 1]);
	return 0;
}