//找零 主要是
//1 只会有5 10两种零钱
//2 只需要找5 或 15
class Solution {
public:
    bool lemonadeChange(vector<int>& bills) {
        int m5=0,m10=0;
        for(const auto& b :bills){
            if(b==5)m5++;
            else if(b==10){
                m10++;
                m5--;
            }else{//15
                if(!m10){
                    m5-=3;
                }else{
                    m10--;
                    m5--;
                }
            }
            if(m5<0)return false;
        }
        return true;
    }
};