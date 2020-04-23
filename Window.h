#ifndef __WINDOW_H
#define __WINDOW_H
#include "Student.h"
#include <iostream>

using namespace std;

class Window
{
	public:
		Window();
		~Window();

		void assignPatient(Student* stud, int time);
		Student* getPatient();

		int patientExitTime();
		bool updateIdleTime();

		int getLongestIdleTime();
		int getIdleTime();
		bool idling();

	private:
		int id;
		int idleTime;
		int longestIdleTime;
		int patientCameIn;
		int patientLeaveTime;

		Student* student;
};
#endif
