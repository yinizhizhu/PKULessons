#include <iostream>
#include <stdio.h>

using namespace std;

#define N 5001

char str[N];
short dp[2][N];

int main() {
	int i, j, k, n, x;
	scanf("%d", &n);
	scanf("%s", str);
	for (i = 0; i < n; i++)
		dp[1][i] = 0;
	for (i = 0, j = 1, x = 0; j < n; i++, j++, x++) {
		if (str[i] == str[j])
			dp[0][x] = 0;
		else
			dp[0][x] = 1;
	}
	for (j = 2; j < n; j++) {
		for (i = 0, k = j, x = 0; k < n; i++, k++, x++) {
			if (str[i] == str[k])
				dp[0][x] = dp[1][x];
			else {
				if (dp[0][x] > dp[0][x + 1])
					dp[0][x] = dp[0][x + 1] + 1;
				else
					dp[0][x] = dp[0][x] + 1;
			}
			dp[1][x] = dp[0][x + 1];
		}
	}
	cout << dp[0][0] << endl;
	return 0;
}