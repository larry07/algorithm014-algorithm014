/** 
647 计数多少个回文子串，具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。

动态规划
dp[i][j]表示 [i ,j]字符串能不能构成回文串,那么dp[i][j] = dp[i +1][j - 1] && (s[i] == s[j])
*/

int countSubstrings(string s) {
    int n = s.size(), ans = 0;
    vector<vector<bool>> dp(n,vector<bool>(n,0));
    for(int j=0;j<n;j++){
        for(int i=0;i<=j;i++){
            if(s[i]==s[j] && (j-i<2 || dp[i+1][j-1])){ //[i+1,j-1]=> i+2<=j
                dp[i][j] = true;
                ans++;
            }
        }
    }
    return ans;
}
//中心拓展，枚举2n-1个可能的回文中心
int countSubstrings(string s) {
	int n = s.size(), ans = 0;
	for (int i = 0; i < 2 * n - 1; ++i) {
		int l = i / 2, r = i / 2 + i % 2; //r其实只是 l 或 l+1
		while (l >= 0 && r < n && s[l] == s[r]) {
			--l;
			++r;
			++ans;
		}
	}
	return ans;
}

//Manacher 算法
//利用对称性 用已知的回文串，增加起始匹配长度,复杂度降低至O(n)
class Solution {
public:
    int countSubstrings(string s) {
        int n = s.size();
        string t = "$#";
        for (const char &c: s) {
            t += c;
            t += '#';
        }
        n = t.size();
        t += '!';

        auto f = vector <int> (n);
        int iMax = 0, rMax = 0, ans = 0;
        for (int i = 1; i < n; ++i) {
            // 初始化 f[i]
            f[i] = (i <= rMax) ? min(rMax - i + 1, f[2 * iMax - i]) : 1;
            // 中心拓展
            while (t[i + f[i]] == t[i - f[i]]) ++f[i];
            // 动态维护 iMax 和 rMax
            if (i + f[i] - 1 > rMax) {
                iMax = i;
                rMax = i + f[i] - 1;
            }
            // 统计答案, 当前贡献为 (f[i] - 1) / 2 上取整
            ans += (f[i] / 2);
        }

        return ans;
    }
};
