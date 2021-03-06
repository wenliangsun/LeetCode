#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
   public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (!head) return nullptr;
        auto dummy = new ListNode(-1);
        dummy->next = head;
        auto pre = dummy;
        auto cur = head;
        for (int i = 0; i < n; i++) cur = cur->next;
        while (cur) {
            pre = pre->next;
            cur = cur->next;
        }
        pre->next = pre->next->next;
        return dummy->next;
    }
};