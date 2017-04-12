/**
功能:输入一个链表，从尾到头打印链表每个节点的值。
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
#include <stdio.h>
#include <assert.h>

typedef struct ListNode
{
	int val;
	struct ListNode *next;
}ListNode;

void printListFromTailToHead(ListNode* head)
{
	assert(head);
	if (head->next)
		printListFromTailToHead(head->next);
	
	printf("val = %d\n", head->val);
}

int main()
{	
	ListNode node1;
	ListNode node2;
	ListNode node3;
	ListNode node4;

	node1.next = &node2;
	node2.next = &node3;
	node3.next = &node4;
	node4.next = NULL;

	node1.val = 1;
	node2.val = 2;
	node3.val = 3;
	node4.val = 4;

	printListFromTailToHead(&node1);

	return 0;
}
