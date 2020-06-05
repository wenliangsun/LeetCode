#include <bits/stdc++.h>

using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
   public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        if (!root) return res;
        queue<TreeNode*> q;
        q.push(root);
        bool d = false; // 方向
        while (q.size()) {
            vector<int> t;
            int len = q.size();
            for (int i = 0; i < len; i++) {
                auto node = q.front();
                q.pop();
                t.push_back(node->val);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            if (d) reverse(t.begin(), t.end());
            res.push_back(t);
            d = !d;
        }
        return res;
    }
};