const int trigPin = 6;
const int echoPin = 5;
const int buttonPin = 4;
const int tonePin = 2;

#define SOUND_VELOCITY 0.034
#define CM_EACH_NOTE 1.0
float distanceCm;

void setup() {
  Serial.begin(115200);
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
  distanceCm = pulseIn(echoPin, HIGH) * SOUND_VELOCITY / 2;
    
  if (digitalRead(buttonPin) == LOW) 
  {
    if (distanceCm<45.0 && distanceCm>6.0)
    {
      float semiTonesFromA4 = (distanceCm - 6.0) / CM_EACH_NOTE;
      float toneHzOfNote = (pow(2, (float)(semiTonesFromA4) / 12.0) * 440.0);
      Serial.print("distanceCm: ");
      Serial.print(distanceCm);
      Serial.print("\tsemiTonesFromA4: ");
      Serial.print(semiTonesFromA4);
      Serial.print("\ttoneHzOfNote: ");
      Serial.println(toneHzOfNote);
      tone(tonePin, toneHzOfNote);
    }
  }
  else
  {
    noTone(tonePin);
  }
}
