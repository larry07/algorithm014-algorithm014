557. 反转字符串中的单词 III
反转字符串中每个单词的字符顺序，同时仍保留空格和单词的初始顺序。

输入："Let's take LeetCode contest"
输出："s'teL ekat edoCteeL tsetnoc"

class Solution {
public:
    string reverseWords(string s) {
        int n = s.size();
        int begin,i=0;
        while(i<n){
            if(s[i]!=' '){
                begin=i;
                while(i<n && s[i]!=' ')i++;
                reverse(s.begin()+begin,s.begin()+i);   //end 开区间
            }else{
                i++;
            }
        }
        return s;
    }
};