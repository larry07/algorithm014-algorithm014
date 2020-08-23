//001 两数之和
//hash表解法
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int,int> hash;
        for(int i =0 ;i<nums.size();i++){
            int com = target - nums[i];
            if(hash.count(com))
                return {hash[com],i};
            hash.insert({nums[i],i});
        }
        return {};
    }
};

//暴力
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int len=nums.size();
        for (int i = 0; i <len-1; ++i) {
            int other=target-nums[i];
            for (int j = i+1; j < len; ++j) {
                if(nums[j]==other){
                    return {i,j};
                }
            }
        }
        return {};
    }
};