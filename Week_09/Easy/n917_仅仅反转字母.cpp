
给定一个字符串 S，返回 “反转后的” 字符串，其中不是字母的字符都保留在原地，而所有字母的位置发生反转。

要点就是 跳过哪些 非字母的，进行reverse
class Solution {

public:
    string reverseOnlyLetters(string S) {
        int n = S.size();
        int l=0,r=n-1;
        while(l<r){
            while(l<r && !isalpha(S[l]))l++;
            while(l<r && !isalpha(S[r]))r--;
            swap(S[l],S[r]);
            l++,r--;
        }
        return S;
    }
};

	stack<char> st;//字母栈,需要字母时拿出来
	for(const char& c:S){
		if(isalpha(c))st.push(c);
	}
	for(char& c:S){
		if(isalpha(c)){
			c=st.top();st.pop();
		}
	}
	return S;