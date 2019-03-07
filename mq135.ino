/*
 * Program to measure gas in ppm using MQ sensor
 * Dated: 03-03-2019
 */
#include<LiquidCrystal.h>
 
#define RL 20  //The value of resistor RL is 47K
#define m -0.263 //Enter calculated Slope 
#define b 0.42 //Enter calculated intercept
#define Ro 76.63 //Enter found Ro value
#define MQ_sensor A0 //Sensor is connected to A4

int avg_value,n=0;
int fan=7,clean=8,ir=10;
int count=0;

int cnt=20;
LiquidCrystal lcd(12,11,5,4,3,2);

void setup() 
{
  pinMode(fan, OUTPUT);
  pinMode(clean, OUTPUT);
  pinMode(ir,INPUT);
  
  Serial.begin(9600); // sets the serial port to 9600
  Serial.println("NH3 in PPM"); //Display a intro message
  //delay(2000); //Wait for display to show info

  analogWrite(6,cnt);
  lcd.begin(16,2);
}

void loop() 
{
  // count person with ir sensor
  if(!(digitalRead(ir)))
  {
    count++;
    Serial.print("Count=");
    Serial.println(count);
    Serial.print("Total=");
    Serial.println(count/2);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
  }

  //ppm levels check with MQ-135 and controlling fan, clean msg
  float VRL; //Voltage drop across the MQ sensor
  float Rs; //Sensor resistance at gas concentration 
  float ratio; //Define variable for ratio
  VRL = analogRead(MQ_sensor)*(5.0/1023.0); //Measure the voltage drop and convert to 0-5V
  Rs = ((5.0*RL)/VRL)-RL; //Use formula to get Rs value
  ratio = Rs/Ro;  // find ratio Rs/Ro
  float ppm = pow(10, ((log10(ratio)-b)/m)); //use formula to calculate ppm

 
  Serial.print("NH3 (ppm) = ");
  Serial.println(ppm);
  //Serial.print("Voltage = "); //Display a intro message 
  //Serial.println(VRL);
  
  if(ppm>2.0 && n!=2)
  {
    n=2;
    digitalWrite(fan, HIGH);
    digitalWrite(clean, HIGH);
  }
  else if(ppm>1.2)
  {
    n=1;
    digitalWrite(fan, HIGH);
    digitalWrite(clean, LOW);
  }
  else
  {
    n=0;
    digitalWrite(fan, LOW);
    digitalWrite(clean, LOW);
  }

  //lcd printing
  lcd.setCursor(0,0);
  lcd.print(String("Count=")+String(count/2));
  //lcd.print(count/2);
  lcd.setCursor(0,1);
  lcd.print(String("NH3 ppm=")+String(ppm));
  //lcd.print(ppm);
}
