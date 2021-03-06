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
    bool isBalanced(TreeNode* root) {
        if (!root) return true;
        int left = dfs(root->left);
        int right = dfs(root->right);
        return abs(left - right) <= 1 && isBalanced(root->left) &&
               isBalanced(root->right);
    }

    int dfs(TreeNode* root) {
        if (!root) return 0;
        int left = dfs(root->left);
        int right = dfs(root->right);
        return max(left, right) + 1;
    }
};