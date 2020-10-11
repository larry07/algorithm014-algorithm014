
//重复利用题目信息  数据范围 [0~1000]

vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    // 计数排序
    int count[1001];
    for (int i = 0; i < 1001; ++i)
        count[i] = 0;
    for (int i = 0; i < arr1.size(); ++i)
        ++count[arr1[i]];
    int idx = 0;
    for (int i = 0; i < arr2.size(); ++i)
        while (count[arr2[i]] > 0) {
            --count[arr2[i]];
            arr1[idx++] = arr2[i];
        }
    for (int i = 0; i < 1001; ++i)
        while (count[i] > 0) {
            --count[i];
            arr1[idx++] = i;
        }
    return arr1;
}

//桶排序  绕弯了
vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
    unordered_map<int,int> hash;
    int n1 = arr1.size(),n2 = arr2.size();
    vector<int> bucket(n2,0);
    for(int i=0;i<n2;i++){
        hash[arr2[i]]=i;
    }
        
    int j=0;
    for(int i=0;i<n1;i++){
        int v = arr1[i];
        if(hash.count(v)){
            bucket[hash[v]]++;
            swap(arr1[j],arr1[i]);
            j++;
        }
    }

    int k=0;
    for(int i=0;i<j;i++){
        if(bucket[k]==0){
            k++;
        }
        arr1[i]=arr2[k];
        bucket[k]--;
    }
    sort(arr1.begin()+j,arr1.end());
    return arr1;
}