# Week2 学习笔记

语言：C++

观摩了一些大佬的作业，发现自己还存在几个大问题

- 主要是没记录，作业都是最后一下子把自己之前做的复制下来全提交，有的题确实一看，只做了一遍:sweat:而看着同样时间下 大佬的优秀作业，除了**遍数表**，还有**条理清晰的长文** ，感觉报班的价值出来了:smile: ,没有对比就没有伤害！​感觉遍数表 是个**习惯问题** （就是**懒**），做题后立即更新表；而长文应该是在学的过程中就记录下来的，后面再去完善，这样会容易些。自己的是最后再去整理，头大:imp: ，也容易不全。

- 自己的总结缺了对课程的内容总结，只有题的，后面边看视频边写吧。

- 死磕还没完全改掉。因为有的题虽然有想法，但细枝末节没想的很清楚，导致还是耗上了很多时间，而且注意力集中不了很长时间，虽然想提高自律能力，但心有余力不足。。拖延很长时间才继续做。这个不好改啊 :shit:

  这周做题比较乱，总结也比较乱，后面想想怎么整理，也参考下其他人。题解文件现在放入了自己做的多种方法，并以`n+题号+题目函数`命名了，方便提交和后续查看。



## 二叉树

牢记遍历顺序

![2tree](.\res\2tree-traverse.png)

#### 层次遍历

通常bfs+队列

找最大深度问题，可以保持队里内全是当前层结点：   需要一次将当前层<u>所有结点</u>弹出，并将其孩子全部放入

```C++
while(!dq.empty()){
	int sz=dq.size();
	vector<int> cur;
	for(int i = 0;i<sz;i++){
		t = dq.front();
		cur.push_back(t->val);
		dq.pop_front();
		len=t->children.size();
		for(int j=0;j<len;j++){
			if(t->children[j])dq.push_back(t->children[j]);
		}
	}
	res.emplace_back(cur);
}
```
使用DFS可以把 level 传下去
```C++
	//dfs+传入level信息
    vector<vector<int> > res;
    void dfs(Node* node,int level){
        if(res.size()<=level)
			res.emplace_back(vector<int>());//还没有加入本level数组
        res[level].emplace_back(node->val);
        for(auto x:node->children){
            if(x)dfs(x,level+1);
        }
    }
    vector<vector<int>> levelOrder(Node* root) {
        if(root==NULL) return {};
        dfs(root,0);
        return res;
    }
```

对于使用迭代的，一般是模拟栈 ,要思考好过程

```C++
vector<int> inorderTraversal(TreeNode* root) {
	vector<int> res;
	stack<TreeNode*> st;
	TreeNode* cur = root;
	while(cur!=NULL || !st.empty()){
		while(cur!=NULL){ //一直向左走 直到无左子树
			st.push(cur);
			cur=cur->left;
		}
		cur = st.top();
		st.pop();
		res.push_back(cur->val);   //do
		cur=cur->right;            //右子树
	}
	return res;
}
```


### TopK 问题

3种实现 参考问题`n347_topKFrequent.cpp`

- 使用堆，维护大小为k的大根堆（求前k小）小根堆（求前k大）

  C++  **priority_queue**默认大根堆，最小堆如下

  ```C++
  priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
  ```

- 快速排序思想`(int partition(vector<int>& vec,int l,int r))`  + 递归的  随机快速选择`quickSelect(vector<pair<int,int>>& nums,int l,int r,int k)`

  ```C++
      void quickSelect(vector<pair<int,int>>& nums,int l,int r,int k){
          if(l>=r)return;
          int pos = partition(nums,l,r);
          int n=pos-l+1;
          if(n==k)return;
          if(n>k)quickSelect(nums,l,pos-1,k);
          else quickSelect(nums,pos+1,r,k-n);
      }
  ```

- 桶排序  除了数组作为桶  使用map也可以  因为map结构最大优点：有序性

### 一些附加

一些API，要记住

1. deque 就是queue的拓展，平时队列用queue就够了，因为push和pop是统一的

2. 队列分 **前后**  ，栈/优先队列只分**顶部**，所以只有top( )

| stack | queue | deque               | priority_queue |
| ----- | ----- | ------------------- | -------------- |
| push  | push  | push_front/pop_back | push           |
| pop   | pop   | pop_front/pop_back  | pop            |
| top   | front | front               | top            |
|       | back  | back                | -              |



:fire:  加油！:eyes:  