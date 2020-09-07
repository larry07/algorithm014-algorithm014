# 学习笔记

​		感觉第四周这周又拉胯了:sob: ，周内有天被一道题搞住了，自己也花了挺长时间，但是老出错，然后就停滞不前了一天，再去看，就没那么大干劲了。单词接龙的题目也让自己看了挺久。感觉就像锻炼跑步一样，跑了很久，突然松懈一下，停下来，就不那么容易再重新跑了。不过听周四的直播，学习有自律，也有他律，感觉说的很对，很难战胜自己的懒惰，但看到他人一直学习，还是挺敬佩的，下一周，要振作起来！还有考试。。。:sweat:

# 课程内容

## 搜索-遍历

每个节点都要访问一次，且仅仅访问一次

顺序不限

DFS深度优先 `depth first search`

BFS广度优先 `breadth first search`

优先级优先 --适用于现实中的很多业务场景  启发式搜索 具有估价函数

```python
def dfs(node):
    if node in visited:
        return
    visited.add(node)
    
    #process current node
    #... #logic here
    dfs(node.left)
    dfs(node.right)
  
def dfs(node,visited):
    visited.add(node)
    #process current node
    for next_node in node.children():
        if not next_node in visited:
            dfs(next_node,visited)
```

DFS递归

```c++
//C/C++
//递归写法：
map<int, int> visited;

void dfs(Node* root) {
  // terminator
  if (!root) return ;

  if (visited.count(root->val)) {
    // already visited
    return ;
  }

  visited[root->val] = 1;

  // process current node here. 
  // ...
  for (int i = 0; i < root->children.size(); ++i) {
    dfs(root->children[i]);
  }
  return ;
}
```

DFS非递归

```c++
//C/C++
//非递归写法：
void dfs(Node* root) {
  map<int, int> visited;
  if(!root) return ;

  stack<Node*> stackNode;
  stackNode.push(root);

  while (!stackNode.empty()) {
    Node* node = stackNode.top();
    stackNode.pop();
    if (visited.count(node->val)) continue;
    visited[node->val] = 1;

    for (int i = node->children.size() - 1; i >= 0; --i) {
        stackNode.push(node->children[i]);
    }
  }
  return ;
}
```

BFS  队列

```c++
// C/C++
void bfs(Node* root) {
  map<int, int> visited;
  if(!root) return ;

  queue<Node*> queueNode;
  queueNode.push(root);

  while (!queueNode.empty()) {
    Node* node = queueNode.top();
    queueNode.pop();
    if (visited.count(node->val)) continue;
    visited[node->val] = 1;

    for (int i = 0; i < node->children.size(); ++i) {
        queueNode.push(node->children[i]);
    }
  }

  return ;
}
```



## 贪心算法

`每一步选择中都采取当前状态最好或最优（即最有利）的选择，从而希望导致结果是全局最好/最优的算法。`

中文内也有 “鼠目寸光”，“ 因小失大”，“ 只顾眼前不顾将来“来说明贪心，但有可能某一步贪心，全局搜索递归/动态规划

- 贪心：当下（每个子问题的解决方案）做局部最优判断，**不能回退**

- 回溯：能够回退

- 动态规划：最优判断+回退（会保存以前的运算结果，并根据以前的结果对当前进行选择，有回退功能。）

贪心解决最优化的问题：图的最小生成树 哈夫曼编码。工程中一般不行。

但**一旦**可以通过贪心法解决，那么贪心法一般是这个问题的**最好办法**。由于贪心法的高效性以及所求得答案比较接近最优结果，所以贪心法可作为**辅助算法**或直接解决一些**要求结果不特别精确**的问题。Dijkstra里面辅助

### 零钱兑换

贪心法反例，如果硬币不具有整除/倍数关系，如[10 9 1] 拼18 显然2个9就可以了，但用10则后面全1

所以贪心法，自己要证明是能用贪心的，问题转化下

### 跳位置

从后往前贪心  记住能够跳到位置的第一个值，节省了一个数组来记录中央的结果，节省一层循环

```c++
bool canJump(vector<int> nums){
    if(nums.empty())return false;
    int enReachable = nums.size()-1;
    for(int i = nums.size()-1;i>=0;i--){
        if(i+nums[i]>=enReachable){ //从[i]能够跳到enReachable
            enReachable = i;
        }
    }
    return endReachable == 0;
}
```

## 二分查找

前提

- 模板函数单调性（单调递增Or递减）
- 存在上下界（bounded）
- 能够通过索引访问（index accessible）

