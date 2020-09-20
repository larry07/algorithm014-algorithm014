
/** 621 任务调度器
贪心
n + 1 个任务为一轮，如示例，好处是同一轮中一个任务最多只能被安排一次，且正好能符合冷却时间
A -> B -> (待命) -> A -> B -> (待命) -> A -> B.
每一轮中，我们将当前的任务按照它们剩余的次数降序排序，并选择剩余次数最多的 n + 1 个任务依次执行
如果任务的种类 t 少于 n + 1 个，就只选择全部的 t 种任务，其余的时间空闲。
只有这样贪心地选尽量多种类的任务来消耗冷却时间，才能最大限度的减少待命的数量
*/
int leastInterval(vector<char>& tasks, int n) {
    int taskMap[26]={0};
    for(char c:tasks)
        taskMap[c-'A']++;
    sort(taskMap,taskMap+26);
    int time = 0;
    while(taskMap[25]>0){ //每次拿到剩余数量最多的一种任务
        int i = 0;
        while(i<=n){
            if(taskMap[25]==0)break;
            if(i<26 && taskMap[25-i] >0)
                taskMap[25-i]--;
            time++;
            i++;
        }
        sort(taskMap,taskMap+26);//保持[25]为当前剩余数量最多
    }
    return time;
}

/** 参考https://leetcode-cn.com/problems/task-scheduler/solution/tong-zi-by-popopop/
桶思想 建立n+1大小的桶，个数为任务数量最多的那个任务
以数量多的任务数为准，是因为数量少的任务都可以被安排到了其他任务的冷却期
	总排队时间 = (桶个数 - 1) * (n + 1) + 最后一桶的任务数
当冷却时间短，任务种类很多时，执行任务所需的时间，就是任务的数量，因为
每个任务之间都不存在空余时间，冷却时间已经被完全填满了，此时使用上面公式算的结果是偏小的，因此2种情况取大即可
*/
int leastInterval(vector<char>& tasks, int n) {
	int len=tasks.size();
	vector<int> vec(26);
	for(char c:tasks) ++vec[c-'A'];
	
	sort(vec.begin(),vec.end(),[](int& x,int&y){return x>y;});//逆序排序
	int cnt=1;
	while(cnt<vec.size()&&vec[cnt]==vec[0]) //最后一桶的数量
		cnt++;
	return max(len,cnt+(n+1)*(vec[0]-1) ); //两种情况
}
