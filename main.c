/**
 *  FileName:     main.c form team project including student_1 and  student_2.
 *	
 *	Name: Embedded application design,  Lab 6
 *
 *	Description:    This lab generates three different waveform at OC1 pin RD0.
 *                  The lab was reorganized to split the workload in two parts.
 *                  Student_1 works on the user interface and student_1 works
 *                  on the various module used to generate the waveforms (i.e. 
 *                  timers, OC). Students must first define the tasks and functions
 *					required to fulfil the requirement. Then they have to draw a 
 *					dataflow diagram of the links between task, IOs and functions.
 *					Also, this diagram  will help figuring out the split of the work 
 *					and to specify the common global variables and the grouping of the
 *					tasks and functions into files. Students must use the 
  *					same naming scheme. 
 *                  Some common functions must be define by both students at the 
 *                  beginning (i.e. OSCILLATOR_INIT((),InitIO())
 *                  Once all common functions, global variables and their files 
 *                  are set up in the local project folder, the project must be pushed 
 *                  to the gitHub. 
 *                  After that, each student must fork the project and eventually 
 *                  pull a request when a decent version is functional.
 *                  see function_generat_data_flow.vsdx v2
      
 * * REVISION HISTORY:
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Author        	Date                Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould      May 24 2017 v1.0    The team.X project is pushed to https://github.com/advanced-programming/lab4-marie-sylavain
 *                                      Team member will fork this project.
 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
 
//#include "..\common\pmp_lcd.h"
#include "include/initBoard.h"
#include "include/public.h"
#include "../../common/GenericTypeDefs.h"

#include <stdio.h>


// Local global

//global and broadcast
display_type    display={1,0,100,400,0}; 
unsigned char sinus[RESOL], sawtooth[RESOL], square[RESOL];

int main( void)
{
	OSCILLATOR_Initialize();
    initIO();
	
    while(1){

    }// end while(1))

}// main

