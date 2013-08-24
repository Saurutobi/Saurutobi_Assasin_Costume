//Author: Saurutobi
int lineA = 2;
int testLED = 13;
int printButton = 11;    //http://www.arduino.cc/en/Tutorial/Button for tutorial
int changeTempButton = 12;
int frequency = 100;

void setup()
{
    //this sets up testLED as an output
    pinMode(testLED, OUTPUT);
    //set up all lines for output
    pinMode(lineA, OUTPUT);
    //sets up printButton to output a frequency or something like that
    pinMode(printButton, INPUT);
}

void loop()
{
    dWrite();
}
void dWrite()
{
    if(digitalRead(printButton) == HIGH)
    {
        Serial.println("duty on frequency = " + frequency);
        digitalWrite(testLED, HIGH);
        delay(1000);
    }
    else if(digitalRead(changeTempButton) == HIGH)
    {
        frequency += 10;
        Serial.println("changed frequency. it is now = " + frequency);
        digitalWrite(testLED, HIGH);
        delay(1000);
    }
    else
    {
        digitalWrite(testLED, LOW);
    }
    
    digitalWrite(lineA, HIGH);
    delayMicroseconds(frequency);
    digitalWrite(lineA, LOW);
    delayMicroseconds(1000 - frequency);
}
