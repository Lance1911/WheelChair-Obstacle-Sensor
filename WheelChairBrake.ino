/* Arduino script for processing the sensor-brake and LED buzzer alarm mechanism for 
 *  Wheelchair Sensor challenge
 * 
 * @Contributers: Lance Aguilar, Jiafu Li, Edmond Tran, Jarvis Ly
 * 
 *
 * 
 */

 #include <Servo.h>


const int trigPin = 9;
const int echoPin = 10;
const int warningLED = 13;
const int buzzer = 2;
const int servoPin = 5;

Servo servo;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  servo.attach(servoPin);
  loop();
}

/**
 * Manages buzzer sounds, LED lighting, and brakes from ultrasonic sensor
 * @param float freqDistance
 */
void ledFrequency(float freqDistance) {
  boolean check = false;
  Serial.println("Entered ledFrequency");
  if (freqDistance < 100) {
      for (int i = 0; i < 3; i++){
          tone(buzzer, 500, 1000);
          
          Serial.println("Entered 100 loop");
          digitalWrite(warningLED, HIGH);
          delay(500);
          digitalWrite(warningLED, LOW);
          delay(500);

          servo.write(0);
          delay(1000);
          servo.write(180);
          delay(1000);
      
          duration = pulseIn(echoPin, HIGH);
          freqDistance = (duration*.0343)/2;
          Serial.print("Distance: ");
          Serial.println(freqDistance);
          Serial.print("Duration: ");
          Serial.print(duration);
      } 
      
  }
  
}

/**
 * Loop function for arduino board and peripherals
 */
void loop() {
  digitalWrite(warningLED, LOW);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  ledFrequency(distance);
  delay(100);
}
