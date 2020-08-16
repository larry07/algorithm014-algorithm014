class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int snowSize=0,len=nums.size();
        for(int i=0;i<len;i++){
            if(nums[i]==0){
                snowSize++;
            }else if(snowSize>0){
                std::swap(nums[i],nums[i-snowSize]);
            }
        }
    }
};