
//Manual System
// Defining pins
#define trigPin 2 //
#define echoPin 4 // pin 4
#define distanceButton 7 // the number of the pushbutton pin
#define systemButton 3
#define VoltagePin A0
#define VCC2 8
int data = 0; //variable input data for vibratotors
const int Vibrator_1 = 5;
const int Vibrator_2 = 6;
const int Vibrator_3 = 9;
const int Vibrator_4 = 10;
const int Vibrator_5 = 11;
void setup() // Initials
{
Serial.begin(9600); //To connect with serial monitor (9600-Data sending rate -bits/second)
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(VCC2,OUTPUT);
digitalWrite(VCC2,HIGH); //5V for potentiometer
pinMode(Vibrator_1, OUTPUT);
pinMode(Vibrator_2, OUTPUT);
pinMode(Vibrator_3, OUTPUT);
pinMode(Vibrator_4, OUTPUT);
pinMode(Vibrator_5, OUTPUT);
pinMode(systemButton,INPUT_PULLUP);
pinMode(distanceButton, INPUT_PULLUP); //initializing the pushbutton pin as an input:
pinMode(VoltagePin,INPUT);
}
void loop()
{
data = analogRead(VoltagePin);
data = map(data, 0,1023,0,255); //dividing voltages
float h =100.0;
int systemMode = digitalRead(systemButton);
//If the system in auto mode
if (systemMode == LOW){
//Sending signal if distancebutton is pressed
int distanceButtonState = digitalRead(distanceButton);
if (distanceButtonState == LOW)
{Serial.write('1');
delay(500);
if(Serial.read()=='Z')
{analogWrite(Vibrator_5,data);analogWrite(Vibrator_4,data);analogWrite(Vibrator_3,data);analogWrite(Vibrator_2,data);analogWrite(Vibrator_1,data);
delay(2000);
  }
}
else {
Serial.write('4');
delay(100);
if ('A'==Serial.read())
{analogWrite(Vibrator_1,data);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);delay(500);}
else if('B'==Serial.read())
{analogWrite(Vibrator_1,data);
digitalWrite(Vibrator_2,LOW);
digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);analogWrite(Vibrator_5,data);delay(500);}
else if ('C'==Serial.read())
{digitalWrite(Vibrator_1,LOW);analogWrite(Vibrator_2,data);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);delay(500);}
else if('D'==Serial.read())
{digitalWrite(Vibrator_1,LOW);analogWrite(Vibrator_2,data);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);analogWrite(Vibrator_5,data);delay(500);}
if ('E'==Serial.read())
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);analogWrite(Vibrator_3,data);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);delay(500);}
else if('F'==Serial.read())
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);analogWrite(Vibrator_3,data);
digitalWrite(Vibrator_4,LOW);analogWrite(Vibrator_5,data);delay(500);}
if ('G'==Serial.read())
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
analogWrite(Vibrator_4,data);digitalWrite(Vibrator_5,LOW);delay(500);}
else if('H'==Serial.read())
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
analogWrite(Vibrator_4,data);analogWrite(Vibrator_5,data);delay(500);}
else
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);delay(500);}
}
}
//If the system in auto mode
else
{
Serial.write('5');
long duration, L_distance; // long - 4 bytes , int - 2 bytes
digitalWrite(trigPin, LOW);
delayMicroseconds(10);
digitalWrite(trigPin, HIGH); //Giving voltage to trigger pin
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH); //Reads the pulse from echo that the the time echo pings goes high If we want the low time then use LOW
L_distance = (duration/2) / 29.1; // 29.1 is a constant that in cm (74 use fo inch) ------ /2 means both transmitting and recerving time
delay(200);
if ((h*0.3)<=L_distance and L_distance< (h*0.5)) //L1 distance (D between X1 range)
{analogWrite(Vibrator_1,data);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);}

else if((h*0.5)<=L_distance and L_distance < (h*0.7)) //L2 distance (D between X2 range)
{digitalWrite(Vibrator_1,LOW);analogWrite(Vibrator_2,data);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);}

else if((h*0.7)<=L_distance and L_distance< (h*0.9)) //L3 distance (D between X3 range)
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,HIGH);
analogWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);}

else if((h*0.9)<=L_distance and L_distance< (h*1.2)) //L3 distance (D between X4 range)
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
analogWrite(Vibrator_4,data);digitalWrite(Vibrator_5,LOW);}

else
{digitalWrite(Vibrator_1,LOW);digitalWrite(Vibrator_2,LOW);digitalWrite(Vibrator_3,LOW);
digitalWrite(Vibrator_4,LOW);digitalWrite(Vibrator_5,LOW);}
}
}
