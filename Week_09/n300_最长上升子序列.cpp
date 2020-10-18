给定一个无序的整数数组，找到其中最长上升子序列的长度。

我们用dp[i]记录以nums[i]为结尾的最长上升子序列的长度
遇到nums[i]时，就向前查找比nums[i]小的数对应的 LIS ,拿到最大的 将[i] 加至末尾来更长
5 6 7 1 2 ,[i] = 8

int lengthOfLIS(vector<int>& nums) {
	if(nums.empty())return 0;
	int n = nums.size(),res=1;//empty
	vector<int> dp(n,1);
	for(int i=1;i<n;i++){
		for(int j=0;j<i;j++){
			if(nums[j]<nums[i])dp[i]=max(dp[i],dp[j]+1);
		}
		res=max(res,dp[i]);
	}
	return res;
}


//优化 只保存 相同长度下 值最小的那个[j]值 因此 该tails数组将是升序的
//因此可用 二分
int lengthOfLIS(vector<int>& nums) {
	int n = nums.size(),res=0;
	vector<int> tails(n);
	for(int num:nums){
		int l =0,r=res;
		while(l<r){ //[l,r)
			int m =(l+r)>>1;
			if(tails[m]<num)l=m+1;
			else r=m;
		}
		tails[r]=num;
		if(res == r)res++;
	}
	return res;
}