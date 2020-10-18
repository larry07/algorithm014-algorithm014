
/*
如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。
所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。
*/

//本来只用了一个hash表 但遇到 ab  aa 或 aa ab 总出错 因为总出现哈希不存在去赋值的情况，但反映射已经有了
//因为它们是相互的映射!!!
bool isIsomorphic(string s, string t) {
	int hashA[128]={0},hashB[128]={0};
	int n = s.size();
	for(int i=0;i<n;i++){
		if(hashA[s[i]]==0 && hashB[t[i]]==0){
			hashA[s[i]] = t[i];
			hashB[t[i]] = s[i];
		}else if(hashA[s[i]]){
			if(hashA[s[i]]!=t[i])return false;
		}else{
			if(hashB[t[i]]!=s[i])return false;
		}
	}
	return true;
}

//另外两种

/*
s[].find(char a):返回字符a第一次出现在数组s中的下标
例子：egg add 分别返回结果是011 011
foo bar 分别返回结果是011 012
paper title分别返回结果是01034 01034
*/
bool isIsomorphic(string s, string t) {
	if(s.size()==0 && t.size()==0) return true;

	for(int i=0; i<s.size(); i++){
		if(s.find(s[i]) != t.find(t[i])) return false;
	}
	return true;
}

//找一个第三方来解决，即，按照字母出现的顺序，把两个字符串都映射到另一个集合中。就像两种不同语言的人通过翻译转换为国际通用语言后，可以交流一样
//为了方便，我们也可以将当前字母直接映射为当前字母的下标加 1
//因为 0 是我们的默认值，所以不能直接赋值为下标，而是「下标加 1」
bool isIsomorphic(string s, string t) {
	int m1[256] = {0}, m2[256] = {0}, n = s.size();
	for (int i = 0; i < n; ++i) 
	{
		if (m1[s[i]] != m2[t[i]]) return false;
		m1[s[i]] = i + 1;
		m2[t[i]] = i + 1;
	}
	return true;
}
