
#include <MaxMatrix.h>
#include <PZEM004T.h>

float w_raw,accum_raw;
unsigned int w,wl,wr,n,nCount;
unsigned int light,mIntensity,mIntensity_pre,counter,counter2;
unsigned long accum_init,accum;
unsigned char isAccum,accumDisplayStep,WhDisplayStep;

byte bar[9]={B00000000,B00000001,B00000011,B00000111,B00001111,B00011111,B00111111,B01111111,B11111111};
byte NL[176]={
  B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B11000000,B11000000,B11111111,B11111111,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000011,  B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,
  B11111111,B11111111,B00000011,B00000011,B00000011,B00000011,B00000000,B00000011,  B11000011,B11000011,B11000011,B11000011,B11111111,B11111111,B00000000,B00000000,
  B00000011,B00000011,B00000011,B00000011,B11111111,B11111111,B00000000,B00000011,  B11000011,B11000011,B11000011,B11000011,B11111111,B11111111,B00000000,B00000000,
  B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,
  B00000011,B00000011,B00000011,B00000011,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B00000000,B00000000,
  B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,B00000000,B00000000,
  B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,B00000000,B00000011,  B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,B00000000,B00000000,
  B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B11000011,B11000011,B11111111,B11111111,B00000000,B00000000,
  B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,B00000000,B00000011,  B11111111,B11111111,B11000000,B11000000,B11111111,B11111111,B00000000,B00000000,
  B11111001,B11111001,B00011001,B00011001,B11111001,B11111001,B00000001,B11111001,  B10011111,B10011111,B10011000,B10011000,B10011111,B10011111,B10000000,B10011111,
  };
byte NR[176]={
  B00000011,B00000000,B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B11000000,B11000000,B11111111,B11111111,
  B00000011,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,  B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,
  B00000011,B00000000,B11111111,B11111111,B00000011,B00000011,B00000011,B00000011,  B00000000,B00000000,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111,
  B00000011,B00000000,B00000011,B00000011,B00000011,B00000011,B11111111,B11111111,  B00000000,B00000000,B11000011,B11000011,B11000011,B11000011,B11111111,B11111111,
  B00000011,B00000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B00000000,B00000000,B11111111,B11111111,
  B00000011,B00000000,B00000011,B00000011,B00000011,B00000011,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,
  B00000011,B00000000,B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B11000011,B11000011,B11000011,B11000011,
  B00000011,B00000000,B00000000,B00000000,B00000000,B00000000,B11111111,B11111111,  B00000000,B00000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,
  B00000011,B00000000,B11111111,B11111111,B00000011,B00000011,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B11000011,B11000011,B11111111,B11111111,
  B00000011,B00000000,B11000000,B11000000,B11000000,B11000000,B11111111,B11111111,  B00000000,B00000000,B11111111,B11111111,B11000000,B11000000,B11111111,B11111111,
  B11111001,B00011001,B00011001,B00011001,B00011001,B00000001,B11011001,B11011001,  B10011111,B10000000,B10000000,B10000000,B10000000,B10000000,B10011111,B10011111 // L
  };
byte NS[30]={
  B11111111,B10000001,B11111111,
  B00000000,B00000000,B11111111,
  B10011111,B10010001,B11110001,
  B10010001,B10010001,B11111111,
  B11111000,B00001000,B11111111,
  B11110001,B10010001,B10011111,
  B11111111,B10010001,B10011111,
  B10000000,B10000000,B11111111,
  B11111111,B10010001,B11111111,
  B11111000,B10001000,B11111111 //9
};
byte Wh[13]={B00000000,B11111110,B11100010,B11101110,B10000010,B11111110,B10000110,B11111010,B11110110,B11111010,B10000110,B11111110,B00000000};

// Matrix Conf: din cs clk
MaxMatrix ml(4, 3, 2, 4); 
MaxMatrix mrb(9, 7,8, 3); 
MaxMatrix mrt(12, 10,11, 3); 

// PZEM Conf: (RX,TX) connect to TX,RX of PZEM
PZEM004T pzem(13,5);  
IPAddress ip(192,168,1,1);

