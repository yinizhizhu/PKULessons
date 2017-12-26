#include "tree.h"

bool cmpItem(ITEM& a, ITEM& b) {
	if (a.counter == b.counter)
		return a.item < b.item;
	return a.counter > b.counter;
}

bool cmpNode(PNODE a, PNODE b) {
	if (a->item.counter == b->item.counter)
		return a->item.item < b->item.item;
	return a->item.counter > b->item.counter;
}

bool cmpStr(string& a, string& b) {
	return a > b;
}

bool cmpContent(CONTENT& a, CONTENT& b) {
	if (a.year.size() == b.year.size()) {
		int i, len = a.year.size();
		for (i = 0; i < len; i++) {
			if (a.year[i] == b.year[i])
				continue;
			return a.year[i] > b.year[i];
		}
	}
	return a.year.size() > b.year.size();
}

bool cmpPair(PAIR& a, PAIR& b) {
	if (a[2] == b[2])
		return a[0] < b[0];
	return a[2] > b[2];
}

FPTree::FPTree() {
	root = new NODE();
	threshold = 3;
}

FPTree::~FPTree() {
	//cout << "In free..." << endl;
	delNode(root);
	//cout << "Out free..." << endl;
}

void FPTree::task1() {
	typedef vector<string> YEAR;

	typedef unordered_map<string, YEAR> A1;
	typedef A1::iterator A1_ITER;

	typedef unordered_map<string, A1> task_a1;
	typedef task_a1::iterator TASK_A1_ITER;

	YEAR tmp;
	reader r;
	int i, j, n, len;

	task_a1	t_a1;
	A1_ITER inner;
	TASK_A1_ITER outer;
	for (; r.readTrans();) {
		outer = t_a1.find(r.conference);
		if (outer != t_a1.end()) {
			len = r.authors.size();
			for (i = 0; i < len; i++) {
				inner = outer->second.find(r.authors[i]);
				if (inner == outer->second.end()) {
					tmp.clear();
					tmp.push_back(r.year);
					outer->second[r.authors[i]] = tmp;
				}
				else
					inner->second.push_back(r.year);
			}
		}
		else {
			A1 a;
			tmp.clear();
			tmp.push_back(r.year);
			len = r.authors.size();
			for (i = 0; i < len; i++)
				a[r.authors[i]] = tmp;
			t_a1[r.conference] = a;
		}
	}

	for (outer = t_a1.begin(); outer != t_a1.end(); outer++) {
		string conf = outer->first;
		vector<CONTENT> mid;
		for (inner = outer->second.begin(); inner != outer->second.end(); inner++) {
			string author = inner->first;
			CONTENT c(author, inner->second);
			sort(c.year.begin(), c.year.end(), cmpStr);
			mid.push_back(c);
		}
		sort(mid.begin(), mid.end(), cmpContent);
		task[conf] = mid;
	}

	ofstream out("task1.txt");
	for (TASK_ITER titer = task.begin(); titer != task.end(); titer++) {
		len = titer->second.size();
		out << titer->first << ": \n";
		for (i = 0; i < len; i++) {
			n = titer->second[i].year.size() - 1;
			out << "	" << n + 1 << "-" << titer->second[i].author << ": ";
			for (j = 0; j < n; j++)
				out << titer->second[i].year[j] << " ";
			out << titer->second[i].year[j] << endl;
		}
	}
	out.close();
}

void FPTree::task2() {
	reader r;
	int i, j, len, n;
	string a;
	vector<string> line;
	vector<vector<string>>	container;
	vector<string>	con, titles, years;
	while (r.readTrans()) {
		len = r.authors.size();
		for (i = 0; i < len; i++) {
			a = r.authors[i];
			addStr(a);
			line.push_back(a);
		}
		con.push_back(r.conference);
		titles.push_back(r.title);
		years.push_back(r.year);
		container.push_back(line);
		line.clear();
	}

	vector<ITEM> fre;
	n = container.size();
	for (i = 0; i < n; i++) {
		len = container[i].size();
		for (j = 0; j < len; j++) {
			a = container[i][j];
			if (dict[a] >= threshold)
				fre.push_back(ITEM(dict[a], a));
		}
		if (fre.size() >= 3) {
			sort(fre.begin(), fre.end(), cmpItem);
			frequent.push_back(fre);
			//showFre(fre); //show the current transaction's frequent items
			insert(fre, con[i], titles[i], years[i]);
		}
		fre.clear();
	}
	addHeader();
	addLink();
	miningFre();
}

