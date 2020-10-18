class Solution {
public:
    int firstUniqChar(string s) {
        int hash[26]={0},n=s.size();
        for(char c:s){
            hash[c-'a']++;
        }

        for(int i=0;i<n;i++){
            if(hash[s[i]-'a']==1)
                return i;
        }
        return -1;
    }
};