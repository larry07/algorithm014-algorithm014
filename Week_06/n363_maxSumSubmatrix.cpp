/**
363.矩形区域不超过K的最大数值和

看了python3代码，也有这个题能到的比较重要的问题
大问题：怎样比较好的把矩形区域枚举出来，怎么暴力计算少一些，枚举左上角 宽 高 是必要的，但还要求和，就一定非常慢
	这里是先枚举[left,right]，题目也提示行数可能远大于列数，所以算是一个 "小循环在外，大循环在内"的for优化
	
然后怎样枚举可能的行范围[rowStart,rowEnd],暴力枚举后的求和还是比较困难
这里是与问题 "求区域和" 联系起来了，直接把每行[left,right]算出来，形成一个rowSum数组
然后问题就变了，这不就是求一维数组连续最大子序和的问题吗？
只不过限制了k，所以比较麻烦，但是整体思路已经非常明朗了，就像自顶向下编程，上层一目了然

*/

class Solution {
public:
//目前是一次看是否最大和<=k,不满足则暴力求解
    int dpMaxSub(const vector<int>& nums, int k) {
        int maxV=INT_MIN,sum=0;
        for(const auto& num:nums){
            sum+=num;
            if(maxV<sum)
                maxV = sum;
            if(maxV>=k)break;
            if(sum<0)
                sum=0;
        }
        if(maxV<=k)return  maxV;

        maxV=INT_MIN;
        int n =nums.size();
        for(int i=0;i< n;i++){
            sum =0;
            for(int j=i;j<n;j++){
                sum += nums[j];
                if(sum>maxV && sum<=k)maxV = sum;
                if(maxV == k)return k;
            }
        }
        return maxV;
    }

    int maxSumSubmatrix(const vector<vector<int>>& matrix, int k) {
        int n = matrix.size(),m= matrix[0].size();
        int res = INT_MIN;

        //[l,r] 对每一种l列开始的矩形，计算每一行的和 rowSum
        for(int l =0;l<m;l++){
            vector<int> rowSum(n,0);
            for(int r = l;r<m;r++){
                for(int row=0;row<n;row++)
                    rowSum[row] += matrix[row][r];
                //对rowSum求连续最大子序和 但限制了 k
                res = max(res,dpMaxSub(rowSum,k));
                if(res==k)return  k;
            }
        }
        return res;
    }
};


/*
附pyhton3 求连续最大子序和 且<=k 的代码
关键：一个转换
sums(i,j)=sums(0,j)-sums(0,i-1)  <=k 且要尽可能大
所以，使用>=sums([0,j])-k寻找时，需要找到 之前的sums[0,i-1]最小，这正好是bisect_left >=插入的功能 可以找到 lst[loc]最小
所以 边构建，边比较结果， lst有序存储了所有{sum([0,j])，j=0~n-1}
*/

import bisect
from typing import List

def maxSub(sums:List[int],k:int)->int:
    lst = [0]
    cur = 0
    res = float("-inf")
    for num in sums:
        cur += num            					#累加和  cur = [0,j]
        loc = bisect.bisect_left(lst,cur-k)     #locate 定位插入位置 
        if loc < len(lst):                      #说明cur-k<=lst中元素
            res = max(cur-lst[loc],res)         #cur-lst[loc] 最接近k的一个值
        bisect.insort(lst,cur)
    return res

nums=[-2,-3,13]
k = 8
res = maxSub(nums,k)
print(res)
