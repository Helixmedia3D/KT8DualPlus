/*
* 2017
* 
* ARDUINO NANO (ATmega 328) HEATER LOOP
* KT8 DUAL+ 3D Printer
* 
* Kunststoftechniek Groep KT8
* Hogeschool Zuyd University of Applied Sciences 
*
*/
//------------------------------------------------------------------------
// Maximale temperatuur voor e-stop
int MAXTEMP = 150;

// Minimale temperatuur voor e-stop
int MINTEMP = 0;

// smoothing afwijking. Voorkomt disco-mode van de voorste led lampjes.
float smoothingDeviation = 0.5; //moet groter dan 0!
//------------------------------------------------------------------------

int fanLinks = 3;
int fanMidden = 6;
int fanRechts = 5;
int tempPinvoorLinks = A1;
int tempPinvoorRechts = A4;
int tempPinachterLinks = A3;
int tempPinachterRechts = A2;
int tempPinonder = A5;
int heater = 11;
int tempSetPin = 12;
int ledBoven = 8;
int ledOnder = 7;

float tempvoorLinks;
float tempvoorRechts;
float tempachterLinks;
float tempachterRechts;
float temponder;
float tempAVG;
unsigned long tempsetPulsBreedte;
float tempsetTEMP;
float maxi = -100,mini = 100; 

void errorMode(){
  digitalWrite(ledBoven, HIGH);
  digitalWrite(ledOnder, HIGH);
  digitalWrite(fanMidden, LOW);
  digitalWrite(fanLinks, HIGH);
  digitalWrite(fanRechts, HIGH);
  digitalWrite(heater, LOW); 
  for (;;); //vereist handmatige reset
}

void setup() {
  pinMode(fanMidden, OUTPUT);
  pinMode(fanRechts, OUTPUT);
  pinMode(fanLinks, OUTPUT);
  pinMode(tempPinvoorLinks, INPUT);
  pinMode(tempPinvoorRechts, INPUT);
  pinMode(tempPinachterLinks, INPUT);
  pinMode(tempPinachterRechts, INPUT);
  pinMode(tempPinonder, INPUT);
  pinMode(heater, OUTPUT);
  pinMode(tempSetPin, INPUT);
  pinMode(ledBoven, OUTPUT);
  pinMode(ledOnder, OUTPUT);
  Serial.begin(9600);
}


void loop() {
  digitalWrite(fanMidden, LOW);  
  digitalWrite(fanRechts, LOW); 
  digitalWrite(fanLinks, LOW);
   
  //temperaturen bepalen
  tempvoorLinks = (analogRead(tempPinvoorLinks)*0.48828125); 
  tempvoorRechts = (analogRead(tempPinvoorRechts)*0.48828125); 
  tempachterLinks = (analogRead(tempPinachterLinks)*0.48828125); 
  tempachterRechts = (analogRead(tempPinachterRechts)*0.48828125); 
  temponder = (analogRead(tempPinonder)*0.48828125); 

  //bepalen gemiddelde temperatuur
  tempAVG = (tempvoorLinks + tempvoorRechts + tempachterLinks + tempachterRechts) / 4;  
  
  //bepalen maximale temperatuur
  if(tempvoorLinks > maxi) {maxi = tempvoorLinks;}
  if(tempvoorRechts > maxi) {maxi = tempvoorRechts;}
  if(tempachterLinks > maxi) {maxi = tempachterLinks;}
  if(tempachterRechts > maxi) {maxi = tempachterRechts;}
  
  //bepalen minimale temperatuur
  if(tempvoorLinks < mini) {mini = tempvoorLinks;} 
  if(tempvoorRechts < mini) {mini = tempvoorRechts;} 
  if(tempachterLinks < mini) {mini = tempachterLinks;} 
  if(tempachterRechts < mini) {mini = tempachterRechts;} 

  tempsetPulsBreedte = pulseIn(tempSetPin, HIGH);
  
  //Super Sketchy temperatuur tabel
  //85 max temp, increments van 6.5 [C]
  if(tempsetPulsBreedte >= 0 && tempsetPulsBreedte < 20) {tempsetTEMP = 5;}
  if(tempsetPulsBreedte > 20 && tempsetPulsBreedte < 200) {tempsetTEMP = 26.5;}
  if(tempsetPulsBreedte > 200 && tempsetPulsBreedte < 400) {tempsetTEMP = 33;}
  if(tempsetPulsBreedte > 400 && tempsetPulsBreedte < 600) {tempsetTEMP = 39.5;}
  if(tempsetPulsBreedte > 600 && tempsetPulsBreedte < 800) {tempsetTEMP = 46;}
  if(tempsetPulsBreedte > 800 && tempsetPulsBreedte < 1000) {tempsetTEMP = 52.5;}
  if(tempsetPulsBreedte > 1000 && tempsetPulsBreedte < 1200) {tempsetTEMP = 59;}
  if(tempsetPulsBreedte > 1200 && tempsetPulsBreedte < 1400) {tempsetTEMP = 65.5;}
  if(tempsetPulsBreedte > 1400 && tempsetPulsBreedte < 1600) {tempsetTEMP = 72;}
  if(tempsetPulsBreedte > 1600 && tempsetPulsBreedte < 1800) {tempsetTEMP = 78.5;}
  if(tempsetPulsBreedte > 1800 && tempsetPulsBreedte < 2500) {tempsetTEMP = 85;}

  Serial.print("Gewenste Temperatuur ");
  Serial.println(tempsetTEMP);

  Serial.print("Huidige Temperatuur ");
  Serial.println(tempAVG);
  Serial.println("");

  
  /*
   * RAMPS PWM (0-255) - ARDUINO READ
   * S1 = 8
   * S50 = 400
   * S100 = 800
   * S150 = 1195
   * S200 = 1595
   * S250 = 1995
   */

  
  //MINTEMP en MAXTEMP voor LM35 onderin
  if (temponder < MINTEMP || temponder > MAXTEMP) { 
  errorMode();
  }

  //MINTEMP en MAXTEMP voor LM35 bovenin
  if (maxi < MINTEMP || maxi > MAXTEMP) {
  errorMode();
  }
  
  if (mini < MINTEMP || mini > MAXTEMP) {
  errorMode();
  }


  /*
  FANS
  */
  
  if(tempsetTEMP > 10) {
  digitalWrite(fanMidden, HIGH);
  digitalWrite(fanLinks, HIGH);
  digitalWrite(fanRechts, HIGH);
  }
  else{
  digitalWrite(fanMidden, LOW);
  digitalWrite(fanLinks, LOW);
  digitalWrite(fanRechts, LOW);
  digitalWrite(heater, LOW);
  }

  /*
  HEATER 
  */
  
  if (tempsetTEMP > 6){
 // if (tempsetTEMP - tempAVG > smoothingDeviation || tempsetTEMP - tempAVG < -smoothingDeviation ) {  
  if (tempsetTEMP > tempAVG) {  
  digitalWrite(heater, HIGH);
  digitalWrite(ledOnder, HIGH);
  digitalWrite(ledBoven, LOW);
   }
   
  else{
  digitalWrite(heater, LOW);
  digitalWrite(ledOnder, LOW);
  digitalWrite(ledBoven, HIGH);
     }
  }
  
  else{
    digitalWrite(heater, LOW);
    digitalWrite(ledOnder, LOW);
    digitalWrite(ledBoven, HIGH);
  }
  
  /*Serial.print("AVG ");
  Serial.println(tempAVG);
  Serial.print("MAX ");
  Serial.println(maxi);
  Serial.print("MIN ");
  Serial.println(mini);
  Serial.println("");
  */
  delay(1000);
                   
}
