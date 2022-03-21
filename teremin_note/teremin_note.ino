const int trigPin = 5;
const int echoPin = 6;
const int buttonPin = 4;
const int tonePin = 2;

//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034
#define CM_EACH_NOTE 3.0
#define CM_AT_MIN 5.0
#define CM_AT_MAX 45.0

long duration;
float distanceCm;
float oldDistanceCm;

void setup() {
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(buttonPin, INPUT_PULLUP); // Sets the echoPin as an Input
  pinMode(tonePin, OUTPUT); // Sets the echoPin as an Input
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distanceCm = duration * SOUND_VELOCITY / 2;
  
  if (distanceCm < CM_AT_MIN)
    distanceCm = CM_AT_MIN;
  if (distanceCm > CM_AT_MAX)
    distanceCm = oldDistanceCm;
    
  if (digitalRead(buttonPin) == LOW) 
  {
    Serial.println("BUTTON");
    if (abs(oldDistanceCm-distanceCm)>(CM_EACH_NOTE/2.0))
      oldDistanceCm = distanceCm;
    int semiTonesFromA4 = (oldDistanceCm - CM_AT_MIN) / CM_EACH_NOTE;
    int toneHzOfNote = (int)(pow(2, (float)(semiTonesFromA4) / 12.0) * 440.0);
    tone(tonePin, toneHzOfNote);
  }
  else
  {
    noTone(tonePin);
  }
}
