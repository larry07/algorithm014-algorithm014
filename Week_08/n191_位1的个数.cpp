
//191 位1的个数

//方法1  逐位查看
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int cnt=0;
        for(int i=0;i<32;i++)
            if(n&1<<i)cnt++;     //移位优先级高于&
        return cnt;
    }
};

//方法2  使用  n&n-1  每次消去最低位的1
int hammingWeight(int n) {
    int sum = 0;
    while (n != 0) {
        sum++;
        n &= (n - 1);
    }
    return sum;
}
