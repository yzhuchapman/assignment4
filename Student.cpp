#include "Student.h"

#include <iostream>

using namespace std;

Student::Student()
{

}

Student::Student(int visTime, int comeAt)
{
	visitTime = visTime;
	comeAtTime = comeAt;
	waitTime = 0;
}

Student::~Student()
{

}	

int Student::getVisitTime()
{
	return visitTime;
}

int Student::getComeAt()
{
	return comeAtTime;
}

int Student::getWaitTime()
{
	return waitTime;
}

void Student::setWaitTime(int minuteIn)
{
	waitTime = minuteIn - comeAtTime;
}

void Student::toString()
{
	cout << "Patient came at " << comeAtTime << " and needs " << visitTime << endl;
}