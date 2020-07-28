#pragma once

#include <sstream>
using namespace std;

class FileName
{
public:
	FileName(char* fullPath);

	const char* GetFileName();
	const char* GetFileExtension();
	const char* GetFilePath();
	const char* GetFullFileName();
	const char* GetSafeFileName();

	void SetFileName(char* newName);
	void SetFileExtension(char* newExtension);
	void SetFilePath(char* newPath);


private:
	string fileName;
	string fileExtension;
	string filePath;
	string fullFileName;
	string safeFileName; //didnt know what else to call this
};
