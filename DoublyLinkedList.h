#ifndef __DOUBLYLINKEDLIST_H
#define __DOUBLYLINKEDLIST_H
#include "List.h"
#include "ListNode.h"
#include <iostream>
using namespace std;

template <typename T>
class DoublyLinkedList : List<T>
{
	private:
		ListNode<T>* front;
		ListNode<T>* back;
		unsigned int size;

	public:
		DoublyLinkedList()
		{
			size = 0;
			front = NULL;
			back = NULL;
		}

		~DoublyLinkedList()
		{
			while(front != NULL) removeFront();
			//empty the content
		}

		void insertFront(T* data)
		{
			ListNode<T>* node = new ListNode<T>(data);
			if(isEmpty()) //check if list is empty
			{
			back = node;
		  }
			else
			{
				front->prev = node;
				node->next = front;
			}

			front = node;
			size++;
		}

		void insertBack(T* data)
		{
			ListNode<T>* node = new ListNode<T>(data);

			if(isEmpty()) front = node;
			else
			{
				back->next = node;
				node->prev = back;
			}

			back = node;
			size++;
		}

		T* seeFront()
		{
			if(front == NULL) return NULL;

			return front->data;
		}

		T* seeBack()
		{
			if(back == NULL) return NULL;

			return back->data;
		}

		T* removeFront()
		{
			if(front == NULL) return NULL;
			ListNode<T>* node = front;

			if(front->next == NULL) back = NULL;
			else front->next->prev = NULL;

			front = front->next;
			size--;
			node->next = NULL;
			T* temp = node->data;

			delete node;
			return temp;
		}

		T* removeBack()
		{
			if(back == NULL) return NULL;
			ListNode<T>* node = back;

			if(back->prev == NULL) back = NULL;
			else back->prev->next = NULL;

			back = back->prev;
			size--;
			node->prev = NULL;
			T* temp = node->data;

			delete node;
			return temp;
		}

		void printList()
		{
			ListNode<T>* curr = front;
			while(curr != NULL)
			{
				cout << curr->data << endl;
				curr = curr->next;
			}
		}

		bool contains(T* value)
		{
			if(find(value) > -1) return true;

			return false;
		}

		int find(T* value)
		{
			int id = -1;
			ListNode<T>* current = front;

			while(current != NULL)
			{
				id++;

				if(current->data == value) break;
				else current = current->next;
			}

			if(current == NULL) return -1;
			else return id;
		}

		T* remove(T* val)
		{
			ListNode<T>* current = front;

			while(current->data != val)
			{
				current = current->next;
				if(current == NULL) return NULL;
			}

			if(current == front) front = current->next;
			else current->prev->next = current->next;

			if(current == back) back = current->prev;
			else current->next->prev = current->prev;


			current->next = NULL;
			current->prev = NULL;
			size--;

			T* temp = current->data;

			delete current;
			return temp;
		}

		unsigned int getSize()
		{
			return size;
		}

		bool isEmpty()
		{
			if(size == 0) return true;

			return false;
		}

		T* allElements()
		{
			T* allElem = new T[size];

			int i = 0;
			ListNode<T>* curr = front;
			while(curr != NULL)
			{
				allElem[i] = curr;
				i++;
				curr = curr->next;
			}

			return allElem;
		}
};
#endif
