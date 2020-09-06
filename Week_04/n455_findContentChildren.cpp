//分发饼干  贪心
//尽可能满足越多数量的孩子 所以先排序 从小胃口孩子开始
class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        if(s.empty()||g.empty())return 0;
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        
        int i=0,cnt=0,lenS=s.size();
        if(s.back()<g[0])return 0;
        
        for(auto x:g){
            while(i<lenS && s[i]<x)i++;
            if(i==lenS)break;
            i++;
            cnt++;
        }
        return cnt;
    }
};