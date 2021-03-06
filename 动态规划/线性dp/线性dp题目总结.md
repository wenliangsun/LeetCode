# 线性dp题目总结

## 连续子数组的最大和(简单)

输入一个整型数组，数组里有正数也有负数。数组中的一个或连续多个整数组成一个子数组。求所有子数组的和的最大值。时间复杂度：$O(n)$[连续子数组的最大和](https://leetcode-cn.com/problems/lian-xu-zi-shu-zu-de-zui-da-he-lcof/)

### 参考代码

```c++
int maxSubArray(vector<int>& nums) {
    int n = nums.size();
    // 状态表示：dp[i] 表示以i为结尾的子数组的集合，其中的值表示子数组的最大和
    // 状态计算：dp[i] = max(dp[i-1], 0) + nums[i]
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) dp[i] = max(dp[i - 1], 0) + nums[i];
    int res = INT_MIN;
    for (int i = 1; i <= n; i++) res = max(res, dp[i]);
    return res;
}
/**
 * 优化版本，因为状态转移方程只与上一状态有关
 */
int maxSubArray(vector<int>& nums) {
    int last = 0, res = INT_MIN;
    for (auto n : nums) {
        int t = max(last, 0) + n;
        res = max(res, t);
        last = t;
    }
    return res;
}
```

## 使用最小花费爬楼梯(简单)

数组的每个索引作为一个阶梯，第 i个阶梯对应着一个非负数的体力花费值 cost(索引从0开始)。每当你爬上一个阶梯你都要花费对应的体力花费值，然后你可以选择继续爬一个阶梯或者爬两个阶梯。您需要找到达到楼层顶部的最低花费。在开始时，你可以选择从索引为 0 或 1 的元素作为初始阶梯。[使用最小花费爬楼梯](https://leetcode-cn.com/problems/min-cost-climbing-stairs/)

### 参考代码

```c++
int minCostClimbingStairs(vector<int>& cost) {
    // 状态表示：dp[i] 表示到达i层时花费的总和
    // 状态计算：dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]) 
    // 当前位置花费为从当年位置爬需要的花费和从前面当当前位置的花费之和
    vector<int> dp(cost.size());
    dp[0] = cost[0];
    dp[1] = cost[1];
    for (int i = 2; i < cost.size(); i++) {
        // cost[i] 表示从当前位置爬需要的花费，
        // min(dp[i-1], dp[i-2]) 表示到达当前位置需要的最小花费(可以跳一阶到达，也可以是跳两节到达)
        dp[i] = cost[i] + min(dp[i - 1], dp[i - 2]);
    }
    // 最后取倒数第一阶和倒数第二阶中的最小值，因为可以从倒数第二阶可以直接跳到最后
    return min(dp[cost.size() - 1], dp[cost.size() - 2]);
}

// 空间优化版
int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    if (n == 1) return cost[0];
    int a = cost[0], b = cost[1];
    for (int i = 2; i < n; i++) {
        int t = cost[i] + min(a, b);
        a = b, b = t;
    }
    return min(a, b);
}
```

## 比特位计数(中等)

给定一个非负整数 num。对于 0 ≤ i ≤ num 范围中的每个数字 i ，计算其二进制数中的 1 的数目并将它们作为数组返回。[比特位计数](https://leetcode-cn.com/problems/counting-bits/)

思路：动态规划+最低有效位，$P(x) = P(x/2) + (x mod 2)$。[参考题解](https://leetcode-cn.com/problems/counting-bits/solution/bi-te-wei-ji-shu-by-leetcode/)

### 参考代码

```c++
vector<int> countBits(int num) {
    vector<int> res(num + 1);
    for (int i = 1; i <= num; i++) {
        res[i] = res[i >> 1] + (i & 1); // 状态转移方程
    }
    return res;
}
// 朴素版本 时间复杂度O(nk)
vector<int> countBits(int num) {
    vector<int> res;
    for (int i = 0; i <= num; i++) {
        int n = i, cnt = 0;
        while (n) {
            cnt++;
            n = n & (n - 1);
        }
        res.push_back(cnt);
    }
    return res;
}
```

## 最大正方形(中等)

在一个由 0 和 1 组成的二维矩阵内，找到只包含 1 的最大正方形，并返回其面积。[最大正方形](https://leetcode-cn.com/problems/maximal-square/)

思路：动态规划：状态表示：`dp[i][j]` 表示以i，j结尾的矩形的最大边长， 状态计算：`dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1])) + 1`。[参考题解](https://leetcode-cn.com/problems/maximal-square/solution/li-jie-san-zhe-qu-zui-xiao-1-by-lzhlyle/)

### 参考代码

```c++
int maximalSquare(vector<vector<char>>& matrix) {
    if (!matrix.size() || !matrix[0].size()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    vector<vector<int>> dp(m, vector<int>(n));
    int len = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == '1') {
                if (!i || !j)
                    dp[i][j] = 1;
                else
                    dp[i][j] = min(dp[i - 1][j - 1],
                                    min(dp[i - 1][j], dp[i][j - 1])) +
                                1;
            }
            len = max(len, dp[i][j]);
        }
    }
    return len * len;
}
```

## 统计全为1的正方形子矩阵(中等)

给你一个 m * n 的矩阵，矩阵中的元素不是 0 就是 1，请你统计并返回其中完全由 1 组成的 正方形 子矩阵的个数。[统计全为 1 的正方形子矩阵](https://leetcode-cn.com/problems/count-square-submatrices-with-all-ones/)

思路：动态规划：状态表示：`dp[i][j]`以i，j结尾的正方形的数量；状态计算：`dp[i][j] = min(dp[i-1][j-1], min(dp[i - 1][j], dp[i][j-1])) + 1`

### 参考代码

```c++
int countSquares(vector<vector<int>>& matrix) {
    if (!matrix.size() || !matrix[0].size()) return 0;
    int m = matrix.size(), n = matrix[0].size();
    int res = 0; // 记录总的正方形数量
    vector<vector<int>> dp(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j]) {
                if (!i || !j)
                    dp[i][j] = 1;
                else
                    dp[i][j] = min(dp[i - 1][j - 1],
                                    min(dp[i - 1][j], dp[i][j - 1])) +
                                1;
                res += dp[i][j];
            }
        }
    }
    return res;
}
```

## 最小路径和(中等)

给定一个包含非负整数的 m x n 网格，请找出一条从左上角到右下角的路径，使得路径上的数字总和为最小。说明：每次只能向下或者向右移动一步。[最小路径和](https://leetcode-cn.com/problems/minimum-path-sum/)

### 参考代码

```c++
int minPathSum(vector<vector<int>>& grid) {
    if (!grid.size() || !grid[0].size()) return 0;
    int m = grid.size(), n = grid[0].size();
    // 状态表示：dp[i][j]表示到达位置i，j的最小路径和
    // 状态计算：dp[i][j] = min(dp[i-1][j], dp[i][j - 1]) + grid[i][j]
    vector<vector<int>> dp(m, vector<int>(n));
    dp[0][0] = grid[0][0]; // 注意这儿的base case
    for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + grid[i][0];
    for (int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + grid[0][j];
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
        }
    }
    return dp[m - 1][n - 1];
}
```

## 地下城游戏(困难)

一些恶魔抓住了公主（P）并将她关在了地下城的右下角。地下城是由 M x N 个房间组成的二维网格。我们英勇的骑士（K）最初被安置在左上角的房间里，他必须穿过地下城并通过对抗恶魔来拯救公主。骑士的初始健康点数为一个正整数。如果他的健康点数在某一时刻降至 0 或以下，他会立即死亡。有些房间由恶魔守卫，因此骑士在进入这些房间时会失去健康点数（若房间里的值为负整数，则表示骑士将损失健康点数）；其他房间要么是空的（房间里的值为 0），要么包含增加骑士健康点数的魔法球（若房间里的值为正整数，则表示骑士将增加健康点数）。为了尽快到达公主，骑士决定每次只向右或向下移动一步。[地下城游戏](https://leetcode-cn.com/problems/dungeon-game/)

思路：从右下到左上状态转移。状态表示：dp[i][j]表示位置i，j到达终点需要的最小初始量；状态计算：dp[i][j] = max(min(dp[i+1][j], dp[i][j+1])- dungeon[i][j], 1)，当前状态只与dp[i+1][j]和dp[i][j+1]的最小值有关，且需要满足当前位置i，j的初始值达到min-dungeon[i][j], 并保证初始值要大于1。

### 参考代码

```c++
int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = dungeon.size(), n = dungeon[0].size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    dp[m][n - 1] = dp[m - 1][n] = 1; // 边界初始化为1
    for (int i = m - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            dp[i][j] =
                max(min(dp[i + 1][j], dp[i][j + 1]) - dungeon[i][j], 1);
        }
    }
    return dp[0][0];
}
```

## 三角形最小路径和(中等)

给定一个三角形，找出自顶向下的最小路径和。每一步只能移动到下一行中相邻的结点上。[三角形最小路径和](https://leetcode-cn.com/problems/triangle/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 用滚动数组优化空间复杂度
     * 考虑到之和上一层的数组有关，只用2层的数组，即所有的i坐标模2,或者&1两个等价
     * 空间复杂度：O(n)
     */
    int minimumTotal(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<long long>> dp(2, vector<long long>(n));
        dp[0][0] = g[0][0];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                dp[i & 1][j] = INT_MAX;
                if (j > 0)
                    dp[i & 1][j] =
                        min(dp[i & 1][j], dp[i - 1 & 1][j - 1] + g[i][j]);
                if (j < i)
                    dp[i & 1][j] =
                        min(dp[i & 1][j], dp[i - 1 & 1][j] + g[i][j]);
            }
        }
        long long res = INT_MAX;
        for (int i = 0; i < n; i++) res = min(res, dp[n - 1 & 1][i]);
        return res;
    }

    /**
     * 状态表示 ：dp[i][j]
     * 表示到达第i层上第j个结点的所有路径集合，其值表示这些路径集合中的最小值
     * 状态计算 ：分为从左上来的和右上来的  左上来的是 dp[i][j] = min(dp[i][j],
     * dp[i-1][j-1]+g[i][j]) 右上来的是 dp[i][j] = min(dp[i][j], dp[i - 1][j] +
     * g[i][j])
     *
     * 空间复杂度：O(n^2)
     */
    int minimumTotal(vector<vector<int>>& g) {
        int n = g.size();
        vector<vector<long long>> dp(n, vector<long long>(n));
        dp[0][0] = g[0][0];
        for (int i = 1; i < n; i++) {
            for (int j = 0; j <= i; j++) {
                dp[i][j] = INT_MAX;  // 初始化最大
                // 左上来的
                if (j > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + g[i][j]);
                // 右上来的
                if (j < i) dp[i][j] = min(dp[i][j], dp[i - 1][j] + g[i][j]);
            }
        }
        long long res = INT_MAX;
        // 遍历一遍，求最小
        for (int i = 0; i < n; i++) {
            res = min(res, dp[n - 1][i]);
        }
        return res;
    }
};
```

## 两个字符串的最小ASCII删除和(中等)

给定两个字符串s1, s2，找到使两个字符串相等所需删除字符的ASCII值的最小和。[两个字符串的最小ASCII删除和](https://leetcode-cn.com/problems/minimum-ascii-delete-sum-for-two-strings/)

思路：和最短编辑距离思路一样。状态表示：`dp[i][j]`表示s1的前i个字母和s2的前j个字母中需要删除的最小和；状态计算：`dp[i][j] = min(dp[i - 1][j - 1] + s1[i - 1] + s2[j - 1], min(dp[i - 1][j] + s1[i - 1], dp[i][j - 1] + s2[j - 1]))`。

### 参考代码

```c++
int minimumDeleteSum(string s1, string s2) {
    int m = s1.size(), n = s2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1));
    for (int i = 1; i <= m; i++) dp[i][0] = dp[i - 1][0] + s1[i - 1]; // 边界情况
    for (int j = 1; j <= n; j++) dp[0][j] = dp[0][j - 1] + s2[j - 1];
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) // 字符相等的情况
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = min(dp[i - 1][j - 1] + s1[i - 1] + s2[j - 1],
                                min(dp[i - 1][j] + s1[i - 1],
                                    dp[i][j - 1] + s2[j - 1]));
        }
    }
    return dp[m][n];
}
```

## 最短编辑距离(困难)

给你两个单词 word1 和 word2，请你计算出将 word1 转换成 word2 所使用的最少操作数 。你可以对一个单词进行如下三种操作： 插入一个字符 删除一个字符 替换一个字符[最短编辑距离](https://leetcode-cn.com/problems/edit-distance/)

### 参考代码

```c++
class Solution {
   public:
   /**
    * 状态表示：dp[i][j]表示w1中前i个字符和w2中前j个字符的最短编辑距离
    * 状态计算：如果不相等的时候，三种情况取最小
    */
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 0; i <= m; i++) dp[i][0] = i;
        for (int j = 0; j <= n; j++) dp[0][j] = j;
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (word1[i - 1] == word2[j - 1])
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1])) + 1;
            }
        }
        return dp[m][n];
    }
};
```

## 最低票价(中等)

在一个火车旅行很受欢迎的国度，你提前一年计划了一些火车旅行。在接下来的一年里，你要旅行的日子将以一个名为 days 的数组给出。每一项是一个从 1 到 365 的整数。火车票有三种不同的销售方式：一张为期一天的通行证售价为 costs[0] 美元；一张为期七天的通行证售价为 costs[1] 美元；一张为期三十天的通行证售价为 costs[2] 美元。通行证允许数天无限制的旅行。 例如，如果我们在第 2 天获得一张为期 7 天的通行证，那么我们可以连着旅行 7 天：第 2 天、第 3 天、第 4 天、第 5 天、第 6 天、第 7 天和第 8 天。返回你想要完成在给定的列表 days 中列出的每一天的旅行所需要的最低消费。[最低票价](https://leetcode-cn.com/problems/minimum-cost-for-tickets/)

思路：从前向后计算。状态表示：dp[i]表示到第i天所用的最小花费；状态计算：`dp[i] = min(dp[i-1] + costs[0], dp[i-7] + costs[1], dp[i-30] + costs[2])` 当第i天是需要出行的时候，否则`dp[i] = dp[i-1]`。[参考题解](https://leetcode-cn.com/problems/minimum-cost-for-tickets/solution/zui-di-piao-jie-by-leetcode-solution/)

### 参考代码

```c++
int mincostTickets(vector<int>& days, vector<int>& costs) {
    int n = days.size();
    int last = days[n - 1]; // 出行的最后一天
    vector<int> dp(last + 1); // 状态数组
    int idx = 0;
    for (int i = 1; i <= last; i++) {
        if (i == days[idx]) { // 当前天需要出行
            int cst = INT_MAX;
            int t1 = i - 1;
            int t7 = i - 7 > 0 ? i - 7 : 0;
            int t30 = i - 30 > 0 ? i - 30 : 0;
            cst = min(dp[t1] + costs[0], cst);
            cst = min(dp[t7] + costs[1], cst);
            cst = min(dp[t30] + costs[2], cst);
            dp[i] = cst;
            idx++;
        } else // 不需要出行
            dp[i] = dp[i - 1];
    }
    return dp[last];
}
```

## 等差数列划分(中等)

如果一个数列至少有三个元素，并且任意两个相邻元素之差相同，则称该数列为等差数列。[等差数列划分](https://leetcode-cn.com/problems/arithmetic-slices/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 思路：暴力法
     * 先计算相邻两个元素之间的差，然后枚举区间起点和枚举区间终点，判断区间内是不是等差数列即可
     * 时间复杂度：O(n^3)
     */
    int numberOfArithmeticSlices(vector<int>& A) {
        int cnt = 0, n = A.size();
        for (int s = 0; s < n - 2; s++) {      // 枚举起点
            int d = A[s + 1] - A[s];           // 计算等差
            for (int e = s + 2; e < n; e++) {  // 枚举终点
                int k = 0;
                for (k = s + 1; k <= e; k++) {  // 判断区间是不是等差数列
                    if (A[k] - A[k - 1] != d) break;
                }
                if (k > e) cnt++;  // 区间是等差数列的话，计数+1
            }
        }
        return cnt;
    }

    /**
     * 优化的暴力
     * 时间复杂度：O(n^2)
     */
    int numberOfArithmeticSlices(vector<int>& A) {
        int cnt = 0, n = A.size();
        for (int s = 0; s < n - 2; s++) {  // 枚举区间起点
            int d = A[s + 1] - A[s];
            for (int e = s + 2; e < n; e++) {  // 枚举区间终点
                if (A[e] - A[e - 1] == d)      // 判断是否等差
                    cnt++;
                else
                    break;
            }
        }
        return cnt;
    }

    /**
     * 动态规划
     * 状态表示：dp[i]表示以i结尾的等差数列的子数组个数
     * 状态计算：dp[i] = 1 + dp[i-1]
     */
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size();
        int sum = 0;
        vector<int> dp(A.size());
        for (int i = 2; i < n; i++) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                dp[i] = 1 + dp[i - 1];
                sum += dp[i];
            }
        }
        return sum;
    }
    // 状态压缩
    int numberOfArithmeticSlices(vector<int>& A) {
        int n = A.size(), sum = 0, dp = 0;
        for (int i = 2; i < n; i++) {
            if (A[i] - A[i - 1] == A[i - 1] - A[i - 2]) {
                dp = 1 + dp;
                sum += dp;
            } else
                dp = 0;
        }
        return sum;
    }
};
```

