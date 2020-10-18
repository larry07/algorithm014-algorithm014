class Solution {
public:
    int myAtoi(string s) {
        int n=s.size();
        if(n==0)return 0;

        int ind = 0,res=0,flag = 1;;
        while(ind<n && s[ind]==' ')ind++;
        if(s[ind]=='-'){
            flag = -1;ind++;
        }else if(s[ind]=='+'){
            ind++;
        }

        while(isdigit(s[ind])){
            if(res<INT_MIN/10 ||
                (res==INT_MIN/10 && (s[ind]-'0')*flag<INT_MIN%10))return INT_MIN;
            if(res>INT_MAX/10 ||
                (res==INT_MAX/10 && (s[ind]-'0')*flag>INT_MAX%10))return INT_MAX;
            res=res*10+(s[ind]-'0')*flag;   //对 INT_MAX INT_MIN  包含符号计算
            ind++;
        }
        return res;
    }
};