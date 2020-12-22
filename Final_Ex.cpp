#include<iostream>
using namespace std;

struct Sach {
    string maSach;
    string tenSach;
    int soTo;
};

istream& operator >> (istream& is, Sach& p) {
    is >> p.maSach >> p.tenSach >> p.soTo;
    return is;
}

ostream& operator << (ostream& os, Sach p) {
    os << p.maSach << "-" << p.tenSach << "-" << p.soTo << endl;
    return os;
}

struct Node {
    Sach value;
    Node* next;
};

struct List {
    Node* pFrist;
    Node* pLast;
};

Node* getNode(Sach c) {
    Node* p = new Node;
    p->value = c;
    p->next = NULL;
    return p;
}

void initList(List& l) {
    l.pFrist = l.pLast = NULL;
}

void addHead(List& l, Node* p) {
    if (l.pFrist == NULL) {
        l.pFrist = l.pLast = p;
    }
    else {
        p->next = l.pFrist;
        l.pFrist = p;
    }
}

void addNode(List& l, Node* p) {
    if (l.pFrist == NULL) {
        l.pFrist = l.pLast = p;
    }
    else {
        l.pLast->next = p;
        l.pLast = p;
    }
}

void printList(List l) {
    Node* p = l.pFrist;
    while (p != NULL) {
        cout << p->value;
        p = p->next;
    }
    cout << endl;
}

void sapXep(Sach& a, Sach& b) {
    Sach c = a;
    a = b;
    b = c;
}

int main() {
    List l;
    initList(l);
    int sl, idx, tong = 0;
    cin >> sl >> idx;
    Sach t;

    for (int i = 0; i < sl; i++) {
        cin >> t;
        addNode(l, getNode(t));
        tong += t.soTo;
    }
    Node* p = l.pFrist;
    Node* last = NULL;
    int i = 0;
    while (p != NULL) {
        if (i == idx) {
            if (p == l.pFrist) {
                Node* t = p;
                l.pFrist = p->next;
                delete t;
            }
            else if (p == l.pLast) {
                Node* t = p;
                l.pLast = last;
                l.pLast->next = NULL;
                delete t;
            }
            else {
                Node* t = p;
                last->next = p->next;
                delete t;
                p = p->next;
                i++;
                continue;
            }
        }
        i++;
        last = p;
        p = p->next;
    }
    cout << tong << endl;
    printList(l);

    return 0;
}
