#include "include/task.h"
#include "include/public.h"
#include <stdio.h>

//global and broadcast
extern display_type display;

extern unsigned char sinus[RESOL], sawtooth[RESOL], square[RESOL];

long TickGet_ms(void){
	return TickGet()/(TIMER_FREQ/1000);

}

void decodeRepeatTask(void) {
  static int amp=RESOL;
  static DWORD  lastTick;
  static DWORD  delay =1000;             // for auto repeat initial delay
  static int    cnt=0;                   // for auto repeat count
  static char curPBs=0, memPBs=0;
  static enum { SM_PBPoll =0, SM_Deb, SM_PBDecod,SM_FREQ, SM_WAV, SM_AMP, SM_PBRelease }state= 0;

	switch(state){
		case SM_PBPoll:
          // to convert into a function int readPBs(void)
		  //curPBs=readPBs();
          curPBs=((_RD6<<3) | (_RD7<<2) | (_RA7<<1)| (_RD13)) & 0x0F;
          memPBs=curPBs;  //memorize current PB state
           // A PB was pressed
            if (curPBs != 0x0f){  //if (curPBs == 0x000fui)
                state= SM_Deb;
                lastTick= TickGet_ms(); 
            }
			break;
		case SM_Deb:
			if(TickGet_ms() - lastTick >=20){
                curPBs=((_RD6<<3) | (_RD7<<2) | (_RA7<<1)| (_RD13)) & 0x0F;
                if(curPBs == memPBs) state=SM_PBDecod;
                else state = SM_PBPoll;
                delay =1000;           
                cnt=0;             
			}
			break;
        case SM_PBDecod:
            lastTick= TickGet_ms();
			switch(curPBs){
                //Amp Up
                case 0b0101:
                    state=SM_PBRelease;
                    if (amp<RESOL)amp++;
                    //initWave(amp);
                    //percent=(unsigned int)_amp*100/AMPL;
                    display.percent=(unsigned int)amp*100/RESOL;
                    //dispBufUpdate(0,0);
                    display.flag = 1;
                //    disp_f1=1;
                    break;
                //Amp Dn
                case 0b0110:
                    state=SM_PBRelease;
                    if (amp>0)amp--;
                    //initWave(amp);
                    display.percent=(unsigned int)amp*100/RESOL;
                    display.flag = 1;
                    //disp_f1=1;
                    break;
                //Freq Up
                case 0b1001:
                    state=SM_PBRelease;
                    if(display.freq<100000)display.freq+=INC_STEP;
                    PR2=((long)FCY/display.freq)/RESOL;
                   // dispBufUpdate(0,0);
                    display.flag = 1;
                   // disp_f1=1;
                    break;
                //Freq Dn
                case 0b1010: 
                    state=SM_PBRelease;
                    if(display.freq>5)display.freq-=50;
                    PR2=((long)FCY/display.freq)/RESOL;
                    display.flag = 1;
                    break;
                //change wave form Up or Dwn
                case 0b1101: 
				//case 0b1110: //dwn TODO
                    state=SM_PBRelease;
                    if(++display.wav>2)display.wav=0;
                    display.flag = 1;
                    break;
                default: state=SM_PBPoll;
            }
            display.flag = 1;
            //dispBufUpdate2(freq,amp,wav,sec);
			break;
        case SM_FREQ:
			
			break;
        case SM_WAV:
			
			break;
        case SM_AMP:
			
			break;
        case SM_PBRelease:
            curPBs=(_RD6<<3) | (_RD7<<2) | (_RA7<<1)| (_RD13);
            if(memPBs != curPBs) state=SM_PBPoll;
            else if(TickGet_ms() - lastTick >=delay){
                state=SM_PBDecod;
                if (cnt++ > 4) delay =200; // decrease delay to 200 mS
            }
			break;


	}

}


void countSecTask(void) {

  static DWORD lastTick;
  static enum { SM_IDLE =0, SM_INC}state= 0;

	switch(state){
		case SM_IDLE:
			if(TickGet_ms() - lastTick >=1000){
				state=SM_INC;   	// memorize the current time
			}
			break;


		case SM_INC:
            lastTick= TickGet_ms();   	// memorize the current time
            display.sec++;
            display.flag=1;
            _LATA0 ^=1;
			state = SM_IDLE;
			break;
	}

}

//non-blocking loop
void displayTask(void) {
//    static DWORD lastTick;
    static unsigned int percent=0;
    static char i=0;
    static char debug=0;
    static char textBuff1[16]={0};
    static char textBuff2[16]={0};
    static enum {SM_IDLE,SM_HOME1,SM_HOME2, SM_DISPLAY1, SM_DISPLAY2} state=0;
    debug++;
    switch (state) {
      	case SM_IDLE:
            if(display.flag){
                state=SM_HOME1;
                display.flag=0;   //reset semaphore
            }
         break;
         
      	case SM_HOME1:
           // _LATG12=1;

            IEC0bits.T2IE = 0; // Disable Timer 2 interrupt
            sprintf(textBuff1,"%dHz     %d    ",display.freq,display.percent);
            IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
            LCDL1Home();    //1200uS
            i=0;
            state=SM_DISPLAY1;
          //  _LATG12=0;
         break;
      	
      	case SM_DISPLAY1:
            
            if(textBuff1[i] !=0){
             // _LATG12=1;
             _LATG15=1;
                LCDPut(textBuff1[i]);//64uS
                i++;
             // _LATG12=0;
              _LATG15=0;
            }
            else state = SM_HOME2;
            break;
            
        case SM_HOME2:
            IEC0bits.T2IE = 0; // Disable Timer 2 interrupt
            if(display.wav==0) sprintf(textBuff2,"     squa %d  ", display.sec);
            else if(display.wav==1)sprintf(textBuff2,"     sawt %d  ", display.sec);
            else sprintf(textBuff2,"     sine %d  ", display.sec); 
            IEC0bits.T2IE = 1; // Enable Timer 2 interrupt
            LCDL2Home();
            i=0;
            state=SM_DISPLAY2;
            break; 
        
       case SM_DISPLAY2:
             //non-blocking loop
            if(textBuff2[i] !=0){
                LCDPut(textBuff2[i]);
                i++;
            }
            else state = SM_IDLE;
         break;
   }
}

