/*  StopedFlow-thor-Energia-3 sketch for one drive pump and one valve servo
 *   
 *   saved 4/25/18 on computer 2
 */
#include <Servo.h>
#define valve PB_0 // Servo control pin for moving valve
#define enablePin PB_7  // new 3/26/15
#define dirPin PB_2    //  determines whether sample injected or removed
#define stepPin PE_0   //  outputs trigger 1/16th step
                             //  200 steps per revolution
#define trigger PF_0        // trigger spectral acquisition
int endStop[] = {PA_7, PA_6};    

//  stuff for fill/empty switches
boolean swReset[] = {true, true};  // has switch been reset?
int switchPin[] = {PE_5,PA_5};   // withdraw, inject
int switchVal[] = {LOW,LOW};  // read values for switch pins
volatile int flag = 0;  // fill switch flag
boolean run = false;

unsigned long stepCount = 0;         // number of steps the motor has taken  
unsigned int rotations;

//uint16_t params[8];           // array to hold parameters in, changed from 7, Feb 2017
int diam = 8;                      // 8 mm syringe dia
//unsigned int sVol;            //three mL syringes
//int fillmode =0;   // run, fill, or titrate
boolean runState=false;      //0 is off, 1 is on
//int nAddns;          // number of additions 
//int adDelay;         //  seconds between each addition in seconds
//float addVol;        // volume of 600 addition during rotations step (~42 uL)
float Area;
//int woi;             // withdraw or infuse; 0 = infuse, 1 = withdraw
unsigned long steps;
float injCyc;       // cycles to inject
//int dispVol;        // uL dispensed per addition
//int spd = 300;    
//float fspd;         //injection speed,

//float usDelay = 600;        // microseconds between pulses, frequency = 1/(2*usDelay)
//float pitch = 7.874; // 20 thread per inch, in threads/cm plunger displacement
//int param =0;      // paramater used in readParams routine in setup
//int addedVol;               // volume of titrant added to reaction
//int currentVol;             // volume of titrant currently in syringe
  boolean rsStatus = false;

int mode = 0;  // 0 is iject, 2 is kinetic run
//int runSpeed;
int triggerDelay = 10;  // was 5
long timingDelay[] = {100,140,190,390,790,1590,3190,6390,12790,90,90,90,90,0,0,0,0,0,0,0};
//{10,15,23,35,53,80,120,180,270,490,590,990,1990,2990,4990,6990,20,20,20};
//int unit;
//long base[] = {1,1000,60000};
volatile int endFlag = LOW;
float pitch = 1/8;               // threads per mm

int microliters = 0;                 // volume in microliters
int dir;                                 // direction, 0 = inject
boolean empty = false;

boolean comCon;            // are you connected to communications?

boolean runFromSwitch = false;  // running from switch
boolean gotParams = false;      // need parameters from serial port
 
int spectra;  // number of spectra to acquire 
int totalTime;

int delta;  // used in calculating timing delay
Servo valve1; // valve controlled by Servo
int valveMode = 0; // used in manual mode, 0 = to reservoir, 1 = to sample
 boolean vd;  // valve direction
int valvePos[] = {40,95};
int valveDelay = 400;
boolean set = false;

void setup()
{
   Serial.begin(9600);
    pinMode(valve, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(endStop[0], INPUT_PULLDOWN);
    pinMode(endStop[1], INPUT_PULLDOWN);
    pinMode(dirPin, OUTPUT);
    pinMode(enablePin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(enablePin,HIGH);
    pinMode(RED_LED,OUTPUT);
    pinMode(GREEN_LED,OUTPUT);

     Area = 3.14159*diam*diam/4;
    attachInterrupt(endStop[0],endStopFlag,RISING);
        attachInterrupt(endStop[1],endStopFlag,RISING);
    //attachInterrupt(emptyStop,endStopFlag,RISING);
  for (int k = 0; k<2; k++){
    pinMode(switchPin[k], INPUT_PULLDOWN);
    attachInterrupt(switchPin[k],pinRun,RISING);
  }
    pinMode(trigger, OUTPUT);
    comCon = false;
    digitalWrite(trigger,LOW);

}

void loop()
{
  
  setValve(0);  
    readSerial();

    if(mode == 1){   // trigger spectrum
  digitalWrite(trigger,HIGH);
  delay(triggerDelay);
  digitalWrite(trigger,LOW);
  Serial.println("Sample Injected");
  }
    if(mode == 2){
 //     setValve(1);   // 1 is send to cell
  digitalWrite(trigger,HIGH);
  delay(triggerDelay);
  digitalWrite(trigger,LOW);
  Serial.println("Spectrum 0 acquired)");
  for (int h=0; h<spectra-1; h++){
  delay(timingDelay[h]);
  digitalWrite(trigger,HIGH);
  delay(triggerDelay);
  digitalWrite(trigger,LOW);
  Serial.print("Spectrum number ");
  Serial.print(h+1);
  Serial.println(" acquired");
  }
  Serial.println("$");
    if(flag){
    readFillSwitch();
  }
  if(endStopFlag){
//  runEndStop();    // in pumpDrive tab
  }

    }
}

void pinRun(){
flag = HIGH;
}
void endStopFlag(){
    endFlag = HIGH;
}

void setValve(int j){  // j = 0 for reservoir and 1 for cell
    valve1.attach(valve);  //PB_0);
    valve1.write(0);
    delay(valveDelay);
    valve1.write(valvePos[j]);
    delay(valveDelay);
    valve1.detach();

}


