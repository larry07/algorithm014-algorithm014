# 学习笔记

[TOC]

# 课程内容

递归模板

《盗梦空间》类比

```c++
// C/C++
void recursion(int level, int param) { 
  // recursion terminator
  if (level > MAX_LEVEL) { 
    // process result 
    return ; //!!!
  }

  // process current logic 
  process(level, param);

  // drill down 
  recursion(level + 1, param);

  // reverse/restore the current level status /clean if needed 
}
```

## 思维要点

1. 抛弃人肉递归（画递归图，最大误区）才能练熟，要在自己脑子里过递归流程
2. 找到最近最简方法，将其拆解成可重复解决的子问题  程序只有3部分 `if-else` 和`for while loop`以及 递归调用  如果可以简化，就是因为可重复性
3. 数学归纳法的思维  点100响的爆竹

所有分项：mutual exclusive,complete exhaustive   （相互排斥,完成详尽的）

### 爬楼梯

```c++
int climbStairs(int n) {
	if(n<=3)return n;
	return climbStairs(n-1)+climbStairs(n-2);
}
```

傻递归，性能很差，因为分支分的太多了，重复计算也多，如下是记忆化递归

```C++
int climbStairs(int n) {
    int* memo=new int[n+1];
    return climb(0,n,memo);//0阶爬到n阶
}
int climb(int i,int n,int memo[]){
    if(i>n)return 0;
    if(i==n)return 1;
    if(memo[i]>0)
        return memo[i];
    memo[i]=climb(i+1,n,memo)+climb(i+2,n,memo);
    return memo[i];
}
```

动态规划  数组递推 也可用滚动常数优化空间

```c++
res=b+a;
a=b;
b=res;  //b>a
	=>
a = (b += a) - a;
```
**矩阵运算** 

```C++
int pow(int x,int n){
    int r =1;
    int v =x;
    while(n){
        if(n % 2==1){ //奇数
            r*=v;
            n--;
        }
        v=v*v; //3^10 = (3^2)^5
        n=n/2;
    }
    return  r;
}
mat matrix22_pow(int x,int n){
    mat r =[[1,0],[0,1]];
    mat v =x;
    while(n){
        if(n % 2==1){ //奇数
            r=matrix22_mul(r,v);
            n--;
        }
        v=matrix22_mul(v,v);
        n=n/2;
    }
    return  r;
}
matrix22_mul([[0,1],[0,0]],matrix22_pow([[0,1],[1,1]],n-1))[0][1];
```

### 括号生成

```c++
void generate(const string& current, int n, vector<string>& result){
    if (current.size()==n) {
        result.push_back(current);
        return;
    }
    generate(current+"(",n,result);
    generate(current+")",n,result);
}
vector<string> res;
generate("",1*2,res);
```

得到4种 `((`,`()`,`)(`,`))` 就是以长度为限制，像二叉树一样，从`""` 向左右分叉为`"("` 和`")"` 进行扩张（这就是同时2个`generate()`递归,同等`current`下的2种选择），最后路径上的字符就是结果。主要限制：

- 右括号数量始终≤左括号数量
- 左括号数量≤n/2   (n为总字符数)

加上限制，相当于对二叉树进行`剪枝` 

```C++
void generate(string current, int left,int right, int n, vector<string>& result) {
    if (current.size()==2*n) { //或left==n && right ==n
        result.push_back(current);
        return;
    }
    if(left<n)		//可以使用左括号
        generate(current+"(",left+1,right, n, result);
    if(left>right)	//可以使用右括号
    	generate(current+")", left,right+1,n, result);
}
string current;
generate(current, 0,0,n, result);
```

爱上看别人的代码，借鉴他人，重剑无锋，大巧不工。上道，取别人精华，模拟，反复写，提高自己的水平。

## 分治

模板

```C++
int divide_conquer(Problem *problem, int params) {
  // recursion terminator
  if (problem == nullptr) {
    process_result
    return return_result;
  } 

  // process current problem
  subproblems = split_problem(problem, data)
  subresult1 = divide_conquer(subproblem[0], p1)
  subresult2 = divide_conquer(subproblem[1], p1)
  subresult3 = divide_conquer(subproblem[2], p1)
  ...

  // merge
  result = process_result(subresult1, subresult2, subresult3)
  // revert the current level status
  return 0;
}
```

## 回溯

一种通过**遍历所有可能成员**来寻找**全部可行解**的算法。若候选 不是 可行解 (或者至少不是 最后一个 解)，回溯法会在前一步进行一些修改以舍弃该候选，换而言之， 回溯 并**再次尝试**。

也是递归实现，典型的例子就是八皇后 括号生成

归去来兮的感觉





# 学习心得

这周题目难度感觉变大了，一到递归回溯就不容易想，以前也很少写递归，所以很生疏，每个题的题解的主要思路也只有常见的一两种，但看的也很费劲:cry:  ,状态也下滑了些​，不过看到群里还是有很多精神十足的人在刷题，感觉我还能战:smile: ，从别人的作业中也得到了很多力量，感谢！不过自己的组织学习能力还真是差挺多的，加油！



### 组合数

这种问题，感觉最主要的是如何去掉类似	`visited`数组或`isValid`函数，组合数问题中，可以通过`start+1`解决，保证 后一个加入的 一定在前面递归层级中没出现过

还可以使用二进制字典序 从`0000~1111` 但代码不容易写出来

