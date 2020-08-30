
/*
全排列 回溯法
不使用visited /isValid 方法 ，而是以first 将题目给定的 n 个数的数组 nums[] 划分成左右两个部分，左边的表示已经填过的数，右边表示待填的数

*/
class Solution {
public:
    void backtrack(vector<vector<int>>& res, vector<int>& nums, int first, int len){
        if (first == len) {
            res.emplace_back(nums);
            return;
        }
        
        for (int i = first; i < len; ++i) {
            if(i==first)backtrack(res,nums,first+1,len);
            else{
                swap(nums[first],nums[i]);
                backtrack(res,nums,first+1,len);
                swap(nums[first],nums[i]);
            }    
        }

    }
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int> > res;
        backtrack(res, nums, 0, (int)nums.size());
        return res;
    }
};