/*
  AnalogReadSerial

  Reads an analog input on pin 0, prints the result to the Serial Monitor.
  Graphical representation is available using Serial Plotter (Tools > Serial Plotter menu).
  Attach the center pin of a potentiometer to pin A0, and the outside pins to +5V and ground.

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogReadSerial
*/
#define MOTOR 9
// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  pinMode(MOTOR,OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  int sensorValue = analogRead(A0);
  int sensorValue2 = analogRead(A1);
  // print out the value you read:
 // Serial.print(" adc: ");
 // Serial.print(sensorValue);
  float volt = 5/1024.0 * sensorValue;
  float volt2 = 5/1024.0 * sensorValue2;
  //Serial.print("volt: ");
 // Serial.println(volt);
  Serial.print("cds: ");
  Serial.println(volt2);

  int pwm = map(sensorValue2,0,1023,0,255);
  analogWrite(MOTOR,pwm);

  delay(1);  // delay in between reads for stability
}
