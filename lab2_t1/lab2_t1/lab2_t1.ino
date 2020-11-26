#define LED 12 //
volatile byte count=00;  //sekunnit
volatile byte count2=00; //minuutit
volatile byte count3=00; //tunnit

void setup()
{
 Serial.begin(9600);
 Serial.print("Timer int test \n");
 pinMode(LED, OUTPUT);
 noInterrupts(); // disable all interrupts
 TCCR1A = 0;
 TCCR1B = 0;
 TCNT1 = 0;
 OCR1A = 62500; // compare match register 16MHz/256/2Hz
 TCCR1B |= (1 << WGM12); // CTC mode
 TCCR1B |= (1 << CS12); // 256 prescaler
 TIMSK1 |= (1 << OCIE1A); // enable timer compare interrupt
 interrupts(); // enable all interrupts
}

void loop()
{
}

ISR(TIMER1_COMPA_vect) // timer compare interrupt service routine
{
 count++;
 Serial.print("Timer count: ");
 Serial.print(count3);
 Serial.print(":");
 Serial.print(count2);
 Serial.print(":");
 Serial.print(count);
 Serial.print("\n");

 if (count == 59){ //sekunnit
  count2++;
  count = -1;
 }
 if (count2 == 60){ //minuutit
  count3++;
  count2 = 0;
 }
 if (count3 == 24){ //tunnit
  count3 = 0;
 }
 
 digitalWrite(LED, digitalRead(LED) ^ 1); //xor
}
