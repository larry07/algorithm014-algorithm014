
/*利用动态规划，转换成子问题
dp[i] str[0...i]的译码方法总数
使用字符确实比较麻烦，很容易写的很繁琐
s[i]='0' 
	则看[i-1]是否是'1'或'2'，才会有效，dp[i]=dp[i-2] 否则无效 return0
否则：
	需要看当前与前一个（下一个那种还要判断越界）能不能构成有效两位数，不能时，译码数是不变的
	s[i-1]='1'  或  s[i-1]='2' && '1'<=s[i]<='6'
		dp[i] = dp[i-1] +dp[i-2]
*/
int numDecodings(string s) {
    if (s[0] == '0') return 0;
    int pre = 1, curr = 1;//dp[-1] = dp[0] = 1
    for (int i = 1; i < s.size(); i++) {
        int tmp = curr;
        if (s[i] == '0')
            if (s[i - 1] == '1' || s[i - 1] == '2') curr = pre;
            else return 0;
        else if (s[i - 1] == '1' || (s[i - 1] == '2' && s[i] >= '1' && s[i] <= '6'))
            curr = curr + pre;
        pre = tmp;
    }
    return curr;
}

//C++的string比较，正好就是我们需要的，直接使用substr()方法获得2字符，以下未空间压缩，比较直观
class Solution {
public:
    int numDecodings(string s) {
        int n = s.size();
        if(n==0)return 0;
        if(s[0]=='0')return 0;

        vector<int> dp(n+1,0);  //要有dp[-1] 整体右移
        dp[0] =dp[1] =1;        //dp[i]表示 [0 i)一共 i 个,最大为 n
        
        string tmp;
        for(int i =2;i<=n;i++){
            if(s[i-1]!='0')
                dp[i]+=dp[i-1];         //跨1步
            tmp =s.substr(i-2,2);       //跨2步
            if(tmp>="10" && tmp<="26")
                dp[i]+=dp[i-2];         //所以dp[0]=1
        }
        return dp[n];
    }
};