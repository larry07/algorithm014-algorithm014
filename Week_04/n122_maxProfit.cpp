class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int len=prices.size();
        if(len<=1)return 0;
        
        int res=0;
        int curMin=prices[0];
        for(int i=1;i<len;i++){
            if(prices[i-1]>prices[i]){ //寻找递增序列的右边界 找到了最小值
                res+=(prices[i-1]-curMin);
                curMin=prices[i];
            }
        }
        //递增到最后 没右 小值情况
        if(curMin<prices[len-1])res+=(prices[len-1]-curMin);
        return res;
    }
};

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res=0,n=prices.size();
        for(int i=1;i<n;i++){
            if(prices[i]>prices[i-1])  //只计利润
                res+=(prices[i]-prices[i-1]);
        }
        return res;
    }
};