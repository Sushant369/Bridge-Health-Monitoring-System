
////flex 
const int flexPin = A4;  
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 3430;//4149.55; // resistance when flat
const float bendResistance = 4444.44;  // resistance at 90 deg
float angle =0.00;

void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
  pinMode(flexPin, INPUT);
 

}

void loop() {
  // put your main code here, to run repeatedly:
getFlexReading();
}

 void getFlexReading()
{
//   // Read the ADC, and calculate voltage and resistance from it
  int ADCflex = analogRead(flexPin);
  float Vflex = ADCflex * VCC / 4095.0;
 float Rflex = R_DIV * (VCC / Vflex - 1.0);
  Serial.println("flex reading ->");
  Serial.print("Resistance: " + String(Rflex) + " ohms");

  // Use the calculated resistance to estimate the sensor's bend angle:
 float angleTemp = map(Rflex, flatResistance, bendResistance, 0, 90.0);
  if(angleTemp>=0 && angleTemp<=90)
  {  
    angle=angleTemp;
  Serial.println("Bend: " + String(angle) + " degrees");
  Serial.println();
  delay(500);
  }
  else
  {
    if(angleTemp<0)
    {
      angle=0;
      Serial.println("Bend: 0 degrees");
  Serial.println();
  delay(500);
      } 
      if(angleTemp>90)
    {
      angle=90;
      Serial.println("Bend: 90 degrees");
  Serial.println();
  delay(500);
      }
    } 
}
  
