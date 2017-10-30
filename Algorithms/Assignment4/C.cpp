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
