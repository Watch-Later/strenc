#pragma once

#include <iostream>
#include <fstream>

using namespace std;

class StringDefinition
{
public:
	StringDefinition(char* name, char* string);
	~StringDefinition();

	char* Name();
	char* String();
	int StringLength();

private:
	int stringLength;
	char name[256];
	char* string;
};

class StringFile
{
public:
	StringFile(const char* path);
	~StringFile();

	StringDefinition* GetString();

private:
	ifstream* fileStream;
};
