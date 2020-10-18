
给定一个非空字符串 s，最多删除一个字符。判断是否能成为回文字符串

要点:
	一旦不同，则必须进行删除操作，之后就必须判断结果
class Solution {
    bool valid(string s,int l,int r){
        int n = (l+r)/2;
        for(int i=l;i<=n;i++){
            if(s[i]!=s[r+l-i])return false;
        }
        return true;
    }
public:
    bool validPalindrome(string s) {
        int n =s.size();
        int l=0,r=n-1;
        while(l<r){
            if(s[l]==s[r]){
                l++;r--;
            }else{
                return valid(s,l+1,r)||valid(s,l,r-1);
            }
        }
        return true;
    }
};