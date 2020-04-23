#ifndef __REGISTRAR_H
#define __REGISTRAR_H
#include "GenQueue.h"
#include "Student.h"
#include "Window.h"
#include "fileReader.h"

#include <vector>

using namespace std;

class Registrar
{
	public:
		Registrar();
		Registrar(string fileName);
		Registrar(int openWindows);
		~Registrar();

		void newStudent(Student* student);

		void runSimulation();

		void runAMinute();

		int idleWindow();
		bool stillPatients();

		double mean();
		double median();
	private:
		GenQueue<Student>* patientsWaiting;
		vector<Student*> patientsPassed;

		Window* windows;

		fileReader* file;

		int totalWindows;

		int minutesPassed;

		int longestWaitTime;
		double medianWaitTime;
		double meanStudentWaitTime;
		int studentWaitingOverTen;
		double meanIdleTime;
		int longestIdleTime;
		int idleWindowCounter;
		int idleTimeOverFive;
};
#endif
