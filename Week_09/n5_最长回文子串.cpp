
要求回文串至少长度2

//中心拓展法 参考执行用时最快速解法
string longestPalindrome(string s) {
	int start = 0, end = 0, len = 0, maxI = 0, i = 0, n = s.size();
	while(i<n) {
		start = i, end = i;
		while(end+1<n && s[end] == s[end+1]) end++ ;//重复元素直接后移，直到[end]!=[end+1]
		i = end + 1;
		//先保证了[start,end]是一个回文串（全重复元素），再拓展
		while(start-1>=0 && end+1<n && s[end+1] == s[start-1]) {
			start-- ;
			end++ ;
		}
		if(end - start + 1 > len) {
			len = end - start + 1;
			maxI = start;
		}
	}
	return s.substr(maxI, len);
}

//Manacher
string longestPalindrome(string s) {
	if(s.empty())return "";
	int n = s.size();

	string t="$#";
	for(const char& c:s){
		t+=c;
		t+='#';
	}
	n=t.size();
	t+='!';

	int r=0,c=0,maxI=0,maxLen=1;
	vector<int> f(n);
	for(int i=1;i<n;i++){
		f[i]=i<r?min(r-i+1,f[2*c-i]):1;
		while(t[i+f[i]]==t[i-f[i]])f[i]++;

		if(i+f[i]-1>r){
			c=i;
			r=i+f[i]-1;
		}
		if(f[i]>maxLen){
			maxLen=f[i];
			maxI=i;
		}
	}
	maxLen --;
	maxI = maxI/2-1;//这个maxI是中心位置 中左  如"ccc" 此时maxI=1 maxLen=3
	maxI -=(maxLen/2);
	if(maxLen%2==0)maxI++;

	return s.substr(maxI,maxLen);
}