#include "StringFile.h"

StringDefinition::StringDefinition(char* name, char* string)
{
	this->stringLength = strlen(string) + 1; //include our padding byte
	this->string = new char[((this->stringLength * 4) / 3) + (this->stringLength / 96) + 6]; //allow room for the in-place base64 encryption
	strcpy(this->name, name);
	strcpy(this->string, string);
}

StringDefinition::~StringDefinition()
{
	delete [] this->string;
}
char* StringDefinition::Name()
{
	return this->name;
}
char* StringDefinition::String()
{
	return this->string;
}

int StringDefinition::StringLength()
{
	return this->stringLength;
}


StringFile::StringFile(const char* path)
{
	this->fileStream = new ifstream(path, ifstream::in);
	if (!this->fileStream->is_open()) throw ("Failed to open file!");
}
StringFile::~StringFile()
{
	delete this->fileStream;
}
StringDefinition* StringFile::GetString()
{
	if (!fileStream->eof())
	{
		char name[256];
		char string[8192];

		if (fileStream->getline(name, 256).eof()) throw ("Unexpected end of file!");
		fileStream->getline(string, 8192);

		return new StringDefinition(name, string);
	}
	else
		return NULL;

}
