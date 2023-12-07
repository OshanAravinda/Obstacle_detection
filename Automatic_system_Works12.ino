//Defining pins+7
#define trigPinL1_R 2    
#define echoPinL1_R 3
#define trigPinL1_L 4    


#define echoPinL1_L 5   
#define trigPinL2 6   
#define echoPinL2 7
#define trigPinL3 8   
#define echoPinL3 9
#define trigPinL4 10   
#define echoPinL4 11

//constants need to the calculations
const float Pi = 3.14159;
const float rad = 3.14159/180;
float L1_Cons = 70, L2_Cons = 100 , L3_Cons=150, L4_Cons= 200, Duration, L1_R_distance, L1_L_distance, L2_distance, L3_distance, L4_distance, h_val=100, L1_error = 5, L2_error =5, L3_error =5, L4_error =5;

void setup() {
Serial.begin (9600); //To connect with serial monitor (9600-Data sending rate -bits/second)
pinMode(trigPinL1_L, OUTPUT);
pinMode(echoPinL1_L, INPUT);
pinMode(trigPinL1_R, OUTPUT);
pinMode(echoPinL1_R, INPUT);
pinMode(trigPinL2, OUTPUT);
pinMode(echoPinL2, INPUT);
pinMode(trigPinL3, OUTPUT);
pinMode(echoPinL3, INPUT);
pinMode(trigPinL4, OUTPUT);
pinMode(echoPinL4, INPUT);
}

void loop(){
char System = Serial.read();
if ('1'== Serial.read()){
  Serial.write('Z');
  delay(2000);
  digitalWrite(trigPinL1_R, HIGH);  //Giving voltage to trigger pin
  delayMicroseconds(100);
  digitalWrite(trigPinL1_R, LOW);
  Duration = pulseIn(echoPinL1_R, HIGH);  //Reads the pulse from echo that the the time echo pings goes high - If we want the low time then use LOW
  L2_Cons = (Duration/2) / 29.1;//106
  h_val = L2_Cons*cos(20*rad); //Storing h value

//Calculating other constant L distances
  L1_Cons = h_val/cos(10*rad);  //101.5
  L3_Cons = h_val/cos(35*rad); //122
  L4_Cons = h_val/cos(45*rad); //141
  
//Calculating error margins. here the margin for floor level is +2cm and -2 cm
  L1_error = 10/cos(10*rad);
  L2_error = 10/cos(20*rad);
  L3_error = 10/cos(35*rad);
  L4_error = 10/cos(45*rad);
}
else if (Serial.read()=='4'){  
  //Detection and indication for level 1 right sensor
  digitalWrite(trigPinL1_R, HIGH);  //Giving voltage to trigger pin  pin of level 1 right sensor
  delayMicroseconds(100);
  digitalWrite(trigPinL1_R, LOW);
  Duration = pulseIn(echoPinL1_R, HIGH);  
  L1_R_distance = (Duration/2) / 29.1; // 29.1 is constant wave speed in air that in cm 
  if (L1_R_distance< (L1_Cons-L1_error)){
   Serial.write('A');} // Level 1 vibrator HIGH,Level 5 vibrator LOW
  else if (L1_R_distance>(L1_Cons+L1_error)){
   Serial.write('B');} // Level 1 vibrator HIGH, level 5 vibrator HIGH
  delay(10); //Travelling time delay

  //Detection and indication for level 1 left sensor
  digitalWrite(trigPinL1_L, HIGH);  //Giving voltage to trigger pin of level 1 left sensor
  delayMicroseconds(100);
  digitalWrite(trigPinL1_L, LOW);
  Duration = pulseIn(echoPinL1_L, HIGH);  
  L1_L_distance = (Duration/2) / 29.1; // 29.1 is constant wave speed in air that in cm 
  if (L1_L_distance< (L1_Cons-L1_error)){
   Serial.write('A');} //  Level 1 vibrator HIGH,Level 5 vibrator LOW
  else if (L1_L_distance>(L1_Cons+L1_error)){
   Serial.write('B');} // Level 1 vibrator HIGH, level 5 vibrator HIGH
  delay(10);

  //Detection and indication for level 2 sensor
  digitalWrite(trigPinL2, HIGH);  //Giving voltage to trigger pin of level 2 sensor
  delayMicroseconds(100);
  digitalWrite(trigPinL2, LOW);
  Duration = pulseIn(echoPinL2, HIGH);  
  L2_distance = (Duration/2) / 29.1; // 29.1 is constant wave speed in air that in cm 
  if (L2_distance< (L2_Cons-L2_error)){
   Serial.write('C');}  // Level 2 vibrator HIGH,Level 5 vibrator LOW
  else if (L2_distance>(L2_Cons+L2_error)){
   Serial.write('D');}   // Level 2 vibrator HIGH,Level 5 vibrator LOW
  delay(10);

  //Detection and indication for level 3 sensor
  digitalWrite(trigPinL3, HIGH);  //Giving voltage to trigger pin of level 3 sensor
  delayMicroseconds(100);
  digitalWrite(trigPinL3, LOW);
  Duration = pulseIn(echoPinL3, HIGH);  
  L3_distance = (Duration/2) / 29.1; // 29.1 is constant wave speed in air that in cm 
  if (L3_distance< (L3_Cons-L3_error)){
   Serial.write('E');} // Level 3 vibrator HIGH,Level 5 vibrator LOW
  else if (L3_distance>(L3_Cons+L3_error)){
   Serial.write('F');}// Level 3 vibrator HIGH,Level 5 vibrator HIGH
  delay(10);

  //Detection and indication for level 4 sensor
  digitalWrite(trigPinL4, HIGH);  //Giving voltage to trigger pin of level 4 sensor
  delayMicroseconds(100);
  digitalWrite(trigPinL4, LOW);
  Duration = pulseIn(echoPinL4, HIGH);  
  L4_distance = (Duration/2) / 29.1; // 29.1 is constant wave speed in air that in cm 
  if (L4_distance< (L4_Cons-L4_error)){
   Serial.write('G');} // Level 4 vibrator HIGH,Level 5 vibrator LOW 
  else if (L4_distance>(L4_Cons+L4_error)){
   Serial.write('H');} // Level 4 vibrator HIGH, Level 5 vibrator HIGH
  delay(10);

}
}
