# Week9

学期快要结束了，还要继续加油！:eyes: :fire:



## 动态规划；递归（自己调用自己）、分治、回溯

一个问题的不同方面

感触

1. 人肉递归低效，很累

2. 找到最近最简方法，将其拆解为可重复解决的问题

   `最近重复性，就像两个数的最大公约数，最接近上一层`

3. 数学归纳法思维

   ```
   反人类。
   人的思维习惯，在现实中希望把每一个步骤自己都能看到和把控住，不然心里面会没底。
   对于『递归管好本层，制度兼顾衔接下层，最后整个体系就是完美的』，人类不适合于这样的思想。
   	但是当你要处理复杂的问题，或者在复杂度公司里工作，或者在复杂的社会中工作，都是要用这样的一种管理方式——即同理可得，以此类推的方式。
   ```

**本质都是寻找重复性->计算机指令集(for,while,递归调用)**，复杂的面试题，也是在10~20行就能解决的，关键是自己的代码功底和提炼重复性，同一个题，没有提炼出重复性，没有善用API，就可能写的又臭又长。。。

分治如果可以去重/淘汰次优解的话，就变成了动态规划	

​		动态规划：  分治+最优子结构

**关键点**：动规和递归/分治没有根本区别（关键看有无最优子结构），拥有共性：找到重复子问题

**差异性**：最优子结构、中途可以淘汰次优解，最快跳出不必要的情况/循环

题目列表（递归->记忆化->动态规划）

- 爬楼梯	`f(n)=f(n-1)+f(n-2),f(1)=1,f(0)=0`

- 不同路径  `f(x,y)=f(x-1,y)+f(x,y-1)`  最自然，无覆盖，可轻松压缩为一维数组

- 打家劫舍 `dp[i]=max(dp[i-2]+nums[i],dp[i-1])`

  `dp[i][0]=max(dp[i-1][0],dp[i-1][1])`低维度0表示没偷

  `dp[i][1]= dp[i-1][0]+nums[i])`

- 三角形最小   路径和  `dp[i][j]=min(dp[i-1][j],dp[i][j-1])+A[i][j]`

- 股票买卖 `dp[i][k][0 or 1](0<=i<=n-1,1<=k<=K)`

  - `i`为天数

  - k为最多交易次数，一笔交易（即买入和卖出一支股票一次）新买入才算下一次，卖出仍属于本次

  - [0,1]为是否持有股票

    总状态数：`n*K*2`种状态

状态都是由  **保持** 或者  **转化**  而来的，时间是连续的，今天只能由昨天而来，只能由昨天**变/不变**而来

    for 0<=i<n:
    	for 1<=k<=K
            for s in {0,1}:
    			dp[i][k][s] = max(buy,sell,rest)
    
    dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1]+prices[i]);
    			  max(      选择rest,         选择sell       )  卖出是收回成本
    今天没持有的情况：
    	昨天没持有股票，今天保持
    	昨天持有，今天卖了
    dp[i][k][1] = max(dp[i-1][k][l],dp[i-1][k-1][0]-prices[i])
    			  max(      选择rest,         选择buy       )  买入是花费成本
    今天持有：
    	昨天持有，保持
    	昨天没持有，今天买入，同时算	新一次交易
因此`dp`方程为

```c++
    dp[-1][k][0]=dp[i][0][0] =0
    dp[-1][k][1]=dp[i][0][1]=-INF   持有股票时，可能成本以及为负值了
    
    dp[i][k][0] = max(dp[i-1][k][0],dp[i-1][k][1]+prices[i]);
    dp[i][k][1] = max(dp[i-1][k][l],dp[i-1][k-1][0]-prices[i])
```

不同路径II由于有了障碍物，因此转移方程变成了
```c++
if(grid[x][y]!=1)
     f(x,y)=f(x-1,y)+f(x,y-1);
else
    f(x,y)=0;
前置条件 也多了 if(grid[0][0]==1||grid[n-1][m-1]==1)return 0
```

## 高级动态规划

状态拥有更多维度（二维，三维，或更多，甚至需要压缩）
状态方程更加复杂
本质：内功、逻辑思维、抽象思维、数学
爬楼梯变形：1 2 3；x1,x2,...xm步；前后不能走相同步伐；

#### 最小花费爬楼梯 

题目是到达`[n]`位置，而不是`[n-1]` ，从`[i]` 往上走就会花费`cost[i]`，因此有如下解法

```c++
int n = cost.size();
vector<int> dp(n+1);
dp[0]=dp[1]=0;
for(int i=2;i<=n;i++){
    dp[i] = min(dp[i-2]+cost[i-2],dp[i-1]+cost[i-1]);
}
return dp[n];
```

官方题解是按照**下楼梯** 思路，符合我们常见认知，到达一阶，有**这一阶**的**奖励** (`cost[i]`会统一) ,同样看最小
```c++
int minCostClimbingStairs(vector<int>& cost) {
    int f1 = 0, f2 = 0;//上方一阶 上方2阶
    for (int i = n - 1; i >= 0; --i) {
        int f0 = cost[i] + min(f1, f2);
        f2 = f1;
        f1 = f0;
    }
    return min(f1, f2);
}

int minCostClimbingStairs(vector<int>& cost) {
    int n = cost.size();
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = cost[0];

    for (int i = 2; i <= n; ++i) {
        dp[i] = min(dp[i - 1], dp[i - 2]) + cost[i - 1];
    }
    return min(dp[n], dp.at(n-1]);
}
```


#### 编辑距离
就算是简单例子的人肉穷举，也很难做  最小距离=>双端BFS，不是`a-z`而是有目的的替换，至少，两端都是尽可能在长度上走接近的方向的，最终长度一致
二维`dp[i][j]表示word1.substr(0,i),word2.substr(0,j)`之间的编辑距离

```c++
不需要直接考虑两个整个词，
w1:....x
w2: ...y
    x==y则 dis(w1[0:i],w2[0:j])=dis(w1[0:i-1],w2[0,j-1])编辑距离不变
    x!=y则 dis(w1[0:i],w2[0:j])=
       	dis(w1[0:i-1],w2[0:j-1])+1  一步替换
        dis(w1[0:i-1],w2[0:j])+1    删掉x
        dis(w1[0:i],w2[0:j-1])+1    删掉y
    注意 增加和删除想法是相对称的,所以以删除为准，且不用考虑一直+++何时停下的问题
        如"" 和 "xyz"
        
    初始化，如果有一方为空，则dis=other.size();即
        dp[i][0]=i;  dp[0][j]=j;
```
## 字符串算法

immutable不可变字符串:Python ,Java,C#,Go

C++可变的（非字符串常量）

Java里字符串 内容相等用`s1.equals(s2)  equalsIgnoreCase`，而不是`s1==s2`，因为`==`是比较指针/reference 地址，尽管内容可能相等，但内存地址不同，就会得到false

1. 字符串，找到它的第一个不重复的字符，并返回它的索引，若不存在，则返回-1。`map(hashmap O(1),treemap O(logN))  再乘O(N)`，或字符哈希表

2. 字符串转换整数`atoi`  正负号，多余空格，非数字等

3. 字符串最长公共前缀:逐列比较  `Trie`  分治

4. 翻转字符串：头尾指针

5. 逐个翻转字符串：①`split + reverse + join`②整个翻转，再每个单词翻转一次

6. Anagram异位词：有效的字母异位词  ，异位词分组，  438字符串中所有字母异位词（滑动窗口,map）

7. Palindrome回文词  最长回文子串`dp[i][j] = (s[i] == s[j]) and dp[i + 1][j - 1]内缩`，对表格只需填`i<=j`部分，且回文串要求长度>=2 因此看到递推式`dp[i+1][j-1]`， 边界为`[i+1,j-1]<2`得`j-i<3`,递推时单个字符也算回文串，且递推也须是从小到大，但dp效率不太佳