## 不同路径(中等)

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。问总共有多少条不同的路径？[不同路径](https://leetcode-cn.com/problems/unique-paths/)

思路：状态表示：`dp[i][j]`表示到达i，j位置的方案数；状态计算：`dp[i][j] = dp[i - 1][j] + dp[i][j-1]`。

### 参考代码

```c++
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!i || !j)
                dp[i][j] = 1;
            else
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
        }
    }
    return dp[m - 1][n - 1];
}
```

## 不同路径II(中等)

一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为“Start” ）。机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为“Finish”）。现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？[不同路径II](https://leetcode-cn.com/problems/unique-paths-ii/)

### 参考代码

```c++
int uniquePathsWithObstacles(vector<vector<int>>& g) {
    int n = g.size(), m = g[0].size();
    vector<vector<long long>> dp(n, vector<long long>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j]) continue;                // 障碍
            if (!i && !j) dp[i][j] = 1;           // 起点
            if (i > 0) dp[i][j] += dp[i - 1][j];  // 左边来的
            if (j > 0) dp[i][j] += dp[i][j - 1];  // 右边来的
        }
    }
    return dp[n - 1][m - 1];
}
```

## 回文子串(中等)

给定一个字符串，你的任务是计算这个字符串中有多少个回文子串。具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被计为是不同的子串。[回文子串](https://leetcode-cn.com/problems/palindromic-substrings/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 中心扩展法
     * 枚举每一个可能的中心位置，长度为n的字符串，有2*n-1个中心，然后向两边扩展
     */
    int countSubstrings(string s) {
        int n = s.size(), res = 0;
        for (int i = 0; i < 2 * n - 1; i++) {
            int l = i / 2, r = l + i % 2;  // 注意这儿求中心位置的方法
            while (l >= 0 && r < n && s[l] == s[r]) {
                res++, r--, l++;
            }
        }
        return res;
    }
    /**
     * 动态规划
     * 状态表示：dp[i][j]表示字符串i到j的子串是否是回文串
     * 状态计算：见代码
     */
    int countSubstrings(string s) {
        int res = 0, n = s.size();
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int j = 0; j < n; j++) {
            dp[j][j] = true;
            res++;
            for (int i = 0; i < j; i++) {
                dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i + 1][j - 1]);
                if (dp[i][j]) res++;
            }
        }
        return res;
    }
};
```

## 下降路径最小和(中等)

给定一个方形整数数组 A，我们想要得到通过 A 的下降路径的最小和。下降路径可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列。[下降路径最小和](https://leetcode-cn.com/problems/minimum-falling-path-sum/)

思路：和三角形最小路径和类似，这个可称为正方形最小路径和。状态表示：`dp[i][j]`到达表示第i层第j列的路径最小和；状态计算：`dp[i][j] = min(dp[i - 1][j - 1], dp[i-1][j], dp[i-1][j+1]) + A[i][j]`。时间复杂度：$O(n^2)$，空间复杂度：$O(n^2)$。

### 参考代码

```c++
int INF = 10000; 
int minFallingPathSum(vector<vector<int>>& A) {
    int n = A.size();
    vector<vector<int>> dp(n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) dp[0][i] = A[0][i];
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dp[i][j] = min(dp[i][j], dp[i - 1][j] + A[i][j]);
            if (j > 0) dp[i][j] = min(dp[i][j], dp[i - 1][j - 1] + A[i][j]);
            if (j < n - 1) dp[i][j] = min(dp[i][j], dp[i - 1][j + 1] + A[i][j]);
        }
    }
    int res = INT_MAX;
    for (int i = 0; i < n; i++) res = min(res, dp[n - 1][i]);
    return res;
}
```

## 最长公共子序列(中等)

给定两个字符串 text1 和 text2，返回这两个字符串的最长公共子序列的长度。一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。两个字符串的「公共子序列」是这两个字符串所共同拥有的子序列。若这两个字符串没有公共子序列，则返回 0。[最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 状态表示：dp[i][j]表示text1的前i个字符和text2的前j个字符中所有子序列的集合，值为子序列的最大长度。
     * 状态计算：见代码
     */
    int longestCommonSubsequence(string text1, string text2) {
        int m = text1.size(), n = text2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (text1[i - 1] == text2[j - 1])  // 当前字符相等时
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else  // 当前字符不相等时
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
        return dp[m][n];
    }
};
```

