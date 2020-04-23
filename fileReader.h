#ifndef __FILEREADER_H
#define __FILEREADER_H
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
//{
class fileReader
{
	public:
		fileReader();
		fileReader(string s);
		~fileReader();

		vector<string> readFile();

		bool isValid();

	private:
		vector<string> lines;
		string file;
		int lineNum;

		bool realFile;
};
#endif
