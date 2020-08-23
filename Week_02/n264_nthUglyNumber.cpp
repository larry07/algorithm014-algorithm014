class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> dp(n,1);

        int p2,p3,p5,v2,v3,v5,v;
        p2=p3=p5=0;
        for(int i=1;i<n;i++){
            v2=dp[p2]*2;
            v3=dp[p3]*3;
            v5=dp[p5]*5;
            dp[i]=min(min(v2,v3),v5);
            if(dp[i]==v2)p2++;
            if(dp[i]==v3)p3++;
            if(dp[i]==v5)p5++;
        }
        return dp[n-1];
    }
};
	// 一个十分巧妙的动态规划问题
    // 1.我们将前面求得的丑数记录下来，后面的丑数就是前面的丑数*2，*3，*5
    // 2.但是问题来了，我怎么确定已知前面k-1个丑数，我怎么确定第k个丑数呢
    // 3.采取用三个指针的方法，p2,p3,p5
    // 4.p2指向的数字下一次永远*2，p3指向的数字下一次永远*3，p5指向的数字永远*5
    // 5.我们从2*p2, 3*p3 ,5*p5选取最小的一个数字，作为第k个丑数
    // 6.如果第K个丑数==2*p2，也就是说前面0-p2个丑数*2不可能产生比第K个丑数更大的丑数了，所以p2++
    // 7.p3,p5同理
    // 8.返回第n个丑数
	
	//小根堆方法 int存在问题：在到达第n个（弹出）之前需要多放很多数 造成溢出
	//int情况下失败  测试是多放了600多个数 遂改为long
	int nthUglyNumber(int n) {
        priority_queue<long,vector<long>,greater<long> >  q;//小根堆
        q.push(1);
        long last=0;
        while(n){
            if(q.top()!=last){
                last=q.top();
                q.pop();
                n--;
                q.push(last*2);
                q.push(last*3);
                q.push(last*5);
            }else{
                q.pop();
            }
        }
        return int(last);
    }