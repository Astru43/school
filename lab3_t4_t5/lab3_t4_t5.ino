float arvo = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(A5, INPUT);
}

void loop()
{
  arvo = analogRead(A5);
  
  Serial.print(analogRead(A5)); //AD-arvon tulostus
  Serial.print("\t");
  
  
  // Tämä on tehtävä 5. lineaarisilla suorilla
  if (analogRead(A5)<= 25 && analogRead(A5) > 0) {
    Serial.println(10 * arvo);                        //1. Arvoalue
  }
  if (analogRead(A5)<= 49 && analogRead(A5) > 25) {
    Serial.println(10.417 * arvo - 10.417);           //2. Arvoalue
  }
  if (analogRead(A5)<= 71 && analogRead(A5) > 49) {
    Serial.println(11.364 * arvo - 56.818);           //3. Arvoalue
  }
  if (analogRead(A5)<= 93 && analogRead(A5) > 71) {
    Serial.println(11.364 * arvo - 56.818);           //4. Arvoalue
  }
  if (analogRead(A5)<= 114 && analogRead(A5) > 93) {
    Serial.println(11.905 * arvo - 107.14);           //5. Arvoalue
  }
  if (analogRead(A5)<= 133 && analogRead(A5) > 114) {
    Serial.println(13.158 * arvo - 250);              //6. Arvoalue
  }
  if (analogRead(A5)<= 152 && analogRead(A5) > 133) {
    Serial.println(13.158 * arvo - 250);              //7. Arvoalue
  }
  if (analogRead(A5)<= 170 && analogRead(A5) > 152) {
    Serial.println(13.889 * arvo - 361.11);           //8. Arvoalue
  }

  
  
  
  
  // Tämä on tehtävä 4.
  Serial.println(0.0134 * pow(arvo, 2) + 9.4528 * arvo + 5.3722);
  
  // 0,0134x2 + 9,4528x + 5,3722     <---       Rx:n kaava
  

  delay(10);
}
