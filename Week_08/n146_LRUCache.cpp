

//使用list 简化双向链表操作 区别在于需要删除旧迭代器 添加新迭代器 
class LRUCache {
    list<pair<int,int>> data;
    unordered_map<int,list<pair<int,int>>::iterator> cache;
    int capacity;
public:
    LRUCache(int capacity):capacity(capacity) {
    }
    
    int get(int key) {
        auto it =cache.find(key);
        if(it==cache.end())
            return -1;

        auto node = *it->second;//pair
        data.erase(it->second);//删除迭代器 就是删掉对应元素
        data.push_front(node);

        // cache.erase(key);
        cache[key]=data.begin();
        return node.second;     // . 而不是 ->
    }
    
    void put(int key, int value) {
        auto it =cache.find(key);
        if(it==cache.end()){
            if(data.size()>=capacity){
                cache.erase(data.back().first);//2句有顺序
                data.pop_back();
            }
        }else{
            data.erase(it->second);
        }
        //不管是否存在 原元素已经不重要了
        data.push_front(make_pair(key,value));
        cache[key]=data.begin();
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
 
 // 常规双向链表  需要自己写 删除和添加结点的方法
 struct Node{
    int key,value;
    Node* prev;
    Node* next;
    Node():key(),value(),prev(nullptr),next(nullptr){}
    Node(int k,int v):key(k),value(v),prev(nullptr),next(nullptr){}
};

//这里 head 指向最常访问节点
class LRUCache{
private:
    unordered_map<int,Node*>cache;//<key,Node*>important!!!
    Node* head;//dummy 假人 虚设
    Node* tail;
    int capacity;//容量
    int size;    //实际使用

public:
    LRUCache(int _capacity):capacity(_capacity),size(0){
        //使用 伪头部 和 伪尾部 节点
        head=new Node();
        tail=new Node();
        head->next=tail;
        tail->prev=head;
    }

    void removeNode(Node *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(Node *node) {
        removeNode(node);
        addToHead(node);
    }

    void addToHead(Node *node) {
        head->next->prev=node;
        node->next=head->next;
        head->next=node;
        node->prev=head;
    }

    Node *removeTail() {
        Node* node=tail->prev;
        removeNode(node);
        return node;
    }

    int get(int key){
        if(!cache.count(key))
            return -1;

        Node* node=cache[key];//key存在 则先通过哈希表定位 再移动到头部
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value){
        if(!cache.count(key)){//key不存在 则创建一个新节点
            Node* node=new Node(key,value);
            cache[key]=node;//添加至哈希表
            addToHead(node);//添加至双向链表的头部
            ++size;
            if(size>capacity){
                Node* removed=removeTail();//删除尾部节点
                cache.erase(removed->key); //删除哈希表内对应项
                delete removed;
                --size;
            }
        }else{//key存在 先通过哈希表定位 再修改value 并移到头部
            Node* node=cache[key];
            node->value=value;
            moveToHead(node);
        }
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */