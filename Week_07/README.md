Week8 学习笔记

## 高级搜索

不用花太多时死磕，间隔时间反复过遍数，可能就慢慢理解了

相对的  初级搜索  朴素搜索

优化方式：**不重复**（斐波那契，备忘录），**剪枝**（生成括号问题，分析隐含限制）

搜索方向：

DFS深度优先（不回头），BFS 广度优先（水波纹，扩散到距离最近的）

### 剪枝

合适的剪枝（剪重复/不合理），或局部贪心（早点确定上界，可以在之后尽快结束），可以大大减少树的节点数量

**回溯**  试错，现有分步答案不能得到有效的正确解答时，它将取消上一步甚至是上几步的计算，再通过其他的可能分步解答再次尝试寻找问题的答案。

回溯通常就用递归实现，结果可能是找到了一个，或所有可能的都失败，最坏情况下，回溯法会导致一次复杂度为指数时间的计算

人类主要就是 回溯深度不够，短期记忆不准，也比较懒:smile:

### 双向BFS

起点，终点分别做BFS ，然后在中间相遇  **数独**问题可用 ，下面以  单词接龙（从 *beginWord* 到 *endWord* 的最短转换序列的长度）  作为模板，使用2个队列（begin,end,不一定使用队列queue），也不再是`while(!queue.empty())`，而是`while(!beginSet.empty())` ，并且维护每次搜索的都是大小较小的队列，当从`beginSet`搜索到的`str`满足`endSet.count(str)==1`说明相遇了，非常有效！

```C++
int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    unordered_set<string> dict(wordList.begin(), wordList.end());
    if(dict.count(endWord) == 0)return 0;
    unordered_set<string> beginSet={beginWord},endSet={endWord};;

    int res=1;
    while(!beginSet.empty()){
        res++;
        unordered_set<string> tmpset;           //临时变量 代表本层 更明确
        for(auto s:beginSet)                    //把上一层从dict中清掉，等价于visited
            dict.erase(s);                      //若不存在，则erase无效
        for(string s:beginSet){
            for(int i=s.size()-1;i>=0;i--){
                string str=s;
                for(char c='a';c<='z';c++){
                    str[i]=c;
                    if(dict.count(str) == 0)
                        continue;
                    if(endSet.count(str) == 1)
                        return res;
                    tmpset.insert(str); 
                }
            }
        }
        if(tmpset.size() < endSet.size())
            beginSet=tmpset;
        else{
            beginSet=endSet;
            endSet=tmpset;
        }
    }
    return 0;
}
```

### 启发式/优先级/思考型搜索(A*)Heuristic Search

不用栈/队列，而是用**优先队列**，按照优先级（有些节点更可能会达到我们需要的结果），先把优先级高的从拿出来进行搜索

搜索问题，脑海里要有一棵搜索树，如 零钱置换的状态树，**数形结合**

人生就是一棵状态数，能看见眼前的几步选择，但一般只能走一条，也可以放弃一条路重头再来

重要的是：定优先级怎样更优  启发式函数 优先级定义函数/估价函数

启发式函数：h(n) 返回一个非负实数，也可认为是从节点n到目标节点路径的估计成本。

是一种告知搜索方向的方法，提供一种明智的方法来猜测那个邻居节点会导向一个目标

```python
# Python
def AstarSearch(graph, start, end):
	pq = collections.priority_queue() # 优先级 —> 估价函数
	pq.append([start]) 
	visited.add(start)
	while pq: 
		node = pq.pop() # can we add more intelligence here ?
		visited.add(node)
		process(node) 
		nodes = generate_related_nodes(node) 
   		unvisited = [node for node in nodes if node not in visited]
		pq.push(unvisited)
```

```c++
C/C++
class Node {
public:
    int x;
    int y;
    bool operator< (const Node &A) {
        // 
    }
};

void generate_related_nodes(Node &node) {
    // 
}
void process(Node &node) {
    // 
}

void AstarSearch(vector<vector<int>>& graph, Node& start, Node& end) {
    vector<vector<bool> > visited(graph.size(), vector<bool>(graph[0].size(), false));
    priority_queue<Node> q;
    q.push(start);

    while (!q.empty()) {
        Node cur = q.top();
        q.pop();
        visited[cur.x][cur.y] = true;

        process(node);
        vector<Node> nodes = generate_related_nodes(node) 
        for (auto node : nodes) {
            if (!visited[node.x][node.y]) q.push(node);
        }
    }
    return ;
}
```

#### 1091二进制矩阵中的最短路径

从左上角走到右下角，八连通，有障碍

DP、BFS都是没有方向性的

越直接往右下走越快（越接近/沿着正方形对角线），A*就是先找最可能最短的路径，若通了，则就是结果，若不通，则继续找次短的，以此类推。即先找捷径。国际站有动图演示，BFS就是傻傻的扫图。

