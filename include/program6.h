#include <string.h>
using namespace std;

#ifndef _PROGRAM_6_H_
#define _PROGRAM_6_H_
const int maxLen = 25;

class BinaryFileHeader
{
  public:

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

class BinaryFileRecord
{
  public:
  uint8_t strLength;
  char stringBuffer[maxLen];
};

string* readInputFile(const char *infilename);

#endif
