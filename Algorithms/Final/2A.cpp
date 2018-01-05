#include <iostream>
#include <stdio.h>
#include <vector>
#include <queue>

using namespace std;

#define N 1001
#define M 100001

typedef struct near {
	int x, t;
	near(int a, int b) : x(a), t(b) {}
} NEAR;

vector< vector<NEAR> > container(N);
int		edge[M][3];
bool	visit[N];
int		tag[N];
int		n, m;

void init() {
	for (int i = 0; i < n; i++)
		visit[i] = true;
}

int check() {
	for (int i = 0; i < n; i++)
		if (visit[i])
			return i;
	return -1;
}

void bfs() {
	int s, i, len, lenL, x;
	for (s = check(); s != -1; s = check()) {
		queue<int> level;
		level.push(s);
		tag[s] = 1;
		for (len = level.size(); len; len = level.size()) {
			for (; len; len--) {
				s = level.front();
				visit[s] = false;
				lenL = container[s].size();
				for (i = 0; i < lenL; i++) {
					x = container[s][i].x;
					if (visit[x]) {
						level.push(x);
						if (container[s][i].t == 0)
							tag[x] = tag[s];
						else
							tag[x] = !tag[s];
					}
				}
				container[s].clear();
				level.pop();
			}
		}
	}
}

int main() {
	int i, x, y, t;
	for (; scanf("%d %d", &n, &m) != EOF;) {
		init();
		for (i = 0; i < m; i++) {
			scanf("%d %d %d", &x, &y, &t);
			edge[i][0] = x;
			edge[i][1] = y;
			edge[i][2] = t;
			container[x].push_back(NEAR(y, t));
			container[y].push_back(NEAR(x, t));
		}
		bfs();
		for (i = 0; i < m; i++) {
			x = edge[i][0];
			y = edge[i][1];
			t = edge[i][2];
			if (t) {
				if (tag[x] == tag[y])
					break;
			}
			else {
				if (tag[x] != tag[y])
					break;
			}
		}
		if (i == m)
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}