```C++
vector<vector<int> > res;
vector<int> list;
for (int i = 1; i < k+1; ++i)
    list.emplace_back(i);
list.emplace_back(n+1);       //对4 2为 [1 2 5]只需要窗口大小+1 , 倒序的低位在前

int j=0;
while(j<k){
    res.emplace_back(list.begin(),list.begin()+k);
    j=0;
    while((j<k) && list[j]+1==list[j+1]) {
        list[j] = j + 1;    //(还原)正常的[0]=1当前位数最大了  窗回到1  1110=>10011
        j++;
    }
    list[j]=list[j]+1;//最高位升1
}
return res;
```

最终 345 =>126 最高位已经来到了 k位 ，说明该退出了

### 全排列

可以将题目给定的 n 个数的数组 `nums[]` 划分成左右两个部分，左边的表示已经填过的数，右边表示待填的数，我们在递归搜索的时候只要动态维护这个数组即可。

代码维护` first`之后的都是没有填过的数，最终`first =len` 结束

由于`[ first len-1] `是未填入的，所以每次` swap(nums[first],nums[i] ) `

**若全排列允许有重复数字** ，则swap可能打乱剩余相同的顺序，如对`1 2 2 3 4`选择`4 2231`之后`41 232`

这样仅仅靠`i>1 && nums[i] == nums[i-1]` 是过滤不掉的，而每轮使用hash表，非常浪费，所以还是使用`visited` 数组来过滤

```c++
vector<int> list;
void backtrace(vector<vector<int>>& res,const vector<int>& nums,
               vector<bool>& used,int index){
	if(index==nums.size())
		res.push_back(list);
	
	for(int i=0;i<nums.size();i++){
		if(used[i])continue;
		if(i>0 && nums[i]==nums[i-1] && !used[i-1])
			continue;  //排除掉  本轮除第一次出现以外的重复元素
		
		used[i]=true;
		list.emplace_back(nums[i]);
		backtrace(res,nums,used,index+1);
		list.pop_back();
		used[i]=false;
	}
}

```

### 从前序和后序序列构建二叉树

主要是从中序 知道**当前根节点**=>再从前序得到**分割的区间**，进行分治

为避免从中序序列遍历得到索引值，使用哈希表存储  `值-索引`  关系，以下为使用数组

```c++
maxVal=INT_MIN;//全局，因为函数 index 要使用
int minVal=INT_MAX;
for(auto x:inorder){
    minVal = min(minVal,x);
    maxVal = max(maxVal,x);
}
int* nodeMap = new int[minVal>=0? maxVal+1: maxVal-minVal+1]; //构建哈希表
for (int i = 0; i < m; i++) {
    nodeMap[index(inorder[i])] = i;
}
inline int index(int val) {
    return (val >= 0 ? val : maxVal - val);
}//[0 maxVal] 存正数，(maxVal maxVal-minVal]存负数 	共maxVal-minVal+1个数
```

构建是一个前序遍历过程

```c++
TreeNode* build(const vector<int>& preorder,int pl,int pr,int il,int* nodeMap){
    if(pl==pr)		//[pl pr) 前闭后开
        return NULL;

    int rootVal = preorder[pl];
    TreeNode* root = new TreeNode(rootVal);

    int rootIndex = nodeMap[index(rootVal)];

    int delta = rootIndex - il;
    root->left = build(preorder,pl + 1, pl + delta + 1, il,nodeMap);
    root->right = build(preorder,pl + delta + 1, pr, rootIndex + 1, nodeMap);
    //[rootIndex+1 ..new rootIndex 绝对索引

    return root;
}
build(preorder, 0, n, 0, nodeMap);
```

**迭代法原理**

对于前序遍历中的任意两个连续节点 u 和 v， u和v只有两种可能的关系：

- v 是 u 的左儿子。
- u 没有左儿子，并且 v 是 u 的某个祖先节点（或者 u 本身）的右儿子。
  如果 u 没有左儿子，那么下一个遍历的节点就是 u 的右儿子。
  如果 u 没有右儿子，就会向上回溯，直到遇到**第一个**有右儿子（且 u 不在它的右儿子的子树中）的节点 $u_a$，那么 v 就是 $u_a$的右儿子。

就相当于带两个端点的线段`u=>v=>`一前一后，沿着前序遍历的轮廓——向前滑动所能遇见的情况。

栈:	存当前节点的所有还没有考虑过右儿子的祖先节点，栈顶就是当前节点。初始为前序遍历的第一个节点。
index: 	指向中序遍历的某个位置，初值0。对应节点是「当前节点不断往左走达到的最终节点」

目前还没有掌握。

```c++
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
	if (!preorder.size()) {
		return nullptr;
	}
	TreeNode* root = new TreeNode(preorder[0]);
	stack<TreeNode*> stk;
	stk.push(root);
	int inorderIndex = 0;
	for (int i = 1; i < preorder.size(); ++i) {
		int preorderVal = preorder[i];
		TreeNode* node = stk.top();
		if (node->val != inorder[inorderIndex]) {
			node->left = new TreeNode(preorderVal);
			stk.push(node->left);
		}
		else {
			while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
				node = stk.top();
				stk.pop();
				++inorderIndex;
			}
			node->right = new TreeNode(preorderVal);
			stk.push(node->right);
		}
	}
	return root;
}
```



## 一些附加


$$
C_n^0+C_n^1+C_n^2+...+C_n^n=2^n \\
C_n^1+C_n^2+...+C_n^n=2^n-1
$$

第一个公式，就是相当于n个元素的**选与不选**的合集，第二个公式至少选一个

```C++
vector<vector<int> > vecs;
vecs.push_back({1,2,3,4});//这里不能使用emplace_back
```

:fire: 加油!	:eyes:

