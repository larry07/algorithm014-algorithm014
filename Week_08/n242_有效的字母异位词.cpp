

//哈希表
bool isAnagram(string s, string t) {
    int n = s.size();
    if(n!=t.size())return false;
    
    int hash[128]={0};
    for(int i=0;i<n;i++){
        hash[s[i]]++;
        hash[t[i]]--;
    }
    for(int i='a';i<='z';i++)
        if(hash[i]!=0)return false;
    return true;
}