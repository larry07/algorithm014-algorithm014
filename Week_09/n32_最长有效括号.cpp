
//结合类似栈的cnt操作，使得在有效情况下 ，统计多少对
int longestValidParentheses(string s) {
	int maxCnt=0,n=s.size();
	int cnt=0;
	vector<int> dp(n+1,0);
	for(int i=1;i<=n;i++){
		char c = s[i-1];
		if(c=='('){
			cnt++;
		}else{
			if(cnt!=0){
				cnt--;
				dp[i]=dp[i-1]+1;
				dp[i]+=dp[i-2*dp[i]];//i从1开始  则 i-2*dp[i]>=0
				maxCnt=max(maxCnt,dp[i]);
			}
		}
	}
	return 2*maxCnt;
}

//dp 仍是利用了对称性 求的不是多少对
int longestValidParentheses(string s) {
	int maxans = 0, n = s.length();
	vector<int> dp(n, 0);
	for (int i = 1; i < n; i++) {
		if (s[i] == ')') {
			if (s[i - 1] == '(') {
				dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
			} else if (i - dp[i - 1] > 0 && s[i - dp[i - 1] - 1] == '(') {
				dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
			}
			maxans = max(maxans, dp[i]);
		}
	}
	return maxans;
}

//栈解法 栈底放入分割点位置 ~ 最后一个没有被匹配的右括号的下标
int longestValidParentheses(string s) {
    stack<int> stk;
    stk.push(-1);
    int res = 0;
    for(int i=0;i<s.size();i++){
        if(s[i] == '('){
            stk.push(i);
        }
        else{
            stk.pop();
            if (stk.empty()){
                stk.push(i);
            }
            else{
                res = max(res, i - stk.top());
            }
        }
    }
    return res;
}

/*
两遍遍历  计数左右括号个数，left,right
    左->右  ：当 ) 多于( 时，左右计数清零，当相等时，计算当前有效字符串长度
    右->左  ：当(  多于) 时，左右计数清零，当相等时，计算当前有效字符串长度
这样我们就能涵盖所有情况从而求解出答案
*/
int longestValidParentheses(string s) {
	int left = 0, right = 0, maxlength = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] == '(') {
			left++;
		} else {
			right++;
		}
		if (left == right) {
			maxlength = max(maxlength, 2 * right);
		} else if (right > left) {
			left = right = 0;
		}
	}
	left = right = 0;
	for (int i = (int)s.length() - 1; i >= 0; i--) {
		if (s[i] == '(') {
			left++;
		} else {
			right++;
		}
		if (left == right) {
			maxlength = max(maxlength, 2 * left);
		} else if (left > right) {
			left = right = 0;
		}
	}
	return maxlength;
}