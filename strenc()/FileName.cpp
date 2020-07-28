#include "FileName.h"

FileName::FileName(char* fullPath)
{
	string codeFilePath = fullPath;

	int lastBackslah = codeFilePath.find_last_of('\\');
	int lastPeriod = codeFilePath.find_last_of('.');

	this->fileName = codeFilePath.substr(lastBackslah + 1, lastPeriod - lastBackslah - 1);
	this->fileExtension = codeFilePath.substr(lastPeriod);
	this->filePath = codeFilePath.substr(0, lastBackslah+1);
}

const char* FileName::GetFileName()
{
	return this->fileName.c_str();
}
const char* FileName::GetFileExtension()
{
	return this->fileExtension.c_str();
}
const char* FileName::GetFilePath()
{
	return this->filePath.c_str();
}
const char* FileName::GetFullFileName()
{
	this->fullFileName = this->filePath + this->fileName + this->fileExtension;
	return this->fullFileName.c_str();
}
const char* FileName::GetSafeFileName()
{
	this->safeFileName = this->fileName;
	for(int i = 0; i < this->safeFileName.length(); i++)
	{
		if (this->safeFileName[i] == ' ')
			this->safeFileName[i] = '_';
		else
			this->safeFileName[i] = toupper(this->safeFileName[i]);
	}

	return this->safeFileName.c_str();
}

void FileName::SetFileName(char* newName)
{
	this->fileName = newName;
}
void FileName::SetFileExtension(char* newExtension)
{
	this->fileExtension = newExtension;
}
void FileName::SetFilePath(char* newPath)
{
	this->filePath = newPath;
}