void FPTree::addStr(string& a) {
	ITER iter = dict.find(a);
	if (iter == dict.end())
		dict[a] = 1;
	else
		iter->second++;
}

void FPTree::addHeader() {
	ITER step = dict.begin();
	for (; step != dict.end(); step++) {
		if (step->second >= threshold) {
			PNODE tmp = new NODE(string(step->first), step->second);
			header.push_back(tmp);
		}
	}
	//showHeader(); //show thee header
	sort(header.begin(), header.end(), cmpNode);
	//showHeader(); //show the header
}

void FPTree::showFre(vector<ITEM>& fre) {
	int i = 0, len = fre.size() - 1;
	for (; i < len; i++)
		cout << fre[i].item << ": " << fre[i].counter << ", ";
	cout << fre[i].item << ": " << fre[i].counter << endl;
}

void FPTree::showHeader() {
	int i, len = header.size()-1;
	for (i = 0; i < len; i++)
		cout << header[i]->item.item << ": " << header[i]->item.counter << ", ";
	cout << header[i]->item.item << ": " << header[i]->item.counter << endl;
}

void FPTree::delNode(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			delNode(r->childs[i]);
		//cout << r->item.item << ": " << r->item.counter << endl;
		r->childs.clear();
		delete r;
		r = NULL;
	}
}

void FPTree::addLink() {
	int i, len = header.size();
	for (i = 0; i < len; i++) {
		//cout << "In addLink: "; //show add process
		target = header[i];
		addHeaderLink(root);
		//cout << ". Out addLink!" << endl; //show the process
		//showLink(header[i]); //show current node link
	}
}

void FPTree::addHeaderLink(PNODE r) {
	if (r) {
		if (r->item.item == target->item.item) {
			//cout << target->item.item << "-" << target->item.counter << "->"; //show r
			target->next = r;
			target = r;
			//cout << target->item.item << "-" << target->item.counter << " "; //show next r
		}
		int i = 0, len = r->childs.size();
		for (; i < len; i++)
			addHeaderLink(r->childs[i]);
	}
}

void FPTree::showLink(PNODE r) {
	while (r->next) {
		cout << r->item.item << ": " << r->item.counter << ", ";
		r = r->next;
	}
	cout << r->item.item << ": " << r->item.counter << endl;
}

bool FPTree::isLeaf(PNODE r) {
	if (r) {
		cout << "The PNODE is NULL!!!" << endl;
		return false;
	}
	if (r->childs.size()) return true;
	return false;
}

string FPTree::getCItem(PNODE r, int i) {
	return r->childs[i]->item.item;
}

int FPTree::getCCounter(PNODE r, int i) {
	return r->childs[i]->item.counter;
}

void FPTree::insert(vector<ITEM>& items, string& con, string& title, string& year) {
	string tmp;
	PNODE step = root;
	int i, j, len = items.size();
	for (i = 0; i < len; i++) {
		tmp = items[i].item;
		for (j = step->childs.size() - 1; j >= 0; j--) {
			if (getCItem(step, j) == tmp) {
				step = step->childs[j];
				step->item.counter++;
				break;
			}
		}
		if (j < 0) {
			PNODE newone = new NODE(tmp, 1);
			step->childs.push_back(newone);
			newone->pre = step;
			step = newone;
		}
	}
	PAIR cty;
	cty.push_back(con);
	cty.push_back(title);
	cty.push_back(year);
	step->con_title_year.push_back(cty);
	//cout << step->item.item << ": " << step->item.counter << endl;
}

void FPTree::firstS() {
	travel(root);
}

void FPTree::travel(PNODE r) {
	if (r) {
		int i = 0, len = r->childs.size();
		cout << r->item.item << ": " << r->item.counter << endl;
		for (; i < len; i++)
			travel(r->childs[i]);
	}
}

void FPTree::miningFre() {
	int i = header.size() - 1;
	
	//cout << "The frequent sub-tree: " << endl;//test
	string		item;
	T_Y			container;
	ofstream	out("frequent.txt");
	for (; i >= 0; i--) {
		/*
			get all the path from bottom to top
			then, I get all the combination
		*/
		miningSubFre(container, header[i]->next);

		item = header[i]->item.item;
		for (T_Y_ITER iter = container.begin(); iter != container.end(); iter++) {
			out << item << iter->first << ":\n";
			outT_Y(iter->second, out);
		}
		container.clear();
	}
	out.close();
}

