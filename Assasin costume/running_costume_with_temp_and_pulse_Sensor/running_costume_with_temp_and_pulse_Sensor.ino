//Author: Saurutobi
#include <OneWire.h>
#include <DallasTemperature.h>

enum LINE {
	lineA = 2,
	lineB,
	lineC,
	lineD,
	lineE,
	lineF,
	lineG
} line;

int statusLED = 10;
int testLED = 13;
float inputTemp = 12;
int freq1 = 100;
int freq2 = 200;
int freq3 = 300;
int freq4 = 400;
int freq5 = 500;
int freq6 = 600;
int freq7 = 700;
int freq8 = 800;
int freq9 = 900;
int freq10 = 1000;
int lowthreshold = 0;
int threshold1 = 1;
int threshold2 = 2;
int threshold3 = 3;
int threshold4 = 4;
int threshold5 = 5;
int threshold6 = 6;
int threshold7 = 7;
int highthreshold = 8;

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

//USE THE DS18B20_address_finder to get this address
DeviceAddress tempSensor = { 0x28, 0x94, 0xE2, 0xDF, 0x02, 0x00, 0x00, 0xFE };

//Pulse Sensor Variables
int pulsePin = 0;                 // Pulse Sensor purple wire connected to analog pin 0
int fadePin = 9;                  // pin to do fancy classy fading blink at each beat
int fadeRate = 0;                 // used to fade LED on with PWM on fadePin
// these variables are volatile because they are used during the interrupt service routine!
volatile int BPM;                   // used to hold the pulse rate
volatile int Signal;                // holds the incoming raw data
volatile int IBI = 600;             // holds the time between beats, must be seeded! 
volatile boolean Pulse = false;     // true when pulse wave is high, false when it's low
volatile boolean QS = false;        // becomes true when Arduoino finds a beat.

void setup()
{
    //set up testLED, statusLED for output
    pinMode(testLED, OUTPUT);
    pinMode(statusLED, OUTPUT);
    
    //set up all lines for output
    pinMode(lineA, OUTPUT);
    pinMode(lineB, OUTPUT);
    pinMode(lineC, OUTPUT);
    pinMode(lineD, OUTPUT);
    pinMode(lineE, OUTPUT);
    pinMode(lineF, OUTPUT);
    pinMode(lineG, OUTPUT);
    
    // Start up the library
    sensors.begin();
    // set the resolution to 10 bit (good enough?)
    sensors.setResolution(tempSensor, 9);
    
    //Pulse Sensor Setup
    pinMode(fadePin,OUTPUT);          // pin that will fade to your heartbeat!
    interruptSetup();                 // sets up to read Pulse Sensor signal every 2mS 
}

void loop()
{
    //read temperature here
    sensors.requestTemperatures();
    inputTemp = sensors.getTempC(tempSensor);
    dWrite();
    
    //Pulse Sensor
    if (QS == true)                        // Quantified Self flag is true when arduino finds a heartbeat
    {
        fadeRate = 255;                    // Set 'fadeRate' Variable to 255 to fade LED with pulse
        QS = false;                        // reset the Quantified Self flag for next time    
    }
    ledFadeToBeat();
  
    //delay(20);                             //  take a break
}

void dWrite()
{	
    //we want to stop when we've started over the 3rd time
    enum LINE line = lineA;
    int frequency = HIGH;
    for(int counter = 0; counter < 2; line = static_cast<LINE>(static_cast<int>(line) + 1))
    {
        digitalWrite(testLED, frequency);  //do the first test
        digitalWrite(line, frequency);  //write to the specific line and freq
        if (line == lineG) //if we're at the end do something different
        {
            /*** Depending on HIGH or LOW we will do freq#  or  1000 - freq# ***/
            if (inputTemp <= lowthreshold)
            {
                delayMicroseconds((counter * 1000) - freq1);
            }
            else if (inputTemp > lowthreshold && inputTemp <= threshold1)
            {
                delayMicroseconds((counter * 1000) - freq2);
            }
            else if (inputTemp > threshold1 && inputTemp <= threshold2)
            {
                delayMicroseconds((counter * 1000) - freq3);
            }
            else if (inputTemp > threshold2 && inputTemp <= threshold3)
            {
                delayMicroseconds((counter * 1000) - freq4);
            }
            else if (inputTemp > threshold3 && inputTemp <= threshold4)
            {
                delayMicroseconds((counter * 1000) - freq5);
            }
            else if (inputTemp > threshold4 && inputTemp <= threshold5)
            {
                delayMicroseconds((counter * 1000) - freq6);
            }
            else if (inputTemp > threshold5 && inputTemp <= threshold6)
            {
                delayMicroseconds((counter * 1000) - freq7);
            }
            else if (inputTemp > threshold6 && inputTemp <= threshold7)
            {
                delayMicroseconds((counter * 1000) - freq8);
            }
            else if (inputTemp > threshold7 && inputTemp <= highthreshold)
            {
                delayMicroseconds((counter * 1000) - freq9);
            }
            else
            {
                delayMicroseconds((counter * 1000) - freq10);
            }
            
            if (counter == 0) //only do this stuff the first time
            {
                frequency = LOW; //change the frequency
                digitalWrite(testLED, frequency); //do a test write
            }
            
            counter++; //change the next set of writes
			line = lineA;
        }
    }
}

void ledFadeToBeat()
{
    fadeRate -= 15;                         //  set LED fade value
    fadeRate = constrain(fadeRate,0,255);   //  keep LED fade value from going into negative numbers!
    analogWrite(fadePin,fadeRate);          //  fade LED
}
