#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <fstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

const int N = 30;
const int INF = 0x3f3f3f3f;

typedef unordered_map<string, int> map;
typedef map::iterator iter;

int n;
map store;
bool visit[N];
double graph[N][N];

void init(int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		visit[i] = false;
		for (j = 0; j < n; j++)
			graph[i][j] = 0;
	}
}

int getI(string& str) {
	iter tmp = store.find(str);
	if (tmp == store.end())
		return -1;
	return tmp->second;
}

bool check(int counter, int s, int pre, double get) {
	if ((s == pre && counter < n) || counter == 0) {
		if (get > 1) return true;
		return false;
	}
	for (int i = 0; i < n; i++) {
		if (!visit[i] && graph[i] > 0) {
			visit[i] = true;
			if (check(counter - 1, s, i, get*graph[pre][i]))
				return true;
			visit[i] = false;
		}
	}
	return false;
}

int main() {
	int i, m, x, y, c = 1;
	bool ans;
	double rate;
	string cur1, cur2;
	while (cin >> n && n) {
		for (i = 0; i < n; i++) {
			cin >> cur1;
			store[cur1] = i;
		}

		init(n);

		cin >> m;
		for (i = 0; i < m; i++) {
			cin >> cur1 >> rate >> cur2;
			x = getI(cur1);
			y = getI(cur2);
			graph[x][y] = rate;
		}
		for (i = 0; i < n; i++) {
			ans = check(n, i, i, 1);
			if (ans) break;
		}
		cout << "Case " << c;
		if (ans)
			cout << ": Yes" << endl;
		else
			cout << ": No" << endl;
		c++;
	}
	return 0;
}