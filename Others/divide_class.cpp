#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string.h>
#include <algorithm>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stack>

using namespace std;

typedef string STR;

typedef struct student {
    STR id, name, subject, kind;
    double grade;
    student(STR i, STR n, STR s, STR k, double g = 0.0) {
        id = i;
        name = n;
        subject = s;
        kind = k;
        grade = g;
    }
}STU;

bool cmp(STU& a, STU& b) {
    return a.grade > b.grade;
}

typedef unordered_map<STR, double>::iterator ITR;

class partion {
public:
    int n_class;
    unordered_map<STR, double> dict;
    vector<STU> s;
    vector<vector<STU> > container;
    partion();
    ~partion();
    void loadG();
    void loadS();
    void getA();
    void reverse(int k);
    void divider();
};

partion::partion() {
    n_class = 25;
//    container.resize(14);
}

partion::~partion() {}

void partion::loadG() {
    ifstream in("grade.txt");
    STR id, name, subject, n_class, n_credit;
    int counter = 0;
    double g;
    while (in>>id) {
        in>>name>>subject>>n_class>>n_credit;
        in>>g;
//        cout<<id<<", "<<name<<" "<<subject<<" "<<g<<endl;
        dict[id] = g;
        counter++;
    }
    cout<<counter<<endl;
    in.close();
}

void partion::loadS() {
    ifstream in("students.txt");
    STR id, name, subject, kind;
    int counter = 0;
    double g;
    while (in>>id) {
        in>>name>>subject>>kind;
//        cout<<id<<", "<<name<<" "<<subject<<" "<<kind<<endl;
        ITR iter = dict.find(id);
        if (iter == dict.end())
            g = 0.0;
        else
            g = iter->second;
        s.push_back(STU(id, name, subject, kind, g));
        counter++;
    }
    cout<<counter<<endl;
    sort(s.begin(), s.end(), cmp);
    in.close();

    cout<<s.size()<<endl;

    ofstream out("tmp.txt");
    for (int i = s.size()-1; i>=0; i--)
        out<<s[i].id<<" "<<s[i].grade<<'\n';
    out.close();
}

void partion::getA() {
    int i = 0, j, n = s.size();
    for (i=0, j=0; i<n; i++) {
        if (i%n_class == 0) {
            vector<STU> tmp;
            container.push_back(tmp);
        }
        container[j].push_back(s[i]);
        if (container[j].size() == n_class)
            j++;
    }

    ofstream out("array.txt");
    cout<<j<<endl;
    int counter = s.size();
    for (int k=0; k<=j; k++) {
        counter -= container[k].size();
        cout << container[k].size() <<", remain: "<<counter <<endl;
        if (k%2) reverse(k);
        for (i=0; i<container[k].size(); i++)
            out<<container[k][i].id<<","<<container[k][i].grade<<" ";
        out<<'\n';
    }
    out.close();
}

void partion::reverse(int k) {
    int n = container[k].size(), i;
    stack<STU> tmp;
    for (i=0; i<n; i++)
        tmp.push(container[k][i]);
    container[k].clear();
    for (; !tmp.empty(); tmp.pop())
        container[k].push_back(tmp.top());
}

void partion::divider() {
    char name[30];
    int i, j, n=container.size()-1;
    for (i=1; i<=n_class; i++) {
        sprintf(name, "out/%d.txt", i);
        cout<<"Inserting students into "<<name<<"..."<<endl;
        ofstream out(name);
        for (j=0; j<n; j++)
            out<<container[j][i-1].id<<"    "<<container[j][i-1].name<<"    "<<container[j][i-1].grade<<'\n';
        if (i<=container[j].size())
            out<<container[j][i-1].id<<"    "<<container[j][i-1].name<<"    "<<container[j][i-1].grade<<'\n';
        out.close();
    }
}

int main() {
    partion t;
    t.loadG();
    t.loadS();
    t.getA();
    t.divider();
    return 0;
}
