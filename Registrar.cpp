#include "Registrar.h"
#include "Student.h"
#include "Window.h"
#include "GenQueue.h"
#include "fileReader.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

Registrar::Registrar()
{
	patientsWaiting = new GenQueue<Student>();
	windows = new Window[5];

	totalWindows = 5;
	minutesPassed = 0;

	for(int i = 0; i < totalWindows; i++)
	{
		windows[i] = Window();
	}
	longestWaitTime = 0;
	medianWaitTime = 0;
	meanStudentWaitTime = 0;
	studentWaitingOverTen = 0;
	meanIdleTime = 0;
	longestIdleTime = 0;
	idleWindowCounter = 0;
	idleTimeOverFive = 0;
}

Registrar::Registrar(string fileName)
{
	patientsWaiting = new GenQueue<Student>();

	file = new fileReader(fileName);

	if(file->isValid())
	{
		vector<string> data = file->readFile();

		int openWindows = 0;
		int currentTime = 0;
		int numStudents = 0;

		for(int i = 0; i < data.size(); i++)
		{
			if(i == 0) openWindows = stoi(data[i]);
			else
			{
				if(numStudents == 0)
				{
					currentTime = stoi(data[i]);
					numStudents = stoi(data[++i]);
				}else
				{
					patientsWaiting->insert(new Student(stoi(data[i]), currentTime));
					numStudents--;
				}
			}
		}

		windows = new Window[openWindows];

		totalWindows = openWindows;
		minutesPassed = 0;

		for(int i = 0; i < totalWindows; i++)
		{
			windows[i] = Window();
		}
		longestWaitTime = 0;
		medianWaitTime = 0;
		meanStudentWaitTime = 0;
		studentWaitingOverTen = 0;
		meanIdleTime = 0;
		longestIdleTime = 0;
		idleWindowCounter = 0;
		idleTimeOverFive = 0;
	}else
	{
		cout << "File " + fileName + " is not valid" << endl;
	}
}

Registrar::Registrar(int openWindows)
{
	patientsWaiting = new GenQueue<Student>();
	windows = new Window[openWindows];

	totalWindows = openWindows;
	minutesPassed = 0;

	for(int i = 0; i < totalWindows; i++)
	{
		windows[i] = Window();
	}

	longestWaitTime = 0;
	medianWaitTime = 0;
	meanStudentWaitTime = 0;
	studentWaitingOverTen = 0;
	meanIdleTime = 0;
	longestIdleTime = 0;
	idleWindowCounter = 0;
	idleTimeOverFive = 0;
}

Registrar::~Registrar()
{

}

void Registrar::newStudent(Student* student)
{
	patientsWaiting->insert(student);
}

void Registrar::runSimulation()
{
	if(file->isValid())
	{
		cout << "Starting simulation..." << endl;
		while(stillPatients()) runAMinute();

		cout << "Simulation done" << endl;

		for(int i = 0; i < totalWindows; i++)
		{
			if(windows[i].getLongestIdleTime() > longestIdleTime) longestIdleTime = windows[i].getLongestIdleTime();
			if(windows[i].getLongestIdleTime() > 5) idleTimeOverFive++;
			if(windows[i].getIdleTime() > 0)
			{
				idleWindowCounter++;
				meanIdleTime += windows[i].getIdleTime();
			}
		}

		medianWaitTime = median();
		meanStudentWaitTime = mean();
		meanIdleTime /= idleWindowCounter;

		for(int i = 0; i < patientsPassed.size(); i++)
		{
			if(patientsPassed[i]->getWaitTime() > longestWaitTime) longestWaitTime = patientsPassed[i]->getWaitTime();
			if(patientsPassed[i]->getWaitTime() > 10) studentWaitingOverTen++;
		}

		cout << "The mean student wait time is: " << meanStudentWaitTime << endl;
		cout << "The median student wait time is: " << medianWaitTime << endl;
		cout << "The longest student wait time is: " << longestWaitTime << endl;
		cout << "The number of students who waited over 10 minutes is: " << studentWaitingOverTen << endl;
		cout << "The mean window idle time is: " << meanIdleTime << endl;
		cout << "The longest window idle time is: " << longestIdleTime << endl;
		cout << "The number of windows with an idle time of more than five is: " << idleTimeOverFive << endl;

	}else cout << "Simulation closing" << endl;
}

void Registrar::runAMinute()
{
	minutesPassed++;

	cout << "On time " << minutesPassed << endl;
	int windowOpen = idleWindow();

	for(int i = 0; i < totalWindows; i++)
	{
		if(!windows[i].updateIdleTime())
		{
			if(windows[i].patientExitTime() == minutesPassed)
			{
				patientsPassed.push_back(windows[i].getPatient());
				windows[i].assignPatient(NULL,minutesPassed);
			}
		}else
		{
		}
	}

	while(patientsWaiting->peek() != NULL && patientsWaiting->peek()->getComeAt() <= minutesPassed)
	{
		if(windowOpen > -1)
		{
			patientsWaiting->peek()->setWaitTime(minutesPassed);

			meanIdleTime += windows[windowOpen].getIdleTime();
			idleWindowCounter++;
			windows[windowOpen].assignPatient(patientsWaiting->remove(),minutesPassed);
			windowOpen = idleWindow();
		}else break;
	}
}

int Registrar::idleWindow()
{
	for(int i = 0; i < totalWindows; i++)
	{
		if(windows[i].idling()) return i;
	}

	return -1;
}

bool Registrar::stillPatients()
{
	if(!patientsWaiting->isEmpty()) return true;

	for(int i = 0; i < totalWindows; i++)
	{
		if(!(windows[i].idling())) return true;
	}
	return false;
}

bool sortingMethod(Student* stud1, Student* stud2)
{
	return stud1->getWaitTime() < stud2->getWaitTime();
}

double Registrar::mean()
{
	int size = patientsPassed.size();
	double total = 0;
	for(int i = 0; i < size; i++)
	{
		total += patientsPassed[i]->getWaitTime();
	}

	return static_cast<double>(total)/static_cast<double>(size);
}

double Registrar::median()
{
	int size = patientsPassed.size();

	if (size == 0) return 0;
	else if (size == 1) return patientsPassed[0]->getWaitTime();
	else
	{
		sort(patientsPassed.begin(), patientsPassed.end(), sortingMethod);
		if (size % 2 == 0) return static_cast<double>(patientsPassed[size / 2 - 1]->getWaitTime() + patientsPassed[size / 2]->getWaitTime()) / 2;
		else return patientsPassed[size / 2]->getWaitTime();
	}
}
