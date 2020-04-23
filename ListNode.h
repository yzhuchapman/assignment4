#ifndef __LISTNODE_H
#define __LISTNODE_H
using namespace std;

template <typename T>
class ListNode
{
	public:

		T* data;
		ListNode* next;
		ListNode* prev;

		ListNode()
		{
			data = NULL;
			next = NULL;
			prev = NULL;
		}

		ListNode(T* value)
		{
			data = value;
			next = NULL;
			prev = NULL;
		}

		~ListNode()
		{
			//delete value;
		}
};
#endif
