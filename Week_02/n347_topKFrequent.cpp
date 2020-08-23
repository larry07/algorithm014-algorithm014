

//最小堆+只放入k个 调整lgK
class Solution {
	
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        vector<int > res(k);
        unordered_map<int,int> hash;
        for(const auto& x:nums)
            hash[x]++;
        priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > Q;
        for(auto x:hash){
            Q.push({x.second,x.first});
            if(Q.size()>k)Q.pop();
        }
        while(!Q.empty()){
            res[--k] = Q.top().second;//逆序  保持高频顺序
            Q.pop();
        }
        return res;
    }
};

//快排思想
class Solution {
    int partition(vector<pair<int,int> >& vec,int l,int r){
        int rd=rand()%(r-l+1)+l;
        swap(vec[l],vec[rd]);

        auto v=vec[l];
        int j=l;//[l+1 j]
        for(int i=l+1;i<=r;i++){
            if(vec[i].first>=v.first){
                swap(vec[i],vec[j+1]);
                j++;
            }
        }
        swap(vec[l],vec[j]);
        return j;
    }
    void quickSelect(vector<pair<int,int>>& nums,int l,int r,int k){
        if(l>=r)return;
        int pos = partition(nums,l,r);
        int n=pos-l+1;
        if(n==k)return;
        if(n>k)quickSelect(nums,l,pos-1,k);
        else quickSelect(nums,pos+1,r,k-n);
    }
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        srand((unsigned)time(NULL));
        unordered_map<int,int> hash;
        for (auto x:nums){
            hash[x]++;
        }
        vector<pair<int,int> > arr;
        for(auto x:hash){
            arr.push_back({x.second,x.first});
        }
        quickSelect(arr,0,arr.size()-1,k);

        vector<int> res;
        for(int i=0;i<k;i++){
            res.push_back(arr[i].second);
        }
        return res;
    }
};
//桶排序方法  用map作为桶 map结构最大优点：有序性
	vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> umap;
        for (const int &n: nums) {
            ++umap[n];
        }
        // 大的放前面，添加仿函数
        map<int, vector<int>, greater<int>> bucket;
        for(const auto &p : umap){
            bucket[p.second].push_back(p.first);
        }
        vector<int> res(k);
        int i = 0;
        for(const auto &p : bucket){
            for(const int &n : p.second){
                if(i >= k){
                    break;
                }
                res[i++] = n;
            }
        }
        return res;
    }