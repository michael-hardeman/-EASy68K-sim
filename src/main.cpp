
#include <stdlib.h>
#include <stdio.h>
#include <string>

#ifdef WIN32
  #include <windows.h>
#else
  #include <unistd.h>
#endif

#include "def.h"
#include "proto.h"
#include "var.h"

//---------------------------------------------------------------------------
// Open program file
int loadProgramFromFile(char* name) {
  int addr;
  initSim();            // initialize simulator
  for (int i=0; i<MEMSIZE; i++)
    memory[i] = 0xFF;        // erase 68000 memory to $FF

  simhalt_on = true;            // default to SIMHALT enabled
  try {
    // load S-Record file
    if(loadSrec(name) == false) {  // if S-Record loads with no errors
      startPC = PC;               // save PC starting address for Reset
      return 0;
    }
  } catch(...) {
    return 1;
  }
}

void runLoop() {
  trace = false;
  sstep = false;
  runMode = true;
  try {
    while(runMode){
      runprog(); // run next 68000 instruction
    }
  }
  catch( ... ) {
    printf("Unexpected error in runLoop");
  }
}


void help(void)
{

  fprintf(stderr, "asy68k cli 68000 simulator Version %s based on source code from http://www.easy68k.com/\n", VERSION);
  fprintf(stderr, "Distributed under the GNU General Public Use License. The software is not warranted in any way. Use at your own risk.\n");
  fprintf(stderr, "\nPorted to the *nix CLI so it can be used in a Makefile workflow w/o WINE by Michael Hardeman December 2024\n\n");
  fprintf(stderr,"Usage:\n   asy68ksim {options} file1.L68 {file2.L68} ... {fileN.L68}\n\n");
  fprintf(stderr,"(Options with \"default:\" are enabled, use --no-{option} to turn off, i.e. --no-list)\n"
  //               "--list               default: produce listing (file.L68)\n"
                  "\n");
}


// stolen from mainS.cpp
int main(int argc, char *argv[])
{
  int i,s;

  if (argc == 1)  {help(); exit(0);}

  // listFlag = true;           // True if a listing is desired

  for (i=1; i<argc; i++)
  {
    //printf("arg[%d]=\"%s\"\n",i,argv[i]);
    // use path of selected source file as temp working directory
    //SetCurrentDir(ExtractFilePath(Active->Project.CurrentFile));

    // if (strncmp(argv[i],"--list",32)==0) {listFlag = true; continue;}

    if (argv[i][0]=='-') {help(); fprintf(stderr,"\n\nUnknown option \"%s\"",argv[i]); exit(1);}

    fprintf(stderr,"Simulating %s\n",argv[i]);
    memory = new char[MEMSIZE];      // reserve 68000 memory space
    if(loadProgramFromFile(argv[i])) {
      printf("Unexpected error in OpenFile\n");
    } else {
      runLoop();

      for (int i=0; i<D_REGS; i++){
        printf("D%d: %d\n", i, D[i]);
      }

      for (int i=0; i<A_REGS; i++){
        printf("A%d: %d\n", i, A[i]);
      }
    }

    delete[] memory;
  }
}