
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>
using std::cout;
using std::endl;
using std::vector;
using std::stack;
using std::string;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* head=new ListNode();
        ListNode* temp=head;
        while(l1!=nullptr && l2!=nullptr){
            if(l1->val<l2->val){
                temp->next=l1;
                l1=l1->next;
            }else{
                temp->next=l2;
                l2=l2->next;
            }
            temp=temp->next;
        }
        if(l1==nullptr)temp->next=l2;
        else if(l2==nullptr)temp->next=l1;
        temp=head->next;
        delete head;
        return temp;
    }
};

int main() {
    ListNode* h1=new ListNode(0);
    ListNode* h2=new ListNode(1);
    ListNode* t1=h1,*t2=h2;
    for (int i = 2; i < 11; ++i) {
        if(i%2==0){
            t1->next=new ListNode(i);
            t1=t1->next;
        }else{
            t2->next=new ListNode(i);
            t2=t2->next;
        }
    }

	Solution sol;
    ListNode* p= sol.mergeTwoLists(h1,h2);
    while(p){
        cout<<p->val<<"\t";
        p=p->next;
    }

    return 0;
}
