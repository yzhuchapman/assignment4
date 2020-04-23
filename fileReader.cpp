#include "fileReader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

fileReader::fileReader()
{
  //default constructor
}

fileReader::fileReader(string s)
{
	file = s;
	ifstream reading(file);
	if(reading) realFile = true;
	else realFile = false;

	lineNum = 0;

	std::string line;

	if(realFile)
	{
		while (getline(reading, line))
		{
			lines.push_back(line);
			lineNum++;
		}
	}
}

fileReader::~fileReader()
{
	lines.clear();
}

vector<string> fileReader::readFile()
{
	return lines;
}

bool fileReader::isValid()
{
	return realFile;
}