## 完全平方数(中等)

给定正整数 n，找到若干个完全平方数（比如 1, 4, 9, 16, ...）使得它们的和等于 n。你需要让组成和的完全平方数的个数最少。[完全平方数](https://leetcode-cn.com/problems/perfect-squares/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 状态表示：dp[i]表示组成数i需要的最少完全平方数的数量
     * 状态计算：dp[i] = min(dp[i], dp[i-j*j]+1) 1<j*j<i
     */
    int numSquares(int n) {
        vector<int> dp(n + 1);
        for (int i = 1; i <= n; i++) {
            dp[i] = i;  // 用1凑是最长的
            for (int j = 1; j * j <= i; j++) { // 枚举尝试更换平方数
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }
        return dp[n];
    }
};
```

## 最长回文子序列(中等)

给定一个字符串 s ，找到其中最长的回文子序列，并返回该序列的长度。可以假设 s 的最大长度为 1000 。[最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 状态表示：dp[i][j]表示区间i，j中最长回文子序列,最终答案是dp[0][n-1],所以起点需要倒着遍历
     * 状态计算：见代码
     */
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = n - 1; i >= 0; i--) {  // 枚举区间起点，需要倒着遍历
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {  // 枚举区间终点
                if (s[i] == s[j])              // 如果两端字符相等
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                else  // 如果两端字符不相等，则说不他两不能同时出现在序列中
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
        return dp[0][n - 1];
    }
};
```

## 整数拆分或剪绳子(中等)

给定一个正整数 n，将其拆分为至少两个正整数的和，并使这些整数的乘积最大化。 返回你可以获得的最大乘积。[整数拆分](https://leetcode-cn.com/problems/integer-break/)

思路：遍历当前剪的长度，剩余部分可以选择不剪，也可以选择剪(递归)，取最大情况。当数据量很大的时候，通过数学推导，将绳子尽可能的剪成长度为3时可以获得最大乘积，考虑最后剩余的绳子长度(1,2)[参考题解](https://leetcode-cn.com/problems/jian-sheng-zi-ii-lcof/solution/mian-shi-ti-14-ii-jian-sheng-zi-iitan-xin-er-fen-f/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 暴力：遍历当前剪的长度，剩余部分可以选择不剪，也可以选择剪(递归)，取最大情况
     */
    int integerBreak(int n) {
        int res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(res, max(i * (n - i), i * integerBreak(n - i)));
        }
        return res;
    }

    /**
     * 备忘录
     */
    int integerBreak(int n) {
        vector<int> memo(n + 1);
        return dfs(n, memo);
    }

    int dfs(int n, vector<int>& memo) {
        if (n == 2) return 1;
        if (memo[n]) return memo[n];
        int res = 0;
        for (int i = 1; i <= n; i++) {
            res = max(res, max(i * (n - i), i * dfs(n - i, memo)));
        }
        memo[n] = res;
        return res;
    }

    /**
     * 动态规划
     * 状态表示：dp[i]表示长度为i的绳子的获得的最大乘积
     * 状态计算：dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]))
     */
    int integerBreak(int n) {
        vector<int> dp(n + 1);
        dp[2] = 1;
        for (int i = 3; i <= n; i++) {
            for (int j = 1; j < i; j++) {
                dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
            }
        }
        return dp[n];
    }
    /**
     * 当绳子长度很大的时候
     */
    int integerBreak(int n) {
        if (n <= 3) return n - 1;
        int a = n / 3, b = n % 3, mod = 1e9;
        int res = qmi(3, a - 1, mod);  // 可以被3整除的绳子（a-1）最大乘积
        if (b == 0) return res * 3 % mod; // 剩余长度为0直接乘以余出来的3
        if (b == 1) return res * 4 % mod; // 剩余长度为1时，和前面余出来的长度为3的剪成2*2的
        return res * 6 % mod; // 剩余长度为2，则乘以余出来的3。2*3
    }
    // 快速幂
    int qmi(int m, int k, int p) {
        int res = 1 % p, t = m;
        while (k) {
            if (k & 1) res = res * t % p;
            k >>= 1;
            t = t * t % p;
        }
        return res;
    }
};
```

## 最长增长子序列(中等)

给定一个无序的整数数组，找到其中最长上升子序列的长度。[最长上升子序列](https://leetcode-cn.com/problems/longest-increasing-subsequence/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 思路：二分查找法
     * 利用扑克牌的一种玩法，给定一把牌，我们只能把点数小的压在点数大的上面，(可用二分法找应该放置的堆)
     * 如果当前牌的点数较大且没有可以放置的堆，则新建一个堆，把这张牌放上去。
     * 如果当前牌有多个堆可供选择，则放置在最左侧的堆。
     * 最终牌的堆数就是最长递增子序列的长度。
     * 时间复杂度：O(nlogn)
     */
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp(nums.size());
        int len = 0;
        for (int i = 0; i < nums.size(); i++) {
            int l = 0, r = len;
            while (l < r) {
                int mid = l + r >> 1;
                if (dp[mid] >= nums[i])
                    r = mid;
                else
                    l = mid + 1;
            }
            if (l == len) len++;
            dp[l] = nums[i];
        }
        return len;
    }

    /**
     * 状态表示：dp[i] 表示以i为终点的上升子序列的集合  其中的值表示长度的最大值
     * 状态计算：dp[i] = dp[j]+1 当nums[j]<nums[i]的时候
     *
     * 时间复杂度：O(n^2)
     */
    int lengthOfLIS1(vector<int>& nums) {
        vector<int> dp(nums.size());
        for (int i = 0; i < nums.size(); i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i]) dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        int res = 0;
        for (int i = 0; i < nums.size(); i++) res = max(res, dp[i]);
        return res;
    }

    /**
     * 输出最长增长子序列，输出任意一个
     * 反向寻找
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(n)
     */
    vector<int> lengthOfLIS2(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n), pos(n);
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            pos[i] = i;
            for (int j = 0; j < i; j++) {
                if (nums[j] < nums[i] && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    pos[i] = j;
                }
            }
        }
        int len = 0, p = 0; // 找最大位置
        for (int i = 0; i < n; i++) {
            if (dp[i] > len) {
                len = dp[i];
                p = i;
            }
        }
        vector<int> res(len);
        int idx = len - 1; // 反向寻找
        while (pos[p] != p || idx >= 0) {
            res[idx--] = nums[p];
            p = pos[p];
        }
        return res;
    }

    /**
     * 输出字典序最小的最长增长子序列
     * 堆纸牌的方法，用一个数组记录每一个数字放在哪一堆上
     * 然后从后向前遍历数组去寻找每一堆上的数字
     * 时间复杂度：O(nlogn)
     * 空间复杂度：O(n)
     */
    vector<int> lengthOfLIS3(vector<int>& nums) {
        int n = nums.size();
        vector<int> dp(n), pos(n);
        int len = 0;
        for (int i = 0; i < n; i ++) {
            int l = 0, r = len;
            while (l < r) {
                int mid = (l + r) >> 1;
                if (dp[mid] >= nums[i]) r = mid;
                else l = mid + 1;
            }
            if (l == len) len++;
            dp[l] = nums[i];
            pos[i] = l; // 记录当前数字放在第几堆上
        }
        vector<int> res(len, INT_MAX); // 答案数组
        int idx = len - 1; // 答案数组的索引
        for (int i = n - 1; i >= 0; i--) {
            if (pos[i] == idx) { // 如果索引相同，则说明该数字是答案数组中当前位置的数字。
                res[idx] = min(res[idx], nums[i]);
                idx--;
            }
        }
        return res;
    }
};
```

## 交错字符串(困难)

给定三个字符串 s1, s2, s3, 验证 s3 是否是由 s1 和 s2 交错组成的。[交错字符串](https://leetcode-cn.com/problems/interleaving-string/)

### 参考代码

```c++
class Solution {
public:
    /**
     * 动态规划
     * 状态表示：dp[i][j]表示s1的前i个字符和s2的前j个字符能否组成s3的前i+j个字符
     * 状态计算：根据s3的最后一个字符是s1提供还是s2提供，分两种情况：
     *        (1)s3的最后一个字符来自s1的情况：dp[i][j] = dp[i][j] || (dp[i - 1][j]&&s1[i - 1] == s3[i + j - 1]);
     *        (2)s3的最后一个字符来自s2的情况：dp[i][j] = dp[i][j] || (dp[i - 1][j]&&s2[j - 1] == s3[i + j - 1])
     */
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size()) return false; // 如果长度不匹配，直接返回false
        vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
        dp[0][0] = true; // base case
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j <= n; j++) {
                int idx = i + j - 1;
                if (i > 0) dp[i][j] = dp[i][j] || (dp[i - 1][j] && s1[i - 1] == s3[idx]);
                if (j > 0) dp[i][j] = dp[i][j] || (dp[i][j - 1] && s2[j - 1] == s3[idx]);
            }
        }
        return dp[m][n];
    }
};
```

## 最长对数链(中等)

给出 n 个数对。 在每一个数对中，第一个数字总是比第二个数字小。现在，我们定义一种跟随关系，当且仅当 b < c 时，数对(c, d) 才可以跟在 (a, b) 后面。我们用这种形式来构造一个数对链。给定一个对数集合，找出能够形成的最长数对链的长度。你不需要用到所有的数对，你**可以以任何顺序**选择其中的一些数对来构造。[最长数对链](https://leetcode-cn.com/problems/maximum-length-of-pair-chain/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 套了个壳子的最长增长子序列
     * 状态表示：dp[i]表示以i位置结尾的子序列，值为最大长度
     * 状态计算：dp[i] = max(dp[i], dp[j] + 1) pairs[j] < pairs[i]
     * 时间复杂度：O(n^2 + nlogn)
     */
    int findLongestChain(vector<vector<int>>& pairs) {
        int n = pairs.size();
        sort(pairs.begin(), pairs.end());
        vector<int> dp(n);
        for (int i = 0; i < n; i++) {
            dp[i] = 1;
            for (int j = 0; j < i; j++) {
                if (pairs[j][1] < pairs[i][0]) dp[i] = max(dp[i], dp[j] + 1);
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++) res = max(res, dp[i]);
        return res;
    }
};
```

## 最长重复子数组(中等)

给两个整数数组 A 和 B ，返回两个数组中公共的、长度最长的子数组的长度。[最长重复子数组](https://leetcode-cn.com/problems/maximum-length-of-repeated-subarray/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 其实就是最长公共子串问题
     * 状态表示： dp[i][j] 表示以A的第i个元素和B的第j个元素的结尾的的子数组，其值表示子数组的最长长度
     * 状态计算：如果A[i]==B[j]则dp[i][j] = dp[i-1][j-1] + 1, 否则，dp[i][j] = 0;
     */
    int findLength(vector<int>& A, vector<int>& B) {
        int m = A.size(), n = B.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++)
                if (A[i - 1] == B[j - 1])
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                else
                    dp[i][j] = 0;
        int res = 0;
        // 寻找最大长度的子数组
        for (int i = 1; i <= m; i++)
            for (int j = 1; j <= n; j++) res = max(res, dp[i][j]);
        return res;
    }
};
```

## 单词拆分(中等)

给定一个非空字符串 s 和一个包含非空单词列表的字典 wordDict，判定 s 是否可以被空格拆分为一个或多个在字典中出现的单词。[单词拆分](https://leetcode-cn.com/problems/word-break/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 动态规划
     * 状态表示：dp[i]表示字符串前i个字符能否由单词表中的单词表示
     * 状态计算：dp[i] = true 如果前i个字符中从后面拆出来一个单词表中的单词，
     * 并且剩余的字符串dp[i-len(单词)]可以用单词表中单词表示时。
     * 时间复杂度：O(n^2)
     */
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> hash;
        for (auto d : wordDict) hash.insert(d);
        int n = s.size();
        vector<bool> dp(n + 1);
        dp[0] = true;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                if (dp[j] && hash.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp[n];
    }
};
```

## 摆动排序(中等)

如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为摆动序列。第一个差（如果存在的话）可能是正数或负数。少于两个元素的序列也是摆动序列。例如， [1,7,4,9,2,5] 是一个摆动序列，因为差值 (6,-3,5,-7,3) 是正负交替出现的。相反, [1,4,7,2,5] 和 [1,7,4,5,5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，第二个序列是因为它的最后一个差值为零。给定一个整数序列，返回作为摆动序列的最长子序列的长度。 通过从原始序列中删除一些（也可以不删除）元素来获得子序列，剩下的元素保持其原始顺序。[摆动排序](https://leetcode-cn.com/problems/wiggle-subsequence/)

### 参考代码

```c++
class Solution {
public:
    /**
     * 动态规划：
     * up[i]表示以i为结尾的且上升的摆动序列的长度
     * down[i]表示以i为结尾的且下降的摆动序列的长度
     * 类似最长增长子序列的更新方式
     * 时间复杂度：O(n^2)
     * 空间复杂度：O(n)
     */
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        vector<int> up(n), down(n);
        for (int i = 0; i < n; i++) {
            up[i] = 1, down[i] = 1;
            for (int j = 0; j < i; j++) {
                if (nums[i] > nums[j]) up[i] = max(up[i], down[j] + 1);
                else if (nums[i] < nums[j]) down[i] = max(down[i], up[j] + 1);
            }
        }
        return max(up[n - 1], down[n - 1]);
    }

    /**
     * 考虑up一定是从down(除初始状态)中产生的，并且此时的down是最大的.
     * 假设down[i]表示的最远末尾元素下标刚好是i，则up[i+1] = down[i] + 1;
     * 假设down[i]表示的最远末尾元素下标小于i，记为j，则i到j之间一定是递增的，因为如果有递减，
     * 则down[i]表示的最远末尾元素就不是j了。所以down[j:i]一直都是down[j]，所以此时依然满足up[i+1] = down[i]+1.
     * 其余情况类似。注意到down和up只和前一个状态有关，所以我们可以优化存储，分别用一个变量即可。
     * 时间复杂度：O(n)
     * 空间复杂度：O(1)
     */
    int wiggleMaxLength(vector<int>& nums) {
        int n = nums.size();
        if (n < 2) return n;
        int up = 1, down = 1;
        for (int i = 1; i < n; i++) {
            if (nums[i] < nums[i - 1]) down = up + 1;
            else if (nums[i] > nums[i - 1]) up = down + 1;
        }
        return max(up, down);
    }
};
```