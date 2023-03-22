/*

Good morning!

This is your coding interview problem for today.

This problem was asked by Fitbit.

Given a linked list, rearrange the node values such that they appear in alternating low -> high -> low -> high ... form. 
For example, given 1 -> 2 -> 3 -> 4 -> 5, you should return 1 -> 3 -> 2 -> 5 -> 4.

We will be sending the solution tomorrow, along with tomorrow's question. As always, feel free to shoot us an email if there's anything we can help with.

Have a great day!

*/

#include <bits/stdc++.h>
using namespace std;


struct List {
    int value;
    List* next;
    List(int value_) : value(value_), next(nullptr) {}
    List(int value_, List* next_) : value(value_), next(next_) {}
    void print() {
        List* p = this; 
        while (p != nullptr) {
            cout << p->value;
            if (p->next != nullptr) {
                cout << " -> ";
            }
            p = p->next;
        }
        cout << endl;
    }
};

List* Example1() {
    int len = 5;
    List* list = new List(len);
    for (int value = len-1; value >= 1; value--) {
        list = new List(value, list);
    }
    return list;
}

List* Example2() {    
    vector<int> values;
    values.assign(10,0);
    iota(values.begin(), values.end(), 1);
    for (int i=0; i<values.size(); i++) {
        int r1 = rand()%values.size();
        int r2 = rand()%values.size();
        int t = values[r1];
        values[r1] = values[r2];
        values[r2] = t;        
    }
    List* list = new List(values[0]);
    for (int i=1; i < values.size(); i++) {
        list = new List(values[i], list);
    }
    return list;
}


// For example, given 1 -> 2 -> 3 -> 4 -> 5, you should return 1 -> 3 -> 2 -> 5 -> 4.

List* Swap(List* list) {
    if (list == nullptr) {     
        return nullptr;
    }
    if (list->next == nullptr) {        
        return list;
    }
    if (list->next->next == nullptr) {    
        List* tmp = list->next;
        list->next = nullptr;
        tmp->next = list;
        return tmp;
    } else {        
        List* rest = Swap(list->next->next);
        List* tmp = list->next;
        list->next = rest;
        tmp->next = list;
        return tmp;
    }
}

List* SwapTail(List* list) {
    list->next = Swap(list->next);
    return list;
}


List* bsort(List* l) {
    cout << "BSORT::"; l->print(); cout<< endl;
    if (l==nullptr) return l;
    if (l->next == nullptr) return l;
    l->next = bsort(l->next);
    cout << "HEAD:" << l->value << " BSORTED REST:";l->next->print(); cout << endl;
    List* head = l;
    bool isHead = true;
    // now the rest is sorted
    while (l->next != nullptr && l->next->value < l->value) {
        List* tmp = l->next;                
        l->next = tmp->next;
        tmp->next = l;
        //l = l->next;        
        if (isHead) {
            head=tmp;
            isHead = false;
        }
    }
    cout << "BSORTED*** "; head->print(); cout << endl;
    return head;
}

int main() {
    List* ex1 = Example1();
    ex1->print();
    // ex1 is already sorted juhee
    SwapTail(ex1)->print();
    List* ex2 = Example2();
    ex2->print();
    ex2 = bsort(ex2);
    ex2->print();
    return 0;
}
