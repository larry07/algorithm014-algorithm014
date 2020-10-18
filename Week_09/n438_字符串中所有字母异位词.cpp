
非常典型的滑动窗口题 ，可以作为模板记忆
vector<int> findAnagrams(string s, string p) {
	vector<int> res;
	int n = s.size(),m=p.size();
	if(n<m)return res;

	int needs[26]={0},win[26]={0};
	for(char c:p)needs[c-'a']++;

	int l =0,r=0;
	while(r<n){
		int curR = s[r]-'a';
		r++;
		win[curR]++;

		while(win[curR]>needs[curR]){ //有不同的 x>0 或 多出来的 就收缩左边 ，因此当之后r-l==m时，就是完全相同
			int curL =s[l]-'a';
			l++;
			win[curL]--;
		}

		if(r-l==m){
			res.push_back(l);
		}
	}
	return res;
}