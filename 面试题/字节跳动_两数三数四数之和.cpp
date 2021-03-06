#include <bits/stdc++.h>

using namespace std;

/**
 * 两数三数四数之和
 */

class Solution {
   public:
    /**
     * 两数之和 nums是排序数组时
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     */
    vector<int> twoSum1(vector<int>& nums, int target) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int sum = nums[l] + nums[r];
            if (sum == target)
                return {l, r};
            else if (sum > target)
                r--;
            else
                l++;
        }
        return {-1, -1};
    }

    /**
     * 两数之和 nums是未排序的
     * 可以暴力，两层循环O(n^2),，用hash来优化
     * 时间复杂度：O(n)
     * 空间复杂度：O(n)
     */
    vector<int> twoSum2(vector<int>& nums, int target) {
        unordered_map<int, int> hash;
        int n = nums.size();
        for (int i = 0; i < n; i++) hash[nums[i]] = i;
        for (int i = 0; i < n; i++) {
            if (hash.count(target - nums[i]) && hash[target - nums[i]] != i) // 不能使用重复数字
                return {hash[target - nums[i]], i};
        }
        return {-1, -1};
    }

    /**
     * 三数之和
     * 排序 + 双指针
     * 时间复杂度：O(n^2)
     */
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> res;
        int n = nums.size();
        sort(nums.begin(), nums.end()); // 排序
        if (n < 3) return res;
        for (int i = 0; i < n - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue; // 去重
            int l = i + 1, r = n -1;
            while (l < r) {
                if (nums[l] + nums[r] > -nums[i]) r--;
                else if (nums[l] + nums[r] < -nums[i]) l++;
                else {
                    if (l == i + 1 || nums[l] != nums[l - 1]) // 去重
                        res.push_back({nums[l], nums[r], nums[i]});
                    l++, r--;
                }
            }
        }
        return res;
    }

    /**
     * 四数之和
     * 排序 + 双指针 + 去重
     * 时间复杂度：O(n^3)
     */
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        vector<vector<int>> res;
        int n = nums.size();
        if (n < 4) return res;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < n - 3; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) continue;
            for (int j = i + 1; j < n - 2; j++) {
                if (j == i + 1 || nums[j] != nums[j - 1]) {
                    int l = j + 1, r = n - 1;
                    while (l < r) {
                        int sum = nums[l] + nums[r] + nums[i] + nums[j];
                        if (sum > target) r--;
                        else if (sum < target) l++;
                        else {
                            if (l == j + 1 || nums[l] != nums[l - 1]) {
                                res.push_back({nums[l], nums[r], nums[i], nums[j]});
                            }
                            l++, r--;
                        }
                    }
                }
            }
        }
        return res;
    }
};