#### 773滑动谜题

```c++
DFS 最后棋盘的状态是有限的
BFS 更快找到最优解 第一次的状态到达最后一次的状态，状态树就是不同的棋盘状态，而不是一个位置
    0 1 2
    3 4 5
    以位置为准，有如下技术处理，方向变换向量
    使用位置，所以可以用一维数组/字符串表示，字符串可以用set存起来，表示visited
unordered_map<int,vector<int>>moves={
    {0,{1,3}}, //位置0可以跟右边1 or 下面3交换
    {1,{0,2,4}},
    {2,{1,5}},
    {3,{0,4}},
    {4,{1,3,5}},
    {5,{2,4}}
};
```

`A*`本身也是基于BFS，曼哈顿是二维的，做本题的相似度更好

- 曼哈顿距离: 两个点在标准坐标系上的绝对轴距之和  $d(i,j)=|x_i-x_j|+|y_i-y_j|$

- 欧式距离：应用勾股定理计算两个点的直线距离

- 汉明距离：两个字符串对应位置的不同字符的个数



## AVL和红黑树的实现和特性

二叉树和链表没有本质区别，只是每个节点多了一个分叉

 二叉搜索树，也称有序二叉树（Ordered Binary Tree）、排序二叉树（Sorted Binary Tree）,指一棵空树或具有以下特点的树

- 左子树**所有节点**均<它的根节点的值
- 右子树**所有节点**均>它的根节点的值
- 以此类推：左右子树也分别为二叉搜索树（重复性）

中序遍历：升序排列

查找类似二分搜索，时间复杂度为O(h)  平均树高h=log2n

最差时，退化成一根棍子链表 h=n

所以要保证性能

1. 保证二维维度>左右子树节点平衡（recursively）
2. Balanced平衡二叉树，每一步插入/删除都会去判断，维护成平衡二叉树

23树，AA树，AVL，B树，B+树（数据库索引结构）,红黑树，Treap 树、Splay伸展树  都是平衡二叉树

### AVL树

1. 自平衡**二叉搜索树!!**  Self-balancing binary search tree

2. Balance Factor左子树高度减去它的右子树**高度**（有时相反），递归地保持在`{-1,0,1}`

3. 通过旋转操作进行平衡（4种）后两种是前两种的搭配起来，子树以从根到底部称呼 方向，"左右子树"即从根先到左再到右，左右旋说的是（子）树根，旋转依据是<u>保持二叉搜索树的左右大小性质</u>，旋转后的根的值一定是三者中的**中位数**。以下三结点高度A>B>C，后两种旋转都是先旋转B再旋转A，将中位数C结点转上来。

- 左旋  右右子树`A->B->C`   =>A左旋  `A<-B->C`

- 右旋  左左子树`C<-B<-A`   =>A右旋  `C<-B->A`

- 左右旋  左右子树`B<-A,B->C`  =>B左旋 `B<-C<-A`=>A右旋`B<-C<-A`

- 右左旋  右左子树`A->B,C<-B` =>B右旋`A->C->B`=>A左旋`A<-C->B`

  记录每个结点的深度

  带有子树的旋转，基于大小关系，将子树也挂到相应位置

  如右旋`C<-B<-A`   =>  `C<-B->A`，若B带一个右子树，则右旋后要挂到A的左子树

  [参考动画]: https://zhuanlan.zhihu.com/p/63272157

不足：结点需要存储额外信息，且调整次数频繁，因为-1 1已结是非常严格的高度差了。实际并不一定需要这么完美，调整的开销可能跟放宽要求的算法差距不大。

所以引入其他树——**近似平衡二叉树**compromise妥协折中

### 红黑树

近似平衡的二叉搜索树，能确保左右子树<u>**高度差**</u>小于2倍，（左右子树中，大的高度差最多是小的两倍）具体为满足如下条件的BST:

- 每个结点要么是红色，要么是黑色

- 根节点是黑色

- 每个叶子结点（NIL结点，空结点）是黑色的

- 不能有相邻的两个红色结点

- 从任一结点到每个叶子的所有路径都包含相同数目的黑色结点

Red Black Tree (RB Tree)对比AVL:

  - AVL trees provide **faster lookups** because AVL are more strictly balanced.
  - RB Tree provide **faster insertion and removal** operations than AVL trees as fewer rotations are done due to relatively relaxed balancing.
  - AVL trees store balance **factors or heights** with each node,thus requires storage for an integer per node whereas RB Tree requires only 1bit of information per node
  - RB Trees are used in most of the **language libraries** like **map,multimap,multiset in C++** whereas AVL trees are used in **databases** where faster retrievals are required.

:fire:加油！:eyes: 