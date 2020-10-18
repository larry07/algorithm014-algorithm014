
给定一个字符串 s 和一个整数 k，你需要对从字符串开头算起的每隔 2k 个字符的前 k 个字符进行反转。

如果剩余字符少于 k 个，则将剩余字符全部反转。
如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。


class Solution {
    void rev(string& s,int begin,int end){
        while(begin<end){
            swap(s[begin],s[end]);
            begin++;
            end--;
        }
    }
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        int i=0,r;
        while(1){
            r = n-i-1;
            if(r<k){
                rev(s,i,n-1);
                break;
            }else if(r<2*k){
                rev(s,i,i+k-1);
                break;
            }else{
                rev(s,i,i+k-1);
                i+=2*k;
                if(i>=n)break;
            }
        }
        return s;
    }
};