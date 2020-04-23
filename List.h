#ifndef __LIST_H
#define __LIST_H
#include <iostream>

using namespace std;

template <typename T>
class List
{
	public:
		virtual void insertFront(T* data) = 0;
		virtual void insertBack(T* data) = 0;
		virtual T* seeFront() = 0;
		virtual T* seeBack() = 0;
		virtual T* removeFront() = 0;
		virtual T* removeBack() = 0;
		virtual bool contains(T* value) = 0;
		virtual T* remove(T* key) = 0;
		virtual unsigned int getSize() = 0;
		virtual bool isEmpty() = 0;
};
#endif
