#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>

using namespace std;

#define N 21

struct iqd {
	priority_queue<int> L;
	priority_queue<int, vector<int>, greater<int>> R;
	void insert(int a) {
		int lenL = L.size(), lenR = R.size();
		if (lenR) {
			int topR = R.top();
			if (lenL >= lenR) {
				int topL = L.top();
				if (a >= topL)
					R.push(a);
				else {
					L.pop();
					L.push(a);
					R.push(topL);
				}
			}
			else {
				if (a < topR)
					L.push(a);
				else {
					R.pop();
					R.push(a);
					L.push(topR);
				}
			}
		}
		else R.push(a);
	}
	int query() {
		int lenL = L.size(), lenR = R.size();
		if (lenL == lenR)
			return L.top();
		else
			return R.top();
	}
	void del() {
		int lenL = L.size(), lenR = R.size();
		if (lenL == lenR)
			L.pop();
		else
			R.pop();
	}
};

int main() {
	int t, n, num;
	char op;
	scanf("%d", &t);
	for (; t; t--) {
		iqd step;
		scanf("%d", &n);
		for (; n; n--) {
			op = getchar();
			scanf("%c", &op);
			if (op == 'I') {
				scanf("%d", &num);
				step.insert(num);
			}
			else if (op == 'Q')
				printf("%d\n", step.query());
			else
				step.del();
		}
	}
	return 0;
}