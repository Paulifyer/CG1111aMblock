int motor_pin = 2;
int trig_pin = 13;
int echo_pin = 12;
float sound_speed = 0.0345;
 
void setup() {
  pinMode(motor_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  pinMode(trig_pin, OUTPUT);
  digitalWrite(trig_pin, LOW);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);
  int microsecs = pulseIn(echo_pin, HIGH);
  float cms = microsecs*sound_speed/2;
  Serial.println(cms);
  if (cms < 30) {
  digitalWrite(motor_pin, LOW);
  } else {
  digitalWrite(motor_pin, HIGH);
  }
}