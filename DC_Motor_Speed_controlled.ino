//How To Make a PWM DC Motor Speed Controller | RPM Counter using Arduino
#include <LiquidCrystal.h>
LiquidCrystal lcd(2,3,4,5,6,7);

const int hallPin=8;
const unsigned long sampleTime=1000;
const int maxRPM = 10000; 

int volume_pin = A0;
int read_ADC;

int pwm_pin = 11;
int duty_cycle;
int duty_cycle_lcd;
 
void setup() {
  pinMode(hallPin,INPUT);
  pinMode(volume_pin, INPUT);
  pinMode(pwm_pin, OUTPUT);

  lcd.begin(16,2);  
  lcd.setCursor(0,0);
  lcd.print(" WELCOME To  My ");
  lcd.setCursor(0,1);
  lcd.print("YouTube  Channel");
  delay(2000);
  lcd.clear();
}
 
void loop() {     
int rpm=getRPM();

read_ADC = analogRead(volume_pin);
duty_cycle = map(read_ADC, 0, 1023, 50, 255);  
duty_cycle_lcd = map(read_ADC, 0, 1023, 0, 100); 

if(duty_cycle_lcd>0){ 
analogWrite(pwm_pin, duty_cycle); 
}else{digitalWrite(pwm_pin, LOW);}

 
lcd.setCursor(0,0);
lcd.print("Duty Cycle: ");
lcd.print(duty_cycle_lcd); 
lcd.print("%  ");
   
lcd.setCursor(0,1); 
lcd.print("   RPM: ");
lcd.print(rpm); 
lcd.print("   ");

delay(10);
}

int getRPM(){
  // sample for sampleTime in millisecs
int kount=0;
boolean kflag=LOW;
unsigned long currentTime=0;
unsigned long startTime=millis();
while (currentTime<=sampleTime){
if(digitalRead(hallPin)==HIGH){kflag=HIGH;}
if(digitalRead(hallPin)==LOW && kflag==HIGH){
kount++;
kflag=LOW;
}
currentTime=millis()-startTime;
}
int kount2rpm = int(30000./float(sampleTime))*kount;
return kount2rpm;
} 
