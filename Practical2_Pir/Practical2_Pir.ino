int ledPin = 11; //pin where LED is connected
int pirPin = 3; //pin where pir sensor is connected

void setup()
{
  pinMode(pirPin, INPUT); //set LED pin for output
  pinMode(ledPin, OUTPUT); //set pir sensor pin for reading input
  Serial.begin(9600);
}

void loop()
{
  int motionState = digitalRead(pirPin);
  if (motionState == HIGH) //if motion is detected 
  {
    digitalWrite(ledPin, HIGH);
    Serial.println("Motion Detected");
  }
  else{
    digitalWrite(ledPin, LOW);
    Serial.println("No Motion Detected");
  }

} 