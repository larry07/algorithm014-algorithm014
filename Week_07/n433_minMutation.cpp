
//最小基因变异
//双端BFS 参考别人的 和单词接龙非常像
int minMutation(string start, string end, vector<string>& bank) {
    unordered_set<string> dict(bank.begin(), bank.end());
    if (dict.find(end) == dict.end()) return -1;
    unordered_set<string> head{start}, tail{end}, *phead, *ptail;
	
    vector<char> letter = {'A', 'C', 'G', 'T'};
    int ladder = 1;

    while (!head.empty() && !tail.empty()) { // 当两个 set 都空时，才说明线索断了
        if (head.size() < tail.size()) { // 每次都选择较短的 set 进行搜索，可以保证考虑的情况尽量的少
            phead = &head;
            ptail = &tail;
        } else {
            phead = &tail;
            ptail = &head;
        }
        
        // 存储要进行扩散的下一层元素，在扩散完成后，会成为新的 phead 指向的 set
        unordered_set<string> temp; // 当temp最终为空时，就是线索断了
        for (auto it = phead->begin(); it != phead->end(); it++) {
            string word = *it;
            for (int i = 0; i < word.size(); i++) {
                char c = word[i];
                for (int k = 0; k < letter.size(); k++) {
                    word[i] = letter[k];
                    if (ptail->find(word) != ptail->end()) {
                        return ladder; // 当前phead中的元素已经出现在了ptail中，即找到了
                    }
                    if (dict.find(word) != dict.end()) {
                        temp.insert(word); // 将可能的选择 insert 到 temp
                        dict.erase(word); // 从 dict 中 erase，避免重复选择
                    }
                }
                word[i] = c; // 字符复原，下次再用
            }
        }
        ladder++;
        phead->swap(temp); // 相比直接赋值，swap 交换两个 set 的引用，速度更快
    }
    return -1;
}