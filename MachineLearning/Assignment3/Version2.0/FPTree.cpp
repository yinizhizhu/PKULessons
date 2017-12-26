#include "tree.h"

void show(vector<string>& line) {
	int i, len = line.size() - 1;
	for (i = 0; i < len; i++)
		cout << line[i] << " ";
	cout << line[i] << endl;
}

int visit[4];
void combinate(vector<string>& container, int i, int n) {
	if (n <= 0) {
		for (int i = 0; i < 3; i++) {
			if (visit[i] == 0)
				cout << container[i];
		}
		cout << endl;
		return; 
	}
	for (; i < 3; i++) {
		if (visit[i]) {
			visit[i] = 0;
			combinate(container, i, n - 1);
			visit[i] = 1;
		}
	}
}

void demoCombinate() {
	vector<string> container;
	container.push_back("a");
	container.push_back("b");
	container.push_back("c");
	for (int i = 0; i < 3; i++) visit[i] = 1;
	combinate(container, 0, 2);
}

int main() {
	FPTree tree;
	tree.task1();
	tree.task2();
    return 0;
}
