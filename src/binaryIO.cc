#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <string>
#include "program6.h"
using namespace std;

string* readInputFile(const char *infilename)
{
  BinaryFileHeader *fileHeader = new BinaryFileHeader();
  BinaryFileRecord *fileRecord = new BinaryFileRecord();
  ifstream binInfile (infilename, ios::in | ios::binary);

  binInfile.read((char *) fileHeader, sizeof(BinaryFileHeader));

  
  string magicNumber = to_string(fileHeader->magicNumber);
  string version = to_string(fileHeader->versionNumber);
  int arraySize = (fileHeader->numRecords)+3;

  string *array = new string[arraySize];

  array[0] = to_string(arraySize);
  array[1] = magicNumber;
  array[2] = version;

  for(int i=3; i < arraySize; i++)
  {
    binInfile.read((char *) fileRecord, sizeof(BinaryFileRecord)); 
    string record(fileRecord->stringBuffer);
    array[i] = record;
  }

  binInfile.close();
  return array;
}

