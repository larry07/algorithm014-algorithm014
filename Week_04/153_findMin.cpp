class Solution {
public:
    int findMin(vector<int>& nums) {
        if(nums.empty())return -1;
        int n = nums.size();
        if(n==1||nums[0]<nums[n-1])return nums[0];//不保证一定拆为2个升序 {1,2} 

        int left = 0;
        int right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + ((right - left) >> 1);
            if (nums[mid] > nums[right])  //mid左 right右
                left = mid + 1;
            else
                right = mid;			 //right拉近到更左的右区
        }
        return nums[left];
    }
};

        int l=0,r=n-1,mid;
        while(l<=r){
            mid = (l+r)/2;
            int m=nums[mid];
            if(mid>0 && nums[mid-1]>m)return m;
            if(mid+1<n && m>nums[mid+1])return nums[mid+1];  //自己的繁琐了  只想到了边界条件

            if(nums[0]<m){//左半区
                l = mid+1;
            }else{
                r = mid-1;
            }
        }