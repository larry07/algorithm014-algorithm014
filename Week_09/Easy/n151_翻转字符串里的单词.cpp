

给定一个字符串，逐个翻转字符串中的每个单词。
说明：

	无空格字符构成一个 单词 。
	输入字符串可以在前面或者后面包含多余的空格，但是反转后的字符不能包括。
	如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。



class Solution {
public:
    string reverseWords(string s) {
        // reverse(s.begin(),s.end());

        int n=s.size(),end;
        int i=n-1;
        string res;
        while(i>=0){
            if(s[i]!=' '){
                end=i;
                while(i>=0 && s[i]!=' ')i--;
                
                if(!res.empty())res+=" ";
                res+=s.substr(i+1,end-i);
            }else{
                i--;
            }
        }

        return res;
    }
};
