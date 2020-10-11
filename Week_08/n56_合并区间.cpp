

//给出一个区间的集合，请合并所有重叠的区间。

//排序+指针
//排序后,很容易可以将有重叠部分的区间 "合并/拓展到一起"
vector<vector<int>> merge(vector<vector<int>>& intervals) {
	sort(intervals.begin(), intervals.end());
	int n = intervals.size();

	vector<vector<int>> res(n,vector<int>(2));
	int idx = -1;
	for(auto& v:intervals){
		if(idx==-1 || v[0]>res[idx][1])//新的区间开始
			res[++idx] = v;
		else
			res[idx][1] = max(res[idx][1],v[1]);
	}
	res.resize(idx+1);
	return res;
}



//本题 思路上容易的地方在于 区间合并的条件比较简单
//将合并后 不用的区间置为 used,最后拿出来非used的数组 也就是合并后的数组,就可以了
//最后使用预分配数组空间赋值，比逐个push_back要快很多
class Solution {
    unordered_map<int,int> used;//合并过的 为空的

    //[i][j]  =>  [j]
    bool merge(vector<vector<int>>& intervals,int i,int j){
        if(intervals[i][1]<intervals[j][0] || intervals[i][0]>intervals[j][1])
            return false;
        intervals[j][0]=min(intervals[i][0],intervals[j][0]);
        intervals[j][1]=max(intervals[i][1],intervals[j][1]);
        used[i]=1;
        return true;
    }
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int n = intervals.size();
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(merge(intervals,i,j))break;
            }
        }
        vector<vector<int>> res(n-used.size());
        for(int i=0,j=0;i<n;i++){
            if(!used.count(i))res[j++]=intervals[i];
        }
        return res;
    }
};