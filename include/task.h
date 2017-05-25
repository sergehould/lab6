/**
  
*/

#ifndef TASK_H
#define TASK_H
/**
    Section: Includes
*/
#include "../common/GenericTypeDefs.h"
#include "../common/tickFast.h"
#include "../common/pmp_lcd.h"
#include <stdint.h>
#include <stdio.h>
#include <xc.h>
#include <math.h>

/**
    Section: Macros
*/
//macros definitions



/**
    Section: Function Prototypes
*/
void decodeTask(void);
void decodeRepeatTask(void);
void countSecTask(void);
void displayTask(void);
void displayTask2(void);
long TickGet_ms(void);

#endif
