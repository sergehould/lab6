/**
 *  FileName:     main.c for student_2 PWM and timer development.
 *                  2:51 PM

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

 * Author        	Date      	Comments on this revision
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Serge Hould      May 19 2017 v1.1     

 *
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	TODO:
		
*/
//#include "..\common\pmp_lcd.h"

#include "include/task.h"

#include "include/initBoard.h"
#include "include/public.h"
#include "common/GenericTypeDefs.h"
#include "common/tickFast.h"

#include <stdio.h>
//#define     PROFILE 
//#define   TIMER_PROFILE 
#define 	_ISR_NO_PSV 	__attribute__((__interrupt__, no_auto_psv))

//global and broadcast
display_type    display={1,0,100,400,0};

=======

#include <stdio.h>

#define 	_ISR_NO_PSV 	__attribute__((__interrupt__, no_auto_psv))


// Local global

//global and broadcast
display_type    display={1,0,100,400,0};
unsigned char sinus[RESOL], sawtooth[RESOL], square[RESOL];

void _ISR_NO_PSV _T3Interrupt( void )
{
       // clear interrupt flag and exit
    _T3IF = 0;
} // T3 Interrupt


/* 	Timer 2 ISR
	This ISR is called at a frequency of ...
*/

void _ISR_NO_PSV _T2Interrupt( void )
{
	static int sample=0;
     /* Task profiling using a timer */
  //  profile.start=TickGet();
	  
        switch(display.wav) {
        case 0:
             OC1RS = square[ sample]; 
             break;
        case 1:
             OC1RS = sawtooth[sample];
             break;
        case 2:
             OC1RS = sinus[ sample];
                     break;
        }
        sample++;
        sample = (sample>=RESOL) ? 0 : sample;
    
	_T2IF = 0; // Clear Timer 2 interrupt flag
}


    
int main( void)
{
	OSCILLATOR_Initialize();
	initWave(RESOL);
    initTimer3();
	initTimer2();
	initOC();
    initIO();
	TickInit();			// initializes the tick function

    LCDInit();  
    LCDClear(); 
    display.flag =1;       
    // main loop
    while(1){
       displayTask(); 
       decodeRepeatTask();
       countSecTask();
    }// end while(1))


}// main

