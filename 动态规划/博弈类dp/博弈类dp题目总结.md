# 博弈类dp题目总结

## 除数博弈

爱丽丝和鲍勃一起玩游戏，他们轮流行动。爱丽丝先手开局。最初，黑板上有一个数字 N 。在每个玩家的回合，玩家需要执行以下操作：选出任一 x，满足 0 < x < N 且 N % x == 0 。用 N - x 替换黑板上的数字 N 。如果玩家无法执行这些操作，就会输掉游戏。只有在爱丽丝在游戏中取得胜利时才返回 True，否则返回 false。假设两个玩家都以最佳状态参与游戏。[除数博弈](https://leetcode-cn.com/problems/divisor-game/)

### 参考代码

```c++
bool divisorGame(int N) {
    if (N == 1) return false;
    if (N == 2) return true;
    vector<bool> dp(N + 1); // dp[i] 表示面对数字i当前玩家的输赢情况
    dp[2] = true;
    for (int i = 3; i <= N; i++) { //枚举玩家面临的数字
        for (int x = 1; x < i; x++) { // 当前玩家需要选一个满足要求的数字，而且选完之后确保下一轮dp[i-x]玩家输的情况。
            if (!(i % x) && !dp[i - x]) {
                dp[i] = true; //则我就会赢
                break;
            }
        }
    }
    return dp[N];
}

/**
 * 归纳法，遇奇则输，遇偶则赢
 */
bool divisorGame(int N) {
    if (N & 1) return false;
    return true;
}
```

## 石子游戏(中等)

亚历克斯和李用几堆石子在做游戏。偶数堆石子排成一行，每堆都有正整数颗石子 piles[i] 。游戏以谁手中的石子最多来决出胜负。石子的总数是奇数，所以没有平局。亚历克斯和李轮流进行，亚历克斯先开始。 每回合，玩家从行的开始或结束处取走整堆石头。 这种情况一直持续到没有更多的石子堆为止，此时手中石子最多的玩家获胜。假设亚历克斯和李都发挥出最佳水平，当亚历克斯赢得比赛时返回 true ，当李赢得比赛时返回 false 。[石子游戏](https://leetcode-cn.com/problems/stone-game/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * Min-Max
     * 博弈类问题
     * 时间复杂度：O(2^n)
     */
    bool stoneGame(vector<int>& piles) {
        return score(piles, 0, piles.size() - 1) > 0;
    }
    // 相对分数 会超时！
    int score(vector<int>& piles, int l, int r) {
        if (l == r) return piles[l];  // 只剩一堆，直接拿走
        // 先手拿左堆和拿右堆中相对分数大的一种情况
        return max(piles[l] - score(piles, l + 1, r),
                   piles[r] - score(piles, l, r - 1));
    }

    // 记忆化搜索 时间复杂度：O(n^2)
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> memo(n, vector<int>(n)); // 记忆数组
        return score(piles, 0, n - 1, memo) > 0;
    }

    int score(vector<int>& piles, int l, int r, vector<vector<int>>& memo) {
        if (l == r) return piles[l];
        if (memo[l][r]) return memo[l][r];
        int res = max(piles[l] - score(piles, l + 1, r, memo),
                   piles[r] - score(piles, l, r - 1, memo));
        memo[l][r] = res;
        return res;
    }

    /**
     * 动态规划
     * 状态表示：dp[i][j]表示i，j区间我可以获得的最大相对分数
     * 状态计算：需要斜着遍历数组
     */
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i ++) dp[i][i] = piles[i];
        for (int l = 2; l <= n; l++) {
            // 斜着遍历数组
            for (int i = 0; i < n - l + 1; i++) { // x坐标
                int j = i + l - 1; // y坐标
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j]- dp[i][j - 1]);
            }
        }
        return dp[0][n - 1] > 0;
    }

    // 空间优化
    bool stoneGame(vector<int>& piles) {
        int n = piles.size();
        vector<int> dp(n);
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                dp[i] = max(piles[i] - dp[i + 1], piles[i + l - 1] - dp[i]);
            }
        }
        return dp[0] > 0;
    }

    // 题目给了偶数堆的条件，则先手必赢
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};
```

## 石子游戏II(中等)

亚历克斯和李继续他们的石子游戏。许多堆石子 排成一行，每堆都有正整数颗石子 piles[i]。游戏以谁手中的石子最多来决出胜负。亚历克斯和李轮流进行，亚历克斯先开始。最初，M = 1。在每个玩家的回合中，该玩家可以拿走剩下的 前 X 堆的所有石子，其中 1 <= X <= 2M。然后，令 M = max(M, X)。游戏一直持续到所有石子都被拿走。假设亚历克斯和李都发挥出最佳水平，返回亚历克斯可以得到的最大数量的石头。[石子游戏II](https://leetcode-cn.com/problems/stone-game-ii/)

### 参考代码

```c++
class Solution {
   public:
    int stoneGameII(vector<int>& piles) {
        int n = piles.size();
        vector<vector<int>> memo(n, vector<int>(n + 1));
        int s = score(piles, 0, 1, memo);
        int total = accumulate(piles.begin(), piles.end(), 0);
        return (total + s) / 2;
    }

