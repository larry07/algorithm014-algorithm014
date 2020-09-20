学习笔记

## Week6

动态规划和递归或者分治，没有根本上的区别（**关键看有无最优子结构**）

**共性：找到重复子问题**

差异性：最优子结构，中途可以**淘汰**次优解

斐波那契的傻递归（指数级）每一层分叉为两支，所以是O(2^n)

```c++
return n<=1?n:fib(n-1)+fib(n-2);
```

可以优化为 =>多项式级别

带缓存，记忆化搜索  ,自底向上构建`memo[n]`,在后面需要某个`fib(n)`时，不用计算，分支就被砍掉了

```c++
//right clean code:
if(n<=1)
    return n;
if(memo[n]==0)
    memo[n]=fib[n-1]+fib[n-2];
return memo[n];
```

动态规划 关键点   

1 最优子结构 `opt[n] = best_of(opt[n-1],opt[n-2],...)   `

2 存储中间状态：`opt[ i ]   `

3 递推公式Fib： `opt[i]=opt[n-1]+opt[n-2]`

​    二维路径：`opt[ i , j ] = opt[i+1][j]+opt[i][j+1] `且判断是否空地

​	1 打破自己的思维习惯，形成机器思维

​	2 理解复杂逻辑的关键

​	3 也是职业逻辑的关键

人为的去想，如果没有找到关键点的话，就是无章可循的，没有**自相似性**，只是直觉是不行的，要有据可依，

#### 最大连续子数组之和

小优化：必然从正数开始，正数结尾，如果全负数，只能有最小的一个了

a. DP  最大子序和=当前元素自身最大，或包含之前  后最大

b.状态数组定义` f[i]`

c.递推DP方程  `max_sum(i)=max(max_sum(i-1),0)+a[i];`

```c++
int maxSubArray(vector<int>& nums) {
    //dp[i]:以[i]结尾的最大值
    if(nums.empty())return 0;
    int n = nums.size();
    if(n==1)return nums[0];

    vector<int> dp(n,0);
    dp[0]=nums[0];
    int res =dp[0];
    for(int i=1;i<n;i++){
        dp[i]=max(dp[i-1],0)+nums[i];
        res = max(res,dp[i]);
    }
    return res;
}
```



#### 乘积最大子序列

主要是要保存乘积最正的和最负的，因为下一步都可能达到最大值

```c++
int maxProduct(vector<int>& nums) {
	int down=1,up=1,res=INT_MIN;
	int n = nums.size();
	for(int i=0;i<n;i++){
		down = down*nums[i];
		up   = up*nums[i];

		if(down>up)swap(down,up);
		down = min(down,nums[i]);
		up   = max(up,nums[i]);
		res=max(res,up);
	}
	return res;
}
```



#### 零钱兑换

题目有很多变换，是理解的基石，可以组成思维逻辑的框架

- 如果不问最少需要多少硬币，而是多少种，题目就变成了爬楼梯问题

状态树->子问题（爬楼梯爬一次后，求剩余楼梯的爬法）树的层次即为爬的次数，问题变成了在状态数里找到状态为0的节点，且层次最低/深度最小的, BFS，最早发现状态0的节点，其深度就是多少个硬币

DP: 联想斐波那契数列 上一二三阶时，`f(n)=f(n-1)+f(n-2)+f(n-3)`

这里`f(n)=min{f(n-k),k in [1 2 5]}+1` ，多少钱就是多少级台阶，可看官方题解

```c++
int coinChange(vector<int>& coins, int amount) {
    int Max = amount + 1;         //MAX 不能INT_MAX +1溢出
    vector<int> dp(amount + 1, Max);
    dp[0] = 0;                    //!!后面要+1的,起始点/导火索
    for (int i = 1; i <= amount; ++i) {
        for (int j = 0; j < (int)coins.size(); ++j) {
            if (coins[j] <= i)    //下标有效性
                dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        }
    }
    return dp[amount] > amount ? -1 : dp[amount];
}
```

如上解法不能用`INT_MAX`，也可用下面这种方法，当然有点繁琐

```c++
if (dp[j] - 1 > dp[j - coins[i - 1]]) // 把 1 移动到左边，避免溢出
    dp[j] = 1 + dp[j - coins[i - 1]];
```

递归解法

```c++
int coinChange(vector<int>& coins, int amount) {
    int res = INT_MAX, n = coins.size();
    sort(coins.begin(), coins.end(), greater<int>()); //逆序
    helper(coins, 0, amount, 0, res);
    return (res == INT_MAX) ? -1 : res;
}
void helper(vector<int>& coins, int start, int target, int cur, int& res) {//0, amount, 0,
    if (start >= coins.size()) return;
    if (target % coins[start] == 0){
        // 能整除的话肯定不用再递归了, 因为coins已从大到小排好序
        res = min(res, cur + target / coins[start]);
        return;
    }
    for (int i = target / coins[start]; i >= 0; --i) {
        if (cur + i >= res - 1) break;
        helper(coins, start + 1, target - i * coins[start], cur + i, res);
    }
}
```

:fire:加油！:eyes:  ，这周困难题很多没做，我尽快补。。。我可不想又自己半途而废，成为一个只喊口号、没有行动的庸人！