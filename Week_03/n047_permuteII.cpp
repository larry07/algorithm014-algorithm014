
/*
全排列II 回溯法
由于全排列 I 的交换 可能打乱顺序，重复解
这里使用visited方法
*/
class Solution {
    vector<int> list;
    void backtrace(vector<vector<int>>& res,const vector<int>& nums,vector<bool>& used,int index){
        if(index==nums.size()){
            res.push_back(list);
        }
        
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
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res;
        sort(nums.begin(),nums.end());
        vector<bool> used(nums.size(),false);

        backtrace(res,nums,used,0);
        return res;
    }
};