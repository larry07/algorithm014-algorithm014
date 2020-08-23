
//字母异位词分组
//哈希表  string->vector<string>
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string,vector<string>> ans;
        for(string s:strs){
            string key=s;
            sort(key.begin(),key.end());
            if(!ans.count(key))ans.insert(make_pair(key,vector<string>()));
            ans[key].push_back(s);
        }
        
        vector<vector<string>> vecs;
        for(auto& n:ans)
            vecs.push_back(n.second);
        return vecs;
    }
};


//优化value   用索引区分value 这样就不需要用vector<string>作为key了
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        int ind=0;
        unordered_map<string,int> ans;
        for(string s:strs){
            string key=s;
            sort(key.begin(),key.end());
            if(ans.count(key)){
                res[ans[key]].push_back(s);
            }else{
                vector<string> v(1,s);
                res.push_back(v);
                ans[key]=ind++;
            }
        }
        return res;
    }
};