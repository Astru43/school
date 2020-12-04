int analogInPin = A0;         // input pin      

int sensorValue = 0;         // Variable                  
       

void setup() {
 
  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(analogInPin);         // read the input on analog pin 0
 
  Serial.print ("Rx=");
  Serial.println (sensorValue);           // Prints out the value you read
  

  delay(2);
}
