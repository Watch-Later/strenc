//MOVE: strenc.exe to C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\bin
//MOVE: strenc.lib to C:\Program Files (x86)\Microsoft Visual Studio 9.0\VC\lib

#include <sstream>
#include <windows.h>
#include <algorithm>

void StrencEncode(char* buffer, int size, const char* Base64CharacterMap)
{
	int n = 0;
	char one, two, three, four;
	std::stringstream result;

	for (int x = 0; x < size; x += 3)
	{
		n = buffer[x] << 16;
		if (x < size - 1)
		{
			n += buffer[x + 1] << 8;
			if (x < size - 2)
				n += buffer[x + 2];
		}

		one = (char)(n >> 18) & 63;
		two = (char)(n >> 12) & 63;
		three = (char)(n >> 6) & 63;
		four = (char)n & 63;

		result << Base64CharacterMap[one];
		result << Base64CharacterMap[two];

		if (x < size - 1)
		{
			result << Base64CharacterMap[three];
			if (x < size - 2)
				result << Base64CharacterMap[four];
		}
	}

	for (int pad_count = 0; pad_count < result.str().size() % 4; pad_count++)
		result << '=';

	strcpy(buffer, result.str().c_str());
}

void StrencDecode(char* buffer, const char* Base64CharacterMap)
{
    char decodedMap[256];
    for (int i = 0; i <= 63; i++)
        decodedMap[(int)Base64CharacterMap[i]] = i;
  

	int size = strlen(buffer);
	int decodedSize = (size + 3) / 4 * 3;
    char* temp = new char[decodedSize];
	memset(temp, 0, decodedSize);

    int bufferPosition = 0;
    for (int i = 0; i < size; i += 4, bufferPosition += 3)
    {
        temp[bufferPosition] = decodedMap[(int)buffer[i]] << 2;

        if (i < size - 1 && buffer[i + 1] != '=')
        {
            temp[bufferPosition] += (decodedMap[(int)buffer[i + 1]] >> 4) & 0x3;
            temp[bufferPosition + 1] = decodedMap[(int)buffer[i + 1]] << 4;

            if (i < size - 2 && buffer[i + 2] != '=')
            {
                temp[bufferPosition + 1] += (decodedMap[(int)buffer[i + 2]] >> 2) & 0xf;
                temp[bufferPosition + 2] = decodedMap[(int)buffer[i + 2]] << 6;

                if (i < size - 1 && buffer[i + 3] != '=')
                    temp[bufferPosition + 2] += decodedMap[(int)buffer[i + 3]];
            }
        }
    }

	memcpy(buffer, temp, size);
	delete [] temp;
}