    int score(vector<int>& piles, int s, int m, vector<vector<int>>& memo) {
        int n = piles.size();
        if (s >= n) return 0;
        m = min(m, n);
        if (memo[s][m]) return memo[s][m];
        if (s + 2 * m >= n)
            return accumulate(piles.begin() + s, piles.end(), 0);
        int res = INT_MIN, cur = 0;
        for (int x = 1; x <= 2 * m; x++) {
            cur += piles[s + x - 1];
            res = max(res, cur - score(piles, s + x, max(x, m), memo));
        }
        memo[s][m] = res;
        return res;
    }
};
```

## 预测赢家(中等)

给定一个表示分数的非负整数数组。 玩家1从数组任意一端拿取一个分数，随后玩家2继续从剩余数组任意一端拿取分数，然后玩家1拿，……。每次一个玩家只能拿取一个分数，分数被拿取之后不再可取。直到没有剩余分数可取时游戏结束。最终获得分数总和最多的玩家获胜。给定一个表示分数的数组，预测玩家1是否会成为赢家。你可以假设每个玩家的玩法都会使他的分数最大化。[预测赢家](https://leetcode-cn.com/problems/predict-the-winner/)

### 参考代码

```c++
class Solution {
   public:
    /**
     * 石子游戏的普通版
     * MiN-Max法
     * 时间复杂度2^n
     */
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        return score(nums, 0, n - 1) >= 0;
    }
    // 暴力递归
    int score(vector<int>& nums, int l, int r) {
        if (l == r) return nums[l];
        return max(nums[l] - score(nums, l + 1, r),
                   nums[r] - score(nums, l, r - 1));
    }

    // 记忆化搜索 时间复杂度O(n^2)
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> memo(n, vector<int>(n));
        return score(nums, 0, n - 1, memo) >= 0;
    }

    int score(vector<int>& nums, int l, int r, vector<vector<int>>& memo) {
        if (l == r) return nums[l];
        if (memo[l][r]) return memo[l][r];
        int res = max(nums[l] - score(nums, l + 1, r, memo),
                      nums[r] - score(nums, l, r - 1, memo));
        memo[l][r] = res;
        return res;
    }
    /**
     * 动态规划
     * 状态表示：dp[i][j]表示i，j区间我可以获得的最大相对分数
     * 状态计算：需要斜着遍历数组
     */
    bool PredictTheWinner(vector<int>& nums) {
        int n = nums.size();
        vector<vector<int>> dp(n, vector<int>(n));
        for (int i = 0; i < n; i++) dp[i][i] = nums[i];
        for (int l = 2; l <= n; l++) {
            for (int i = 0; i < n - l + 1; i++) {
                int j = i + l - 1;
                dp[i][j] = max(nums[i] - dp[i + 1][j], nums[j] - dp[i][j - 1]);
            }
        }
        return dp[0][n - 1] >= 0;
    }
};
```
