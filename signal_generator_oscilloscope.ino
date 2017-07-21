#include<avr/io.h>
#include<util/delay.h>
unsigned long timer[2];
byte last_channel;
int input;
float  output;
void setup() {
  // put your setup code here, to run once:
PCICR |= (1 << PCIE0);
  PCMSK0 |= (1 << PCINT0);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
print(); 
}
ISR(PCINT0_vect) {
  timer[0] = micros();
  // channel 1 ---------------
  if(last_channel == 0 && PINB & B00000001 ) {
    last_channel = 1;
    timer[1] = timer[0];
  }
  else if(last_channel == 1 && !(PINB & B00000001) ) {
    last_channel = 0;
    input = timer[0] - timer[1];
  }
  output=(1*1000000.0)/(input);
}
void print() {
  Serial.print("frequency:");
  Serial.print(output);
  Serial.println("Hz");
  _delay_ms(300);}