void setup(){
  delay(500);

  ml.init();
  ml.setIntensity(0);
  mrt.init();
  mrt.setIntensity(0); 
  mrb.init();
  mrb.setIntensity(0);  
    
  pzem.setAddress(ip);  

  accum_raw = pzem.energy(ip);
  if (accum_raw < 0.0) accum_raw = 0.0;
  accum_init=round(accum_raw);   
  isAccum=0;   
  counter2=100;
}

void loop(){

  w_raw = pzem.power(ip);  
  if (w_raw < 0.0) w_raw = 0.0;

  w=round(w_raw/100)*100;
  wl=w / 1000;
  wr=(w-wl*1000)/100;
  
  // left display
  if (w>=9999){
    printNL(10);
    printNR(10);
  } else {
    printNL(wl);
    printNR(wr);        
  }

  // summary display (1min)  
  if (isAccum) {
    accumDisplay();
  } else {
    counter2++;
    if (counter2>25 && w_raw<500){
      // check if idle
      isAccum=1;
      accumDisplayStep=0;
      WhDisplayStep=0;
      counter2=0;      
      accumDisplay();
    } else {
      barDisplay();
    }
  }

  intensityAdp(); 
  delay(1000);
}

void barDisplay(){
  mrt.shiftRight(false,false);
  mrb.shiftRight(false,false);

  if (w>4000)  {
    if (w>8000) {
      // overload
      mrb.setColumn(0,B11111111); 
      mrt.setColumn(0,B11111111); 
    } else { 
      mrb.setColumn(0,B11111111); 
      mrt.setColumn(0,bar[map(w,4000,8000,0,8)]);
    }
  } else {    
    mrt.setColumn(0,B00000000); 
    mrb.setColumn(0,bar[map(w,0,4000,0,8)]);
  }
}

void WhDisplay(){  
  mrt.shiftRight(false,true);
  if (WhDisplayStep<=12) {
    mrt.setColumn(0,Wh[WhDisplayStep]); 
    WhDisplayStep++;
  }
};

void accumDisplay(){  
  WhDisplay();
  switch(accumDisplayStep){
    case 0:     
      // lead in
      mrb.shiftRight(false,true);
      accumDisplayStep=1;
      
      accum_raw = pzem.energy(ip);
      if (accum_raw < 0.0) accum_raw = 0.0;
      accum=round(accum_raw)-accum_init;
      break; 
    case 1:
      // numbers 1/3
      n=accum==0?0:accum % 10;
      mrb.shiftRight(false,false);
      mrb.setColumn(0,NS[n*3+2]); 
      accumDisplayStep=2;
      break; 
    case 2:
      // numbers 2/3
      mrb.shiftRight(false,false);
      mrb.setColumn(0,NS[n*3+1]); 
      accumDisplayStep=3;
      break; 
    case 3:
      // numbers 3/3
      mrb.shiftRight(false,false);
      mrb.setColumn(0,NS[n*3]); 
      accum /= 10;

      // show at least 3 numbers    
      if (accum==0 && nCount>=2) {
          accumDisplayStep=255;
          nCount=0;     
      } else {
        nCount++;
        accumDisplayStep=1;
        delay(1000);      
        mrb.shiftRight(false,true);
        WhDisplay();
      }
      break; 
    case 255:
      // lead out
      mrb.shiftRight(false,true);
      isAccum=0;      
    default : 
      accumDisplayStep=0;
      WhDisplayStep=0;
  }
}

void printNL(int n) {
  for (int i=16; i<32; i++){
    ml.setColumn(i,NL[i+n*16-16]); 
  }
}
void printNR(int n) {
  for (int i=0; i<16; i++){
    ml.setColumn(i,NR[i+n*16]); 
  }
}
void intensityAdp(){ 
  // update intensity every 10 secs
  if(counter>10){    
    light=analogRead(A0);
    if (light<=400){
      mIntensity=0;
    } else if (light>=800) {
      mIntensity=8;
    } else {
      mIntensity=map(light,400,800,0,8);      
    }
    while(mIntensity!=mIntensity_pre){
      mIntensity_pre=mIntensity_pre>mIntensity?mIntensity_pre-1:mIntensity_pre+1;
      ml.setIntensity(mIntensity_pre);
      mrt.setIntensity(mIntensity_pre); 
      mrb.setIntensity(mIntensity_pre);   
      delay(40);
    }
    counter=0;
  } else {
    counter++;
  }
}



