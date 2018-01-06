#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <string>
#include <algorithm>

using namespace std;

#define N 100001

int container[N];

int main() {
	int i, j, n, m, mid;
	int h = 0, t;
	scanf("%d %d", &n, &m);
	for (i = 0; i < n; i++) {
		scanf("%d", &j);
		if (h < j) h = j;
		container[i] = j;
	}
	t = h*n / m;
	while (h < t) {
		mid = (h + t) / 2;
		int step = mid - container[0];
		for (i = 1, j = m - 1; i < n; i++) {
			if (step >= container[i])
				step -= container[i];
			else {
				step = mid - container[i];
				j--;
			}
		}
		if (j >= 0) {
			t = mid;
		}
		else
			h = mid + 1;
	}
	printf("%d\n", t);
	return 0;
}