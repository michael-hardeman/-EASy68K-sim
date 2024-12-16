
/***************************** 68000 SIMULATOR ****************************

File Name: SIM.C
Version: 1.0

This file contains the function 'main()' and various screen management
	routines.

   Modified: Chuck Kelly
             Monroe County Community College
             http://www.monroeccc.edu/ckelly

***************************************************************************/

#include <stdio.h>
#include <iostream>
#include "extern.h"

//void scrshow(); 	/* update register display */
extern bool inputMode;
extern bool disableKeyCommands;  // defined in SIM68Ku

void initSim()                   // initialization for the simulator
{
  int	i;

  //autoTraceInProgress = false;

  inputMode = false;
  pendingKey = 0;               // clear pendingKey

  runMode = false;
  lbuf[0] = '\0';		// initialize to prevent memory access violations
  wordptr[0] = lbuf;
  for (i = 0; i <= 7; i++)
    A[i] = D[i] = 0;
  cycles = 0;
  SR = 0x2000;
  A[7] = 0x00FF0000;            // user stack
  A[8] = 0x01000000;            // supervisor stack
  OLD_PC = -1;                  // set different from 'PC' and 'cycles'
  trace = sstep = false;
  stopInstruction = false;
  stepToAddr = 0;               // clear step
  runToAddr = 0;                // clear runTo
  keyboardEcho = true;          // true, EASy68K input is echoed (default)
  inputPrompt = true;           // true, display prompt during input (default)
  inputLFdisplay = true;

  for (i=0; i<MAXFILES; i++) {  // clear file structures
    files[i].fp = nullptr;
  }

  irq = 0;                      // reset IRQ flags
  hardReset = false;
  /*
  FullScreenMonitor = 0;

  mouseX = 0;
  mouseY = 0;
  mouseLeft = false;
  mouseRight = false;
  mouseMiddle = false;
  mouseDouble = false;
  keyShift = false;
  keyAlt = false;
  keyCtrl =false;

  mouseXUp = 0;
  mouseYUp = 0;
  mouseLeftUp = false;
  mouseRightUp = false;
  mouseMiddleUp = false;
  mouseDoubleUp = false;
  keyShiftUp = false;
  keyAltUp = false;
  keyCtrlUp = false;

  mouseXDown = 0;
  mouseYDown = 0;
  mouseLeftDown = false;
  mouseRightDown = false;
  mouseMiddleDown = false;
  mouseDoubleDown = false;
  keyShiftDown = false;
  keyAltDown = false;
  keyCtrlDown = false;
  */
}

