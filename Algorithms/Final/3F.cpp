#include <stdio.h>
#include <string.h>
#include <iostream>
#include <algorithm>

using namespace std;

#define N 101

int store[N][N];
int ans[N][N];

int max_lee(int a, int b) { return (a > b ? a : b); }

int dp(int f, int v) {
	int i, j;
	ans[0][0] = store[0][0];
	for (j = 1; j < v; j++)
		ans[0][j] = max_lee(store[0][j], ans[0][j - 1]);
	for (i = 1; i < f; i++) {
		ans[i][i] = ans[i - 1][i - 1] + store[i][i];
		for (j = i + 1; j < v; j++)
			ans[i][j] = max_lee(ans[i - 1][j - 1] + store[i][j], ans[i][j - 1]);
	}
	return ans[f - 1][v - 1];
}

int main() {
	int f, v, i, j;
	scanf("%d %d", &f, &v);
	for (i = 0; i < f; i++)
		for (j = 0; j < v; j++)
			scanf("%d", &store[i][j]);
	printf("%d\n", dp(f, v));
	return 0;
}