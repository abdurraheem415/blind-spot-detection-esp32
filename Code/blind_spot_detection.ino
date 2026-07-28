/*
=========================================================
 Blind Spot Detection & Driver Warning System using ESP32
 Project: Contretemps Nullification
 Platform: ESP32
 Developed for Engineering Clinic Project
=========================================================
*/

// ---------------- PIN DEFINITIONS ----------------

// Left Ultrasonic Sensor
const int trigPin1 = 18;
const int echoPin1 = 21;

// Right Ultrasonic Sensor
const int trigPin2 = 19;
const int echoPin2 = 22;

// Left Warning System
const int buzzer1 = 13;
const int led1 = 25;

// Right Warning System
const int buzzer2 = 14;
const int led2 = 26;

// Safety distance (cm)
const int distanceThreshold = 4;

// --------------------------------------------------

void setup()
{
  Serial.begin(115200);

  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);

  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  pinMode(buzzer1, OUTPUT);
  pinMode(led1, OUTPUT);

  pinMode(buzzer2, OUTPUT);
  pinMode(led2, OUTPUT);

  Serial.println("Blind Spot Detection System Started");
}

void loop()
{
  long distance1 = measureDistance(trigPin1, echoPin1);
  long distance2 = measureDistance(trigPin2, echoPin2);

  Serial.print("Left Distance : ");
  Serial.print(distance1);
  Serial.print(" cm\t");

  Serial.print("Right Distance : ");
  Serial.print(distance2);
  Serial.println(" cm");

  // LEFT SIDE WARNING
  if (distance1 > 0 && distance1 <= distanceThreshold)
  {
    digitalWrite(buzzer1, HIGH);
    digitalWrite(led1, HIGH);
  }
  else
  {
    digitalWrite(buzzer1, LOW);
    digitalWrite(led1, LOW);
  }

  // RIGHT SIDE WARNING
  if (distance2 > 0 && distance2 <= distanceThreshold)
  {
    digitalWrite(buzzer2, HIGH);
    digitalWrite(led2, HIGH);
  }
  else
  {
    digitalWrite(buzzer2, LOW);
    digitalWrite(led2, LOW);
  }

  delay(100);
}

// --------------------------------------------------

// Function to measure distance
long measureDistance(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);

  long distance = duration * 0.034 / 2;

  return distance;
}