模板

```c++
int binarySearch(const vector<int>& nums, int target) {
	int left = 0, right = (int)nums.size()-1;
	
	while (left <= right) {
		int mid = left + (right - left)/ 2;
		if (nums[mid] == target) return mid;
		else if (nums[mid] < target) left = mid + 1;
		else right = mid - 1;
	}
	return -1;
}
```

完全平方数  动态规划 / 位运算解法

### 二分查找，寻找一个半有序数组 [4, 5, 6, 7, 0, 1, 2] 中间无序的地方

这个就是`153.寻找旋转排序数组中最小值findMin`题目,因为`[mid]`只可能在左区或右区

`left`和`right` 夹逼直到`出while，left=right` 都在右区，则为`min`

```c++
if (nums.size() == 1)
	return nums[0];
int left = 0,right = nums.size() - 1;
while (left < right){
    int mid = left + ((right - left) >> 1);
    if (nums[mid] > nums[right])  //mid在左区，right在右区
        left = mid + 1;           //left 可能越到右区
    else						  //mid同right都在右区 right往左缩 并保持right在右区
        right = mid;
}
return nums[left];
```



## DFS相关题目

### DFS 应用-岛屿问题

二叉树的 DFS 有两个要素：「**判断 base case/terminator**」和「**访问相邻结点/drill down **」

对于格子` (r, c)` 来说（r 和 c 分别代表行坐标和列坐标），四个相邻的格子分别是 `(r-1, c)、(r+1, c)、(r, c-1)、(r, c+1)` 换句话说，网格结构是`四叉的`.

下面terminator是 **先污染后治理** 型的，即`if(root==NULL)` 型，另一种写法就像`if(root->left)dfs(root->left)`;因此也不会下传`NULL`。

```c++
void dfs(int[][] grid, int r, int c) {
    // 判断 base case, 坐标 (r, c) 超出了网格范围，直接返回
    if (!inArea(grid, r, c)) {
        return;
    }
    // 访问上、下、左、右四个相邻结点
    dfs(grid, r - 1, c);
    dfs(grid, r + 1, c);
    dfs(grid, r, c - 1);
    dfs(grid, r, c + 1);
}

// 判断坐标 (r, c) 是否在网格中
boolean inArea(int[][] grid, int r, int c) {
    return 0 <= r && r < grid.length 
        	&& 0 <= c && c < grid[0].length;
}
```

**如何避免重复遍历**

网格结构的 DFS 与二叉树的 DFS 最大的不同之处在于，遍历中可能遇到遍历过的结点。这是因为，网格结构本质上是一个「**图**」，我们可以把每个格子看成图中的结点，每个结点有向上下左右的四条边。在图中遍历时，自然可能遇到重复遍历结点。

这时候，为避免DFS 可能的不停「兜圈子」，需要标记已经走过的节点。岛屿问题为例，我们需要在所有值为 1 的**陆地格子**上做 DFS 遍历。每走过一个陆地格子，就把格子的值改为 2，这样当我们遇到 2 的时候，就知道这是遍历过的格子了。也就是说，每个格子可能取三个值：

-  0 —— 海洋格子
- 1 —— 陆地格子（未遍历过）
- 2 —— 陆地格子（已遍历过）

```c++
void dfs(int[][] grid, int r, int c) {
    if (!inArea(grid, r, c)) {
        return;
    }
    // 如果这个格子不是岛屿，直接返回
    if (grid[r][c] != 1) {
        return;
    }
    grid[r][c] = 2; // 将格子标记为「已遍历过」
    
    // 访问上、下、左、右四个相邻结点
    dfs(grid, r - 1, c);
    dfs(grid, r + 1, c);
    dfs(grid, r, c - 1);
    dfs(grid, r, c + 1);
}
boolean inArea(int[][] grid, int r, int c) {
    return 0 <= r && r < grid.length 
        	&& 0 <= c && c < grid[0].length;
}
```

有的访问过就**将陆地沉没为海洋**，但一旦要求海洋细节，就会无法区分了

例子：求岛屿周长问题 ，将岛屿的周长中的边分为两类

黄色的边是与网格边界相邻的周长，而蓝色的边是与海洋格子相邻的周长