```c++
string longestPalindrome(string s) {
    int n = s.size();
    const int MAXM = 1e3 + 1;

    int dp[MAXM][MAXM] = { { 0 } };//这里仍然是表示 bool
    int begin=0,maxLen=1;
    for (int len = 0; len < n; ++len) {
        for (int i = 0; i + len < n; ++i) {	//使用 i+len作为j 边界处理很清晰
            int j = i + len;    //len实际上是 枚举 子串长度-1  也可以统一奇偶性
            if (len == 0) {		//单字
                dp[i][j] = 1;
            } else if (len == 1) {//双字
                dp[i][j] = (s[i] == s[j]);
            } else {
                dp[i][j] = (s[i] == s[j] && dp[i + 1][j - 1]);
            }
            
            if (dp[i][j] && len + 1 > maxLen) {
                begin=i;
                maxLen=len+1;
            }
        }
    }
    return s.substr(begin,maxLen);
}
```

438题滑动窗口

```c++
 vector<int> findAnagrams(string s, string p) {
     vector<int> res;
     int n = s.size(),m=p.size();
     if(n<m)return res;

     int needs[26]={0},win[26]={0};
     for(char c:p)needs[c-'a']++;

     int l =0,r=0;
     while(r<n){
         int curR = s[r]-'a';
         r++;
         win[curR]++;
//有不同的 x>0 或 多出来的 就收缩左边 ，因此当之后r-l==m时，就是完全相同
         while(win[curR]>needs[curR]){
             int curL =s[l]-'a';
             l++;
             win[curL]--;
         }

         if(r-l==m){
             res.push_back(l);
         }
     }
     return res;
 }
```

#### 暴力比较

#### Rabin-Karp

首先对比子串的哈希值，与pattern的哈希值，即`hash(txt.substr(i,M))==hash(pat)(pat只计算一次)`，然后再进行暴力匹配，相当于一层过滤。需要一个好的哈希函数，不能计算量过大，用类似滑动窗口的方法比较好，能够**添头去尾**地用`O(1)`复杂度得到哈希值。256进制，两位都65536了，为避免数据越界，每次模一个素数9997

```c++
const int D = 256;
const int Q = 9997;

int RabinKarpSerach(string txt, string pat) {
    int M = pat.length();
    int N = txt.length();
    int i, j;
    int patHash = 0, txtHash = 0;

    for (i = 0; i < M; i++) {
        patHash = (D * patHash + pat[i]) % Q;
        txtHash = (D * txtHash + txt[i]) % Q;
    }
    int highestPow = 1;  // pow(256, M-1)  最高位权重
    for (i = 0; i < M - 1; i++) 
        highestPow = (highestPow * D) % Q;

    for (i = 0; i <= N - M; i++) { // 枚举起点
        if (patHash == txtHash) {
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j])
                    break;
            }
            if (j == M)
                return i;
        }
        if (i < N - M) {//移除最高位 加上最低位
            txtHash = (D * (txtHash - txt[i] * highestPow) + txt[i + M]) % Q;
            if (txtHash < 0)
                txtHash += Q;
        }
    }

    return -1;
}
```



#### KMP

[阮一峰讲解KMP](http://www.ruanyifeng.com/blog/2013/05/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm.html)

预计算源串`p`的最大相同前后缀，以此在匹配失败时，迅速调到下一个可能的位置，并有一个起始长度，而不是每次都一步步右移比较，每次还要从头开始

```c++
BBC ABCDAB AB
    ABCDABD      遇到不相同字符
    	ABCDABD  下一次比较
如上,匹配到 最后A与D不相等,那么我们就看 D之前 即比较是相等部分(前6个字符) 的最大相同前后缀是多少，这里是2 即AB 那么CD就不用看了，我们直接将 模式串右移6-2=4位，就能对齐这个前缀!!! 一下子就减少了一步步地右移操作，且有了比较的起始长度
    优势就是 这个跳到相同后缀的位置，是完全只看模式串p的，因此可以预计算
```





