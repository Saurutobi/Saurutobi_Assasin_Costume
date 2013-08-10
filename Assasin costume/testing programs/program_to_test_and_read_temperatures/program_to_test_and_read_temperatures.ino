//Author:Saurutobi
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 3 on the Arduino
#define ONE_WIRE_BUS 3

// Setup a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);


//USE THE DS18B20_address_finder to get this address
DeviceAddress tempSensor = { 0x28, 0x94, 0xE2, 0xDF, 0x02, 0x00, 0x00, 0xFE };
float currTemp;
float pastTemp;
boolean up = true;


void setup(void)
{
    // Start up the library
    sensors.begin();
    // set the resolution to 10 bit (good enough?)
    sensors.setResolution(tempSensor, 9);
}

void loop(void)
{
    pastTemp = currTemp;
    sensors.requestTemperatures();
    currTemp = sensors.getTempC(tempSensor);
    
    if(up)
    {
        if(pastTemp > currTemp)
        {
            up = false;
            Serial.print("Peaked at: ");
            Serial.println(pastTemp);
        }
    }
    else
    {
        if(pastTemp < currTemp)
        {
            up = true;
            Serial.print("hit bottom at: ");
            Serial.println(pastTemp);
        }
    }
}

