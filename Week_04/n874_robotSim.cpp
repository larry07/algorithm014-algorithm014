
//方向处理太厉害了  自己的太麻烦 没用set 自己处理find很麻烦
//绝对方向使用时钟角度 0 90 180 270 ，分别用 0 1 2 3表示
//左转90就是右转270，所以使用了取余   dir = (dir+3)%4
//commands = [4,-1,4,-2,4], obstacles = [[2,4]]

class Solution {
public:
    int robotSim(vector<int>& commands, vector<vector<int>>& obstacles) {
        int dx[4] = {0, 1, 0, -1};
        int dy[4] = {1, 0, -1, 0};
        int x = 0, y = 0, di = 0;

        set<pair<int, int>> obstacleSet;  //set优化  可以使用find 方法，所以比自己写好多了
        for (const auto& obstacle: obstacles)
            obstacleSet.insert(make_pair(obstacle[0], obstacle[1]));

        int ans = 0;
        for (int cmd: commands) { //命令 只有3种
            if (cmd == -2)
                di = (di + 3) % 4;
            else if (cmd == -1)
                di = (di + 1) % 4;
            else {
                for (int k = 0; k < cmd; ++k) {//一次只走di方向上的 1位移
                    int nx = x + dx[di];
                    int ny = y + dy[di];
                    if (obstacleSet.find(make_pair(nx, ny)) != obstacleSet.end()) 
                        break;
                    x = nx;
                    y = ny;
                    ans = max(ans, x*x + y*y);//移动1位移都要计一次  因为方向可能是接近原点的
                }
            }
        }

        return ans;
    }
};