void FPTree::outT_Y(vector<PNODE>& part, ofstream& out) {
	vector<PAIR> t_y;
	int i, n = part.size();
	for (i = 0; i < n; i++)
		deepT_Y(part[i], t_y);
	sort(t_y.begin(), t_y.end(), cmpPair);
	n = t_y.size();
	for (i = 0; i < n; i++)
		out << "	" << t_y[i][0] << ", " << t_y[i][2] << ", " << t_y[i][1] << endl;
}

void FPTree::deepT_Y(PNODE r, vector<PAIR>& t_y) {
	int i, n = r->con_title_year.size();
	for (i = 0; i < n; i++) {
		PAIR cty;
		cty.push_back(r->con_title_year[i][0]);
		cty.push_back(r->con_title_year[i][1]);
		cty.push_back(r->con_title_year[i][2]);
		t_y.push_back(cty);
	}
	n = r->childs.size();
	for (i = 0; i < n; i++)
		deepT_Y(r->childs[i], t_y);
}

void FPTree::miningSubFre(T_Y& container, PNODE step) {
	//cout << "In subFre..." << endl;//test
	int			n;
	string		item;
	vector<string>	str;
	vector<PNODE>	backup, part;
	for (; step; step = step->next) {
		n = step->item.counter;
		if (n >= threshold) {
			//cout << n << endl;//test
			for (PNODE bottom = step->pre; bottom != root; bottom = bottom->pre) {
				item = bottom->item.item;
				str.push_back(item);
			}
			part.clear();
			part.push_back(step);
			miningStep(str, part, container);
		}
		else
			backup.push_back(step);
	}
	int j;
	vector<int>	visit;
	n = backup.size();
	visit.resize(n);
	//cout << "Backup size: " << n << endl; //test
	for (j = 0; j < n; j++)
		visit[j] = 1;
	for (j = 2; j <= n; j++)
		combinatePath(visit, backup, container, 0, j);
	//cout << "Out subFre!" << endl;//test
}

void FPTree::miningStep(vector<string>& str, vector<PNODE>& part, T_Y& container) {
	int j, n = str.size();
	if (n >= 2) {
		//showFreStr(str);
		string tmp = "";
		for (j = 0; j < n; j++)
			tmp += ", " + str[j];
		if (container.find(tmp) == container.end()) {
			vector<PNODE> tmpV;
			n = part.size();
			for (j = 0; j < n; j++)
				tmpV.push_back(part[j]);
			container[tmp] = tmpV;
		}
	}
	str.clear();
}

void FPTree::showFreStr(vector<string>& str) {
	for (int i = str.size() - 1; i >= 0; i--)
		cout << str[i] << " ";
	cout << endl;
}

void FPTree::combinatePath(vector<int>& visit, vector<PNODE>& backup, T_Y& container, int h, int n) {
	int len = backup.size();
	if (n <= 0) {
		string		item;
		item_int	store;
		vector<int>	index;
		vector<string>	str;
		vector<PNODE>	part;
		int	counter = 0, i, j;
		for (i = 0; i < len; i++)
			if (visit[i] == 0) {
				counter += backup[i]->item.counter;
				index.push_back(i);
				part.push_back(backup[i]);
			}
		if (counter >= threshold) {
			len = index.size();
			for (i = 0; i < len; i++) {
				j = index[i];
				counter = backup[i]->item.counter;
				for (PNODE bottom = backup[j]->pre; bottom != root; bottom = bottom->pre) {
					item = bottom->item.item;
					ITER iter = store.find(item);
					if (iter == store.end())
						store[item] = counter;
					else
						iter->second += counter;
				}
			}
			for (ITER iter = store.begin(); iter != store.end(); iter++)
				if (iter->second >= threshold) {
					item = iter->first;
					str.push_back(item);
				}
			miningStep(str, part, container);

		}
		return;
	}
	if (len - h < n) return;
	for (; h < len; h++) {
		if (visit[h]) {
			visit[h] = 0;
			combinatePath(visit, backup, container, h, n - 1);
			visit[h] = 1;
		}
	}
}