```c++
public int islandPerimeter(int[][] grid) {
    for (int r = 0; r < grid.length; r++) {
        for (int c = 0; c < grid[0].length; c++) {
            if (grid[r][c] == 1) 
                return dfs(grid, r, c); // 题目限制只有一个岛屿，计算一个即可
        }
    }
    return 0;
}

int dfs(int[][] grid, int r, int c) {
    // 函数因为「坐标 (r, c) 超出网格范围」返回，对应一条黄色的边
    if (!inArea(grid, r, c)) {
        return 1;
    }
    // 函数因为「当前格子是海洋格子」返回,(只计一个，不往海洋深处走),对应一条蓝色的边
    if (grid[r][c] == 0) {
        return 1;
    }
    // 函数因为「当前格子是已遍历的陆地格子」返回，和周长没关系
    if (grid[r][c] == 2) //!=1
        return 0;
    grid[r][c] = 2;
    return dfs(grid, r - 1, c)
        + dfs(grid, r + 1, c)
        + dfs(grid, r, c - 1)
        + dfs(grid, r, c + 1);
}
```



### BFS应用

- BFS应用1：二叉树的层次遍历

​       BFS直接，DFS也可以，记住节点的 level 信息，在求深度时，BFS将一次出队队内所有节点

- BFS应用2：最短路径

`※`  Dijkstra 算法解决的是**带权最短路径**问题，当关注的是**无权最短路径**问题（也可以看成每条边的权重都是 1），用 BFS 求解就行了。

最短路径问题属于**图算法**。由于图的表示和描述比较复杂，本文用比较简单的**网格结构**代替。网格结构是一种特殊的图，它的表示和遍历都比较简单，适合作为练习题。在 `LeetCode` 中，最短路径问题也以网格结构为主。

[LeetCode 1162. As Far from Land as Possible](https://leetcode-cn.com/problems/as-far-from-land-as-possible/) 离开陆地的最远距离（Medium）

网格结构的层序遍历，一次一层全部出队

```c++
// 网格结构的层序遍历
// 从格子 (i, j) 开始遍历
pair<int,int> moves = {
	{-1, 0}, {1, 0}, {0, -1}, {0, 1},
};
void bfs(vector<vector<int> >& grid, int i, int j) {
    if(grid.empty())
        return;
    int nr = grid.size(),nc = grid[0].size();
    queue<pair<int,int> > Q;
    Q.push_back({r, c});
    while (!Q.empty()) {
        //distance++;
        int n = Q.size();
        for (int i = 0; i < n; i++) {
            auto node = Q.front();Q.pop();
            int r = node.first;
            int c = node.second;
            for(auto move:moves){
                int x = r + move.first;
                int y = c + move.second;
                if(inArea(grid,x,y) && grid[x][y]==0){ //海洋格子
                    grid[x][y]=2;
                    Q.push({x,y});
                }
            }
        }
    }
    return distance;
}
bool inArea(vector<vector<int> >& grid,int r,int c){
    return 0 <= r && r < grid.size() &&
           0 <= c && c < grid[0].size();
}
```

最终遍历了几层，海洋格子的最远距离就是几。

有多个陆地格子的时候怎么办？一种方法是将每个陆地格子都作为起点做一次层序遍历，但是这样时间开销太大。

BFS 完全可以**以多个格子同时作为起点**。我们可以把所有的陆地格子同时放入初始队列，然后开始层序遍历

在代码中，我们不需要给每个遍历到的格子标记层数，只需要用一个 `distance` 变量记录当前的遍历的层数（也就是到陆地格子的距离）即可

```c++
bool inArea(vector<vector<int> >& grid,int r,int c){
    return 0 <= r && r < grid.size() &&
        0 <= c && c < grid[0].size();
}

int maxDistance(vector<vector<int>>& grid) {
    int N =grid.size();
    if(N==0)return -1;
    queue<pair<int,int> > Q;
    //...将所有陆地格子（==1）加入队列
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            if(grid[i][j]==1)Q.push({i,j});
        }
    }
    if(Q.empty()||Q.size()==N*N)return -1;
    int distance = -1; // 记录当前遍历的层数（距离）
    pair<int,int> moves[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    while (!Q.empty()) {
        distance++;
        int n = Q.size();
        for (int i = 0; i < n; i++) {
            auto node = Q.front();Q.pop();
            int r = node.first;
            int c = node.second;
            for(auto move:moves){
                int x = r + move.first;
                int y = c + move.second;
                if(inArea(grid,x,y) && grid[x][y]==0){ //海洋格子
                    grid[x][y]=2;
                    Q.push({x,y});
                }
            }
        }
    }
    return distance;
}
```

:fire:加油！:eyes: