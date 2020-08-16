# Week1 学习笔记

语言：C++

解题需要注意 

* 理解并记忆解法
* 熟悉API函数 `unordered_map<int,int> map;` 和` if(map.count(x)&&map[x]...)`
* 写代码前，一定确保**理解了题意**！！！（我的模拟队列还是从尾部出队的:sweat_smile:）要对整体逻辑要心中有数，尽可能想到所有要注意的点
* 一定要思考题目条件下的**额外信息**，利用找到的特点可以形成更巧妙的算法，也就是面试考察的逻辑思维能力，目前还是挺欠缺的:sweat: 所以要多思考，多向他人学习(链表环入口，除了哈希表`<ListNode*,int>`，Floyd规律)
* 提高效率，避免死磕，避免拖延，避免半天做一题:worried:, 过遍数，每一次清空重做总能发现很多问题。。再简单的题还是错了好多次。

## 数组链表

1.数组可以构建 高级的数据结构，如链表，栈，（环形）队列

对字符串问题，数组还可以作为**哈希表/桶**，进行计数，如`vec[128]代表ASCII码`，然后对字符c计数`vec[c]++;`

2.链表

基本功：反转链表，两两反转，k个一组反转（可以在每一节的tail后面使用头插法），链表环问题

递归方法需要加强 :shit:

快慢指针

链表最重要的特点：**单向**  因此注意保持前一个，避免回不去/访问不了

```C++
//翻转单链表
ListNode* pre,* cur,*ne;
cur = head;
pre = NULL;
while(cur){
    ne= cur->next; //pre->cur -> ne->... 先存ne  再pre<-cur ne->...
    cur->next=pre;
    pre=cur;
    cur=ne;
}
return pre;
```

## 栈 队列 双端队列

双指针 

看了一个`单调栈`，栈顶弹出过程中可以结束栈顶元素的处理（最大面积，接雨水），但是具体套路，需要多看。。。

一个滑动窗口算法：移入+移出    窗口 [ left , right)

```C++
void slidingWindow(string s, string t) {
    unordered_map<char, int> need, window;
    for (char c : t) need[c]++;

    int left = 0, right = 0;
    int valid = 0;
    while (right < s.size()) {
        char c = s[right];    // c 是将移入窗口的字符
        right++;              // 右移窗口
        // 进行窗口内数据的一系列更新
        ...

        printf("window: [%d, %d)\n", left, right);

        // 判断左侧窗口是否要收缩
        while (window needs shrink) {
            char d = s[left];  // d 是将移出窗口的字符
            left++;            // 左侧窗口收缩
            // 进行窗口内数据的一系列更新
            ...
        }
    }
}
```

### 解题语法点

'a'~0x61 'A'~0x41  相差0x20，即32

`char* chrs=new int[len+1]`  字符串有保留位 `'\0'`

`return to_string(A)+"A"+to_string(B)+"B";`  string 可以用+=

`if(!vec.empty() && vec.back())` 使用back()方法，前提是**vector非空**  很多方法也都需要非空才能用！

`vec`作为成员变量，初始化`className( ):vec(k,0){ }`  不能使用new 如`vec = new vector<int>(k);`

`ListNode dummy(0);  dummy.next=head;`  哑节点

`tail->next=l1?l1:l2;`  条件表达式 简化代码

`while (i >= 0 || j >= 0 || add != 0) {int x = i >= 0 ? num1[i] - '0' : 0;  ...`  简化 少个if 分支

`map.insert(make_pair(complement,i))`  注意C++ insert 不会覆盖，`map[complement]=i` 可以覆盖，并且可以作为新插入

`return  {nums[i],nums[j],nums[k]};` 对于返回vector 的 ，可以返回初始化列表

`if(i>0 && nums[i]==nums[i-1])continue;`  //去重 只要第一个 ;3元组 不能重复 **不能要最后一个 漏解 0 0 0**



### 一些附加

加一问题，是一个只考虑`最低位和进位`的**重复结构**，去掉最后一位，如果有进位，则又变成了**前面部分+1**的操作

爬楼梯：DP **最近**重复子问题    n阶 只能从n-1台阶跨一级 到达 ；或n-2级台阶 跨2步到达   ，   空间：滚动数组

代码顺序  ， 区间开闭规定，如 pre[start ... end] next 



:fire:  加油！:eyes:  