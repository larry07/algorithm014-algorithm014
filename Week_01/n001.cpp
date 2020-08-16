

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        int len=nums.size();
        if(len<=1)return {};
        unordered_map<int,int> aux;
        
        for(int i=0;i<len;i++){
            int com=target-nums[i];
            if(aux.count(nums[i])){
                return {aux[nums[i]],i};
            }
            aux.insert(make_pair(com,i));
        }
        return {};
    }
};