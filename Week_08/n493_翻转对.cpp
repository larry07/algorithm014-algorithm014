
/*
给定一个数组 nums ，如果 i < j 且 nums[i] > 2*nums[j] 我们就将 (i, j) 称作一个重要翻转对。
你需要返回给定数组中的重要翻转对的数量

*/

//归并排序 同时比较 所有的 nums[i]>2LL * nums[j]
class Solution {
    int cnt=0;
    vector<int> tmp;
//[l mid] [mid+1 r]
    void merge(vector<int>& nums,int l,int mid,int r){
        for(int i=l;i<=r;i++)tmp[i]=nums[i];
        int i=l,j=mid+1;

        while(i<=mid){//只看 [i]>2*[j]
            while(j<=r && (nums[i]>2LL * nums[j])){ //防止溢出
                cnt+=(mid-i+1);
                j++;
            }
            i++;
        }

        i=l,j=mid+1;
        for(int k=l;k<=r;k++){
            if(i>mid)
                nums[k] = tmp[j++];
            else if(j>r||tmp[i]<tmp[j])
                nums[k] = tmp[i++];
            else
                nums[k] = tmp[j++];
        }
        
    }

    void mergeSort(vector<int>& nums,int l,int r){
        if(l>=r)return;
        int mid =(l+r)>>1;
        mergeSort(nums,l,mid);
        mergeSort(nums,mid+1,r);
        
        //-6 <-4 但-6 > -8(-4的两倍) 所以不能用 if(nums[mid]>=nums[mid+1])
            merge(nums,l,mid,r);
    }
public:
    int reversePairs(vector<int>& nums) {
        tmp.resize(nums.size());
        mergeSort(nums,0,nums.size()-1);
        return cnt;
    }
};


//树状数组 ...

