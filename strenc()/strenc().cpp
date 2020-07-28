//MOVE: strenc.exe to C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin
//MOVE: strenc.lib to C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib

#include <vector>
#include <stdio.h>
#include <windows.h>
#include <fstream>

#include "StringFile.h"
#include "Base64.h"
#include "FileName.h"

using namespace std;

typedef vector<StringDefinition*> StringList;

StringList* ParseFile(StringFile* Parser)
{
	StringList* Strings = new StringList();
	StringDefinition* str = Parser->GetString();
	while (str != NULL)
	{
		Strings->push_back(str);
		str = Parser->GetString();
	}
	return Strings;
}

void EncodeStrings(StringList* RawStrings)
{
	Base64::ShuffleCharacterMap();

	for (int i = 0; i < RawStrings->size(); i++)
	{
		StringDefinition* CurrentString = (*RawStrings)[i];
		Base64::Encode(CurrentString->String(), CurrentString->StringLength());
	}
}


int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("No file specified.");
	}
	else
	{
		try
		{
			FileName CurrentFileName(argv[1]);

			StringFile Parser(CurrentFileName.GetFullFileName());
			
			StringList* RawStrings = ParseFile(&Parser);
			EncodeStrings(RawStrings);

			CurrentFileName.SetFileExtension(".h");

			//TODO: class this out
			ofstream output(CurrentFileName.GetFullFileName(), ios::trunc);

			output << "#ifndef " << CurrentFileName.GetSafeFileName() << "_KEY" << endl;
			{
				output << "	#define " << CurrentFileName.GetSafeFileName() << "_KEY \"" << Base64::Base64CharacterMap << "\"" << endl;

				int maxSize = 0;
				for (int i = 0; i < RawStrings->size(); i++)
				{
					maxSize = max(strlen((*RawStrings)[i]->String()), maxSize); //find the longest string so we know our static buffers size
					output << "	#define " << (*RawStrings)[i]->Name() << " GetDecryptedString(\"" << (*RawStrings)[i]->String() << "\")" << endl;
				}

        output << "#if (defined DEBUG || defined _DEBUG)" << endl;
				output << "#pragma comment(lib, \"strenc_d.lib\")" << endl;
        output << "#else" << endl;
        output << "#pragma comment(lib, \"strenc.lib\")" << endl;
        output << "#endif" << endl;
				output << "	void StrencDecode(char* buffer, const char* Base64CharacterMap);" << endl;

				output << "	const char* GetDecryptedString(const char* encryptedString)" << endl;
				output << "	{" << endl;
				output << "		static char string[" << maxSize + 1 << "];" << endl;
				output << "		strcpy(string, encryptedString);" << endl;
				output << "		StrencDecode(string, " << CurrentFileName.GetSafeFileName() << "_KEY);" << endl;
				output << "		return string;" << endl;
				output << "	}" << endl;

			}
			output << "#endif";
			

		}
		catch (char* str)
		{
			printf("ERROR: %s", str);
		}
	}

	return 0;
}

