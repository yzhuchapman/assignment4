#include "Window.h"
#include "Student.h"

#include <iostream>

using namespace std;

Window::Window()
{
	idleTime = 0;
	longestIdleTime = 0;
	student = NULL;
}

Window::~Window()
{

}	

void Window::assignPatient(Student* stud, int time)
{
	if(stud == NULL) student = NULL;
	else
	{
		student = stud;
		idleTime = 0;
		patientCameIn = time;
		patientLeaveTime = stud->getVisitTime() + time;
	}
}

Student* Window::getPatient()
{
	if(!idling()) return student;
	return NULL;
}

int Window::patientExitTime()
{
	if(!idling()) return patientLeaveTime;
	else return -1;
}

int Window::getLongestIdleTime()
{
	return longestIdleTime;
}

int Window::getIdleTime()
{
	return idleTime;
}

bool Window::updateIdleTime()
{
	bool waiting = idling();
	if(waiting)
	{
		idleTime++;
		if(idleTime > longestIdleTime) longestIdleTime = idleTime;
	}

	return waiting;
}

bool Window::idling()
{
	if(student != NULL) return false;
	return true;
}