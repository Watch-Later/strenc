#include "Base64.h"

char Base64::Base64CharacterMap[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void Base64::ShuffleCharacterMap() {
  srand(GetTickCount());
  string shuffledmap(Base64::Base64CharacterMap);
  random_shuffle(shuffledmap.begin(), shuffledmap.end());
  for (int i = 0; i < strlen(Base64::Base64CharacterMap); i++)
    Base64::Base64CharacterMap[i] = shuffledmap[i];
}

void Base64::Encode(char* buffer, int size) {
  StrencEncode(buffer, size, Base64::Base64CharacterMap);
}

void Base64::Decode(char* buffer) {
  StrencDecode(buffer, Base64::Base64CharacterMap);
}