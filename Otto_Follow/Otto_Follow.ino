#include <Servo.h> 
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
Otto Otto;  //This is Otto!

/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4
         |-----   ------|
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]

 /*SOUNDS******************
 * S_connection  S_disconnection  S_buttonPushed S_mode1 S_mode2 S_mode3 S_surprise S_OhOoh  S_OhOoh2  S_cuddly 
 * S_sleeping  S_happy S_superHappy S_happy_short S_sad S_confused S_fart1 S_fart2  S_fart3 
 */
/*MOVEMENTS LIST**************
 * dir=1---> FORWARD/LEFT
 * dir=-1---> BACKWARD/RIGTH
 * T : amount of movement. HIGHER VALUE SLOWER MOVEMENT usually 1000 (from 600 to 1400) 
 * h: height of mov. around 20
     jump(steps=1, int T = 2000);
     walk(steps, T, dir);
     turn(steps, T, dir);
     bend (steps, T, dir); //usually steps =1, T=2000
     shakeLeg (steps, T, dir);
     updown(steps, T, HEIGHT);
     swing(steps, T, HEIGHT);
     tiptoeSwing(steps, T, HEIGHT);
     jitter(steps, T, HEIGHT); (small T)
     ascendingTurn(steps, T, HEIGHT);
     moonwalker(steps, T, HEIGHT,dir);
     crusaito(steps, T, HEIGHT,dir);
     flapping(steps, T, HEIGHT,dir);
/*GESTURES LIST***************
OttoHappy OttoSuperHappy  OttoSad   OttoSleeping  OttoFart  OttoConfused OttoLove  OttoAngry   
OttoFretful OttoMagic  OttoWave  OttoVictory  OttoFail*/

boolean lost = false;

void setup(){
  Serial.begin(9600);
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true);
  Otto.setTrims(0,0,-45,0);
  Otto.sing(S_connection); //Otto wake up!
  Otto.home();
  delay(50);
}


void loop() {
  float distance = Otto.getDistance();
  char *c_Data = (char*) &distance;
  for(char c_index = 0; c_index < 5 ; Serial.write( c_Data[ c_index++] ) )
  Serial.print(distance, 4);
  Serial.print('\n');
    if(distance == 999 && !lost) {
      Otto.sing(S_sad);
      lost = true;
    }
    else if(distance > 60) {
      Otto.walk(2, 1000, 1);
      lost = false;
    }
    else if(distance != 999) {
      lost = false;
    }
    
}

