#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <queue>
#include <algorithm>

using namespace std;

#define N 21

typedef pair<int, int> P;
char maze[N][N];
int m, n;

bool check(int x, int y) {
	if (x < 0 || x >= m) return false;
	if (y < 0 || y >= n) return false;
	if (maze[x][y] == '#') return false;
	return true;
}

int bfs(int x, int y) {
	queue<P> level;
	level.push(P(x, y));
	int len, step = 0;
	for (len = level.size(); len; len = level.size()) {
		for (; len; len--) {
			P tmp = level.front();
			x = tmp.first;
			y = tmp.second;
			if (maze[x][y] == '*')
				return step;
			maze[x][y] = '#';
			if (check(x + 1, y))
				level.push(P(x + 1, y));
			if (check(x - 1, y))
				level.push(P(x - 1, y));
			if (check(x, y + 1))
				level.push(P(x, y + 1));
			if (check(x, y - 1))
				level.push(P(x, y - 1));
			level.pop();
		}
		step++;
	}
	return -1;
}

int main() {
	char c;
	int i, j, x, y;
	for (cin >> m >> n; m; cin >> m >> n) {
		for (i = 0; i < m; i++) {
			for (j = 0; j < n; j++) {
				cin >> c;
				maze[i][j] = c;
				if (c == '@') {
					x = i;
					y = j;
				}
			}
		}
		printf("%d\n", bfs(x, y));
	}
	return 0;
}