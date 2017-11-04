#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_LEE 2147483647
#define N 1001

int store[N], index[N];

int maxN(int a, int b) { return (a > b ? a : b); }

void longest(int h, int t) {
	int i, j, n = t - h, mid;
	if (n == 1) {
		index[h] = 1;
		return;
	}
	mid = h + n / 2;
	longest(h, mid);
	longest(mid, t);
	for (j = mid; j < t; j++) {
		n = index[j];
		for (i = h; i < j; i++)
			if (store[j] > store[i])
				n = maxN(n, index[i] + 1);
		index[j] = n;
	}
}

int main() {
	int i, n, ans = 1;
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", store + i);
	longest(0, n);
	for (i = 0; i < n; i++)
		if (index[i] > ans)
			ans = index[i];
	printf("%d\n", ans);
	return 0;
}

#include <iostream>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_LEE 2147483647
#define N 1001

int longest(int store[], int index[], int n) {
	int i, j, maxN, maxI;
	for (i = 1; i < n; i++) {
		maxN = index[i];
		maxI = i;
		for (j = i - 1; j >= 0; j--) {
			if (store[j] < store[i]) {
				if (index[j] >= maxN) {
					maxN = index[j];
					maxI = j;
				}
			}
		}
		if (maxI != i)
			index[i] = maxN + 1;
	}
	maxN = 1;
	for (i = 1; i < n; i++)
		if (index[i] > maxN)
			maxN = index[i];
	return maxN;
}

int main() {
	int i, n;
	int store[N], index[N];
	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", store + i);
	for (i = 0; i < n; i++)
		index[i] = 1;
	printf("%d\n", longest(store, index, n));
	return 0;
}
