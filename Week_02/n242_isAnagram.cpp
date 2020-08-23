//242. 有效的字母异位词
// 字母表作为哈希表
class Solution {
public:
    bool isAnagram(string s, string t) {
        int sLen = s.size();
        int tLen = t.size();
        if(sLen!=tLen)return false;
        
        int chrs[26]={0};
        for(int i=0;i<sLen;i++){
            chrs[s[i]-'a']++;
            chrs[t[i]-'a']--;
        }
        for(int i:chrs){
            if(i!=0)return false;
        }
        return true;
    }
};