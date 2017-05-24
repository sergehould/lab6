/**
  
*/

#ifndef PUBLIC_H
#define PUBLIC_H
/**
    Section: Includes
*/


/**
    Section: Macros
*/
//macros definitions

#define RESOL	64
#define FCY     16000000ull
#define TIMER_FREQ	FCY/8   //2000000
#define LED7 _LATA7
#define LED6 _LATA7
#define PB  _RD13
#define A_SET   _RD6
#define F_SET   _RD7
#define UP      _RA7
#define DN     _RD13
#define AMPL     40
#define FREQ    1
#define TWO_PI 		6.2831
#define INC_STEP    50

typedef struct{
    int wav;
    int sec;
    int percent;
    int freq;
    int flag;
}display_type;


#endif
