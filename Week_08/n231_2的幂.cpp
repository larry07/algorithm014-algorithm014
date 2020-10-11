

//常规lgN  注意0不算
	if (n == 0) return false;
	while (n % 2 == 0) n /= 2;
	return n == 1;

//去除末位的1
//x & x-1
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n<=0)return false;
        long x=n;
        return (x & x - 1) == 0;
    }
};

//获取二进制中最右边的 1
//n & (-n)
  bool isPowerOfTwo(int n) {
    if (n == 0) return false;
    long x = n;
    return n & (-n) == n;
  }
