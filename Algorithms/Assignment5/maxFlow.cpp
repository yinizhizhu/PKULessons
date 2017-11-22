#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int N = 1100;
const int INF = 0x3f3f3f3f;

struct node {
	/*
	for node, three arguments for computing
	index - store the index of starting node of the edge of the graph in vector
	des	- store the destination node in the graph
	cap - capacity of the edge
	*/
	int index, des, cap;
	node(int i, int d, int c) : index(i), des(d), cap(c) {}
};

int m, n;
vector<node> v[N];
bool used[N];

int minLee(int a, int b) {
	return (a > b ? b : a);
}

void addNode(int from, int to, int cap) {
	v[from].push_back(node(v[to].size(), to, cap));
	v[to].push_back(node(v[from].size() - 1, from, 0));
}

int bfs(int s, int t, int f) {
	if (s == t)	return f;
	used[s] = true;
	for (int i = 0; i < v[s].size(); i++) {
		node& tmp = v[s][i];
		if (used[tmp.des] == false && tmp.cap > 0) {
			int d = bfs(tmp.des, t, minLee(f, tmp.cap));
			if (d > 0) {
				tmp.cap -= d;
				v[tmp.des][tmp.index].cap += d;
				return d;
			}
		}
	}
	return 0;
}

int maxFlow() {
	int flow = 0;
	for (;;) {
		for (int i = 0; i < n; i++) used[i] = false;
		int f = bfs(0, n - 1, INF);
		if (f == 0) break;
		flow += f;
	}
	return flow;
}

void init() {
	/*
	The text file which stores the graph gives the number of node of graph: n, while m which is number of edges is given.
	Then, the next m lines indicate the m edges.
	Each line follows three number with formation:
		s t c
		s - start point of the edge
		t - end point of the edge
		c - the capacity of the edge: zero indicating this edge is not existing in this graph
	*/
	ifstream in("in.txt");
	int s, t, c;
	in >> n >> m;
	for (; m; m--) {
		in >> s >> t >> c;
		addNode(s, t, c);
	}
	in.close();
}

int main() {
	init();
	cout << INF << endl;
	cout << maxFlow() << endl;
	return 0;
}