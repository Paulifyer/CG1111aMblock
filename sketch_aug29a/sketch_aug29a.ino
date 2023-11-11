#include <Servo.h>
Servo servo;
int servo_pin = 2;
int TRIG_PIN = 13;
int ECHO_PIN = 12;
int MOTOR_PIN1 = 6;
int MOTOR_PIN2 = 5;
float SPEED_OF_SOUND = 0.0345;

void setup() {
  servo.attach(servo_pin, 544, 2400);
  servo.write(0);
  pinMode(MOTOR_PIN1, OUTPUT);
  pinMode(MOTOR_PIN2, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  digitalWrite(TRIG_PIN, LOW);
  pinMode (ECHO_PIN, INPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  int microsecs = pulseIn (ECHO_PIN, HIGH);
  float cms = microsecs*SPEED_OF_SOUND/2;
  Serial.println(cms);
  if (cms < 30) {
    digitalWrite(MOTOR_PIN1, LOW);
    digitalWrite(MOTOR_PIN2, LOW);
    delay(1000);
    servo.write(90);
  } 
  else {
    digitalWrite(MOTOR_PIN1, HIGH);
    digitalWrite(MOTOR_PIN2, HIGH);
    servo.write(0);
  }
delay(10);
}
