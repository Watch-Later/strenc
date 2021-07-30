#pragma once
#include <windows.h>
#include <algorithm>
#include <sstream>

using namespace std;

#if (defined DEBUG || defined _DEBUG)
#pragma comment(lib, "libstrenc_d.lib")
#else
#pragma comment(lib, "libstrenc.lib")
#endif
void StrencEncode(char* buffer, int size, const char* Base64CharacterMap);
void StrencDecode(char* buffer, const char* Base64CharacterMap);

class Base64 {
 public:
  static char Base64CharacterMap[];

  static void ShuffleCharacterMap();
  static void Encode(char* buffer, int size);
  static void Decode(char* buffer);
};
