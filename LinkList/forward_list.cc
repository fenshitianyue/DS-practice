//forward list
#include <iostream>
using namespace std;

typedef struct Node{
	int val;
	struct Node* next;
	Node(int data) : val(data), next(NULL){}
}* PNode;

class List{
public:
	List() :head(NULL){}
	void ListPush(int val);
	void ListPop();
	void ListErase();
	void ListPrint();
	~List(){
		ListErase();
	}
private:
	PNode head;
	int size;
};

void List::ListPush(int val){
	if (NULL == head){
		head = new Node(val);
	}
	else{
		PNode tmp = head;
		while (tmp->next != NULL){
			tmp = tmp->next;
		}
		tmp->next = new Node(val);
	}
	++size;
}

void List::ListPop(){
	if (NULL == head){
		return;
	}
	else if (NULL == head->next){
		delete head;
		head = NULL;
	}
	else{
		PNode tmp = head;
		PNode pre = NULL;
		while (tmp->next != NULL){
			pre = tmp;
			tmp = tmp->next;
		}
		delete tmp;
		pre->next = NULL;
	}
	--size;
}

void List::ListErase(){
	for (int i = 0; i < size; ++i){
		ListPop();
	}
}

void List::ListPrint(){
	for (PNode tmp = head; tmp != NULL; tmp = tmp->next){
		if (tmp->next)
			cout << tmp->val << ",";
		else
			cout << tmp->val << endl; 
	}
}

//test case
int main(){
	List nums;
	for (int i = 1; i <= 5; ++i){
		nums.ListPush(i);
	}
	/*nums.ListPop();
	nums.ListPop();
	nums.ListPop();
	nums.ListPop();
	nums.ListPop();*/
	nums.ListPrint();
	cin.get();
	return 0;
}