#ifndef __STUDENT_H
#define __STUDENT_H
#include <iostream>

using namespace std;

class Student
{
	public:
		Student();
		Student(int visTime, int comeAt);
		~Student();

		int getVisitTime();
		int getComeAt();
		int getWaitTime();
		void setWaitTime(int minuteIn);

		void updateWaitTime();

		void toString();

	private:
		int visitTime;
		int waitTime;
		int comeAtTime;

		bool atWindow;
};
#endif
