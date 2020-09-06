
//跳跃游戏
//判断是否能够到达最后一个位置

//本想dfs  枚举每次跳1~nums[i] 但对于中间很多很大的元素 如放几个20000 就成了灾难..
//所以必须贪心 只要能跳到的最大距离
class Solution {
public:
    bool canJump(vector<int>& nums) {
        int reach=0,n=nums.size();
        for(int i = 0;i < n;i++){
            if(i > reach)
                return false; 	    //中间有断层 已经跳不到了
			
            if(i+nums[i]>reach)
                reach = i+nums[i];  //类似一个maxValue = max(maxValue,xx); 大则更新
			
            if(reach>=n-1) 			//已经可以跳到了
                return true;		
        }
        return true;
    }
};
