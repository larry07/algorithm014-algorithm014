
//搜索二维矩阵
//先定位行 后定位列  两次二分查找
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if(matrix.empty()||matrix[0].empty())return false;
        int m = matrix.size(),n=matrix[0].size();
        if(target<matrix[0][0]||target>matrix[m-1][n-1])return false;

        //0 1 2 4 target=3 返回第一个大于target的前一个 这里即4之前的2
        int l=0,r=m,row;
        while(l<r){
            int mid = l+(r-l)/2;
            int v = matrix[mid][0];
            if(v==target)
                return true;
            if(v<target){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        if(r==m||matrix[r][0]!=target)row=r-1;//定位行
        else{
            return true;
        }

        l=0,r=n;
        while(l<r){
            int mid = l+(r-l)/2;
            int v = matrix[row][mid];
            if(v==target)
                return true;
            if(v<target){
                l=mid+1;
            }else{
                r=mid;
            }
        }
        return !(r == n || matrix[row][r] != target);
    }
};

//官方  视为[0~m*n-1]的一维矩阵
class Solution {
  public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m = matrix.size();
    if (m == 0) return false;
    int n = matrix[0].size();

    // 二分查找
    int left = 0, right = m * n - 1;
    int pivotIdx, pivotElement;
    while (left <= right) {
      pivotIdx = (left + right) / 2;
      pivotElement = matrix[pivotIdx / n][pivotIdx % n];
      if (target == pivotElement) return true;
      else {
        if (target < pivotElement) right = pivotIdx - 1;
        else left = pivotIdx + 1;
      }
    }
    return false;
  }
};
