#include <iostream>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

#define N 1001

vector<int> container;
int store[N];
int n, ans;

void dp() {
	int i, j, tmp, step;
	for (i = 0; i < n; i++)
		store[i] = 1;
	ans = 1;
	for (i = 1; i < n; i++) {
		step = store[i];
		for (j = i - 1; j >= step - 1; j--)
			if (container[i] > container[j]) {
				tmp = store[j] + 1;
				if (tmp > step)
					step = tmp;
			}
		if (step > ans) ans = step;
		store[i] = step;
	}
}

int main() {
	int i, x;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &x);
		container.push_back(x);
	}
	dp();
	printf("%d\n", ans);
	return 0;
}