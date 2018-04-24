/*
 * Program 6 - Binary File I/O Visualization
 * Author: Jimmy Nguyen
 * Email: tbn160230@utdallas.edu | jimmy@jimmyworks.net
 * Course: CS 3377.502 - C/C++ Programming in a UNIX Environment
 *
 */

#include <iostream>
#include <string>
#include "cdk.h"
#include "program6.h"
#include <sstream>
#include <iomanip>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

const char *infilename = "cs3377.bin";

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  // Matrix begins at 1,1. Row and Column 0 are placeholders
  const char    *rowTitles[] = {"", "a", "b", "c", "d", "e"};
  const char    *columnTitles[] = {"", "a", "b", "c"};
  int		boxWidths[] = { BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH, 
				BOX_WIDTH};
  int		boxTypes[] = {	vMIXED, 
  				vMIXED, 
				vMIXED, 
				vMIXED,  
				vMIXED,  
				vMIXED};

  // Initialize CDK screen
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
                          MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
                                     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
  {
    printf("Error creating Matrix\n");
    exit(1);
  }

  string *result = readInputFile(infilename);

  int arraySize = stoi(result[0]);
  int numRecords = arraySize - 3;
  int i = 0;
  while(i < arraySize)
  {
     cout << result[i] << endl;
     i++;
  }

  string showNumRecords = "NumRecords: " + to_string(numRecords);
  stringstream stream;
  stream << std::uppercase << std::hex << stol(result[1]);
  string magicNumBase16 = "Magic: 0x" + stream.str();

  string version = "Version: " + result[2];

  // Display the Matrix
  drawCDKMatrix(myMatrix, true);


  // Display a message
  setCDKMatrixCell(myMatrix, 1, 1, magicNumBase16.c_str());
  setCDKMatrixCell(myMatrix, 1, 3, showNumRecords.c_str());
  setCDKMatrixCell(myMatrix, 1, 2, version.c_str());
  setCDKMatrixCell(myMatrix, 2, 1, ("strlen: " + to_string(result[3].length())).c_str());
  setCDKMatrixCell(myMatrix, 2, 2, result[3].c_str());
  setCDKMatrixCell(myMatrix, 3, 1, ("strlen: " + to_string(result[4].length())).c_str());
  setCDKMatrixCell(myMatrix, 3, 2, result[4].c_str());
  setCDKMatrixCell(myMatrix, 4, 1, ("strlen: " + to_string(result[5].length())).c_str());
  setCDKMatrixCell(myMatrix, 4, 2, result[5].c_str());
  setCDKMatrixCell(myMatrix, 5, 1, ("strlen: " + to_string(result[6].length())).c_str());
  setCDKMatrixCell(myMatrix, 5, 2, result[6].c_str());


  drawCDKMatrix(myMatrix, true);

  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}

