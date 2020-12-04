//Variable declarations
volatile int value = 0;
volatile unsigned long time = 0, time2;
double finish_time = 0;

void setup() {
  pinMode(2, OUTPUT); //Set capasitor input pin
  Serial.begin(9600); //Initialize serial
  cli(); //Disable interrupts

  //Zero ad-converter registers
  ADMUX ^= ADMUX;
  ADCSRA ^= ADCSRA;
  
  ADCSRA |= (1 << ADEN); //Enable ad-converter
  ADCSRA |= 0x7; //Set ad-converter's prescalar to 128
  ADCSRA |= (1 << ADIE); //Enable ad-conversion interupt
  
  ADCSRA |= (1 << ADSC); //Start first conversion

  //Zero timer registers
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  
  OCR1A = 125; //Timing for 0.5ms
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= ((1 << CS11) | (1 << CS10)); //64 prescaler
  sei(); //Enable interrupts

  //Precharge the capacitor to full
  digitalWrite(2, HIGH);
  while(value < 1023) {
    ADCSRA |= (1 << ADSC);
  }
  
  digitalWrite(2, LOW); //Start discharging the capasitor
  TIMSK1 |= (1 << OCIE1A); //Start timer
  
}

void loop() {
  double ux = value * 5 / 1023.0f; //Calculate capacitor voltage
  
  //If timer is stopped the capacitor is at 37% and we can calculate the capacitor's capacitance
  if(TIMSK1 == 0) {
    
    finish_time = time / 2 / 1000.0f; //The time the capacitor took to get to 37% in seconds
    double cx = finish_time / 10000000.0f; //Calculate the capacitance by dividing finish_time by the resistance

    //Print the result
    Serial.print(finish_time);
    Serial.print("\t");
    Serial.print(ux);
    Serial.print("\t");

    //Select sutable format for the capacitor's capacitance
    if(cx < 0.000001f) {
      Serial.print(cx * 1000000000);
      Serial.println("nF");
    } else if(cx < 0.001f) {
      Serial.print(cx * 1000000);
      Serial.println("uF");
    } else if(cx < 1.0f) {
      Serial.print(cx * 1000);
      Serial.println("mF");
    } else {
      Serial.println(cx);
    }
  } else { //Print some information while waiting
    Serial.print(time);
    Serial.print("\t");
    Serial.print(value);
    Serial.print("\t");
    Serial.println(ux);
  }
    
  delay(100); //Wait for 100ms
}

//Ad-converter interrupt service routine
ISR(ADC_vect) {
  value = ADCL | (ADCH << 8); //Combine the upper and lower byte register for a complete value
}

//Timer interrupt service routine
ISR(TIMER1_COMPA_vect) {
  ADCSRA |= (1 << ADSC); //Start ad-conversion for every 0.5ms  
  int ux = value;

  //Check if the capacitor is discarged to 37%
  if (ux < 0.37f * 1023){
    TIMSK1 = 0; //Stop the timer
  }
  time++; //Add 1 timer tick
}
