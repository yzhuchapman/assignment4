#ifndef __GENQUEUE_H
#define __GENQUEUE_H
#include "DoublyLinkedList.h"
#include <iostream>

using namespace std;
template <typename T>
class GenQueue
{
	public:
		GenQueue()
		{
			front = 0;
			myQueue = new DoublyLinkedList<T>();
		}

		~GenQueue()
		{
			delete myQueue;
		}

		void insert(T* elem)
		{
			myQueue->insertBack(elem);
		}

		T* peek()
		{
			return myQueue->seeFront();
		}

		T* remove()
		{
			return myQueue->removeFront();
		}

		int getSize()
		{
			return myQueue->getSize();
		}

		T* allElements()
		{
			return myQueue->allElements();
		}

		bool isEmpty()
		{
			return getSize() == 0;
		}

	private:
		int front;
		DoublyLinkedList<T>* myQueue;
};
#endif
