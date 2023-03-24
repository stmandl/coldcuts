/*
You are given the head of a singly linked-list. The list can be represented as:

L0 → L1 → … → Ln - 1 → Ln
Reorder the list to be on the following form:

L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
You may not modify the values in the list's nodes. Only nodes themselves may be changed.
*/
/**
 * Definition for singly-linked list.
 * 
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

#include<bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};



inline ListNode* reverse(ListNode* head) {
    if (head == nullptr) return head;
    ListNode* prev = nullptr;
    ListNode* tmp;
    while (head != nullptr) {
        tmp = head->next;
        head->next = prev;
        prev = head;
        head = tmp;
    }
    //head->next = prev;
    return prev;
}

class Solution {
public:
    void reorderList(ListNode* head) {
        if (head == nullptr || head->next == nullptr)
            return;
        ListNode* slow=head;
        ListNode* fast=head;
        while (fast != nullptr && fast->next != nullptr) {
            slow=slow->next;
            fast=fast->next->next;
        }
        // slow now points to the middle
        ListNode* head2 = reverse(slow->next);
        slow->next = nullptr;
        while (head != nullptr && head2 != nullptr) {
            ListNode* tmpN = head->next;
            head->next = head2;
            ListNode* tmpN2 = head2->next;
            head2->next = tmpN;
            head = tmpN;
            head2 = tmpN2;
        }
        if (head2 != nullptr) {
            head->next = head2;
        }

    }
};


ostream& operator<<(ostream& os, ListNode* l) {
    if (l == nullptr) {
        os << ".";
        return os;
    }
    os << l->val << ", " << l->next;
    return os;
}

ListNode* make_list(vector<int> v) {
    ListNode dummy;
    ListNode* current = &dummy;
    for (auto i : v) {
        current->next = new ListNode(i);
        current = current->next;
    }
    current->next = nullptr;
    return dummy.next;
}

int main() {
    ListNode* l1 = make_list({1,2,3,4,5});
    //cout << "l1: " << l1 << endl;
    //cout << "rl1: " << reverse(l1) << endl;
    Solution().reorderList(l1);
    cout << l1;

}