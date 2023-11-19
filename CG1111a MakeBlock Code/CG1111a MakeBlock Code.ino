#include <MeMCore.h>

#define TURNING_TIME_MS 395 // The time duration (ms) for turning
#define SPEED_OF_SOUND 340
#define ULTRASONIC 12
#define RGBWait 200  //in milliseconds
// Define time delay before taking another LDR reading
#define LDRWait 10  //in milliseconds
#define LDR A0      //LDR sensor pin at A0
#define LED 13      //Check Indicator to signal Calibration Completed
MeDCMotor leftMotor(M1); // assigning leftMotor to port M1
MeDCMotor rightMotor(M2); // assigning RightMotor to port M2
MeRGBLed led(0,30);
MeBuzzer buzzer;
MeLineFollower lineFinder(PORT_2);
uint8_t motorSpeed = 255;


//floats to hold colour arrays
float colourArray[] = { 0, 0, 0 };
float whiteArray[] = { 968, 974, 941 };
float blackArray[] = { 927, 926, 895 };
float greyDiff[] = { 16, 37, 43 };
char colourStr[3][5] = { "R = ", "G = ", "B = " };

void celebrate() {// Code for playing celebratory tune}
// Each of the following "function calls" plays a single tone.
// The numbers in the bracket specify the frequency and the duration (ms)
buzzer.tone(190, 200);
buzzer.tone(220, 200);
buzzer.tone(220, 200);
buzzer.tone(587.33, 200);
buzzer.tone(587.33, 200);
buzzer.tone(739.99, 200);
buzzer.tone(739.99, 200);
buzzer.tone(880, 200);
buzzer.tone(185, 200);
buzzer.tone(220, 200);
buzzer.tone(220, 200);
buzzer.tone(587.33, 200);
buzzer.tone(587.33, 200);
buzzer.tone(740, 200);
buzzer.tone(740, 200);
buzzer.tone(880, 200);
buzzer.tone(987.77, 600);
buzzer.tone(783.99, 150);
buzzer.tone(1174.66, 1600);
buzzer.tone(185, 200);
buzzer.tone(220, 200);
buzzer.tone(220, 200);
buzzer.tone(587.33, 200);
buzzer.tone(587.33, 200);
buzzer.tone(739.99, 200);
buzzer.tone(739.99, 200);
buzzer.tone(880, 200);
buzzer.tone(185, 200);
buzzer.tone(220, 200);
buzzer.tone(220, 200);
buzzer.tone(587.33, 200);
buzzer.tone(587.33, 200);
buzzer.tone(740, 200);
buzzer.tone(740, 200);
buzzer.tone(880, 200);
buzzer.tone(1046.50, 500);
buzzer.tone(1046.50, 200);
buzzer.tone(1046.50, 1200);
buzzer.tone(1046.50, 200);
buzzer.tone(987.77, 500);
buzzer.tone(1046.50, 150);
buzzer.tone(783.99, 1000);
buzzer.noTone();
}


void set_output() {
  pinMode(A2, OUTPUT);
  pinMode(A3, OUTPUT);
}

void turnoff() {
  digitalWrite(A2, LOW);
  digitalWrite(A3, LOW);
}

void shineRed() {
  digitalWrite(A3, HIGH);
  digitalWrite(A2, HIGH);
}

void shineGreen() {
  digitalWrite(A2, HIGH);
  digitalWrite(A3, LOW);
}

void shineBlue() {
  digitalWrite(A3, HIGH);
  digitalWrite(A2, LOW);
}

float measureAmbient()
{
  shineRed();
  delay(10);
  return analogRead(A1);
}

float measureIR()
{
  digitalWrite(A3, LOW);
  digitalWrite(A2, LOW);
  delay(10);
  return analogRead(A1);
}

void stopMotor() {// Codfe for stopping motor}
leftMotor.stop();
rightMotor.stop();
delay(1000);
}

void moveForward() {// Code for moving forward for some short interval}
leftMotor.run(-230);
rightMotor.run(motorSpeed);
}

void nudgeLeft() {// Code for nudging slightly to the left for some short interval
leftMotor.run(-120);
rightMotor.run(255);
delay(50);
}

void nudgeRight() {// Code for nudging slightly to the right for some short interval
rightMotor.run(120);
leftMotor.run(-255);
delay(50);
}

void turnRight() {// Code for turning right 90 deg
leftMotor.run(-motorSpeed * 0.8); // Positive: wheel turns anti-clockwise
rightMotor.run(-motorSpeed * 0.8); // Positive: wheel turns anti-clockwise
delay(TURNING_TIME_MS); // Keep turning right for this time duration
leftMotor.stop(); // Stop left motor
rightMotor.stop(); // Stop right motor
}

void turnLeft() {// Code for turning left 90 deg
leftMotor.run(motorSpeed * 0.8); // Positive: wheel turns clockwise
rightMotor.run(motorSpeed * 0.8); // Positive: wheel turns clockwise
delay(TURNING_TIME_MS); // Keep turning left for this time duration
leftMotor.stop(); // Stop left motor
rightMotor.stop(); // Stop right motor
}

char check_colour(float colourArray[])
{
  if (colourArray[0] > 200 && colourArray[1] > 200 && colourArray[2] > 200)
  {
    return 'W';
  }
  if (colourArray[0] > colourArray[1] && colourArray[0] > colourArray[2])
  {
    if (colourArray[1] < 100 && colourArray[2] < 100 && colourArray[1] - colourArray[2] <= 10) 
    {
      return 'R';
    }
    if (colourArray[0] - colourArray[2] <= 40)
    {
      return 'P';
    }
    if (colourArray[1] > colourArray[2])
    {
      return 'O';
    }
  }
  else if (colourArray[1] > colourArray[0] && colourArray[1] > colourArray[2])
  {
    return 'G';
  } 
  else if (colourArray[2] > colourArray[0] && colourArray[2] > colourArray[1])
  {
    if (colourArray[0] - colourArray[1] > 40)
    {
      return 'P';
    }
    return 'B';
  }
  return 'I';
}

void moveByColor(char color)
{
  if (color == 'R')
  {
    turnLeft();
  }
  else if (color == 'G')
  {
    turnRight();
  }
  else if (color == 'O')
  {
    turnRight();
    turnRight();
  }
  else if (color == 'P')
  {
    turnLeft();
    moveForward();
    delay(700);
    stopMotor();
    turnLeft();
  }
  else if (color == 'B')
  {
    turnRight();
    moveForward();
    delay(780);
    stopMotor();
    turnRight();
  }
  else if(color == 'W')
  {
    stopMotor();
    celebrate();
    delay(2000);
  }
}

void colourSensor(float blackArray[], float greyDiff[])
{
   for (int c = 0; c <= 2; c++) {
   Serial.print(colourStr[c]);
   if (c == 0) {
     shineRed();
   } else if (c == 1) {
     shineGreen();
   } else {
     shineBlue();
   }
   delay(RGBWait);
    // get the average of 5 consecutive readings for the current colour and return an average
   colourArray[c] = getAvgReading(5);
    // the average reading returned minus the lowest value divided by the maximum possible range, multiplied by 255 will give a value between 0-255, representing the value for the current reflectivity (i.e. the colour LDR is exposed to)
   colourArray[c] = (colourArray[c] - blackArray[c]) / (greyDiff[c]) * 255;
   turnoff();  //turn off the current LED colour
   delay(RGBWait);
   Serial.println(int(colourArray[c]));  //show the value for the current colour LED, which corresponds to either the R, G or B of the RGB code
 }
 Serial.println(check_colour(colourArray));
 moveByColor(check_colour(colourArray));
}

void lineSensor() {
int sensorState = lineFinder.readSensors();  
if (sensorState == S1_IN_S2_IN)
{
  stopMotor(); // Stop motor and activate the color sensor
  colourSensor(blackArray, greyDiff);
}
else if (sensorState == S1_OUT_S2_IN) {
    leftMotor.run(-100); // Left wheel moves forward
    rightMotor.run(0); // Right wheel stops
}
else if (sensorState == S1_IN_S2_OUT) {
    leftMotor.run(0); // Left wheel stops
    rightMotor.run(100); // Right wheel moves forward    
}
  else if (sensorState == S1_OUT_S2_OUT){
     moveForward(); // continue moving forward if the line detector still detects color
     return;
  }
  delay(50);
}

int checkDistanceUR()
{
  pinMode(ULTRASONIC, OUTPUT);
  digitalWrite(ULTRASONIC, LOW);
  delayMicroseconds(2);
  digitalWrite(ULTRASONIC, HIGH);
  delayMicroseconds(10);
  digitalWrite(ULTRASONIC, LOW);
  pinMode(ULTRASONIC, INPUT);
  long duration = pulseIn(ULTRASONIC, HIGH, 4000);
  return duration / 2.0 / 1000000 * SPEED_OF_SOUND * 100;
}

void setup() {
  //setup the outputs for the colour sensor
  for (int c = 0; c <= 2; c++) {
    set_output();
  }
  led.setpin(13);  //Check Indicator -- OFF during Calibration
  pinMode(A1, INPUT);
  Serial.begin(9600); //begin serial communication
  // setBalance(); // code to fill the black, white and grey arrays
  led.show();  //Check Indicator -- ON after Calibration
  delay(200);
}
void loop() {
  lineSensor();
  float ambient = 1024 - measureAmbient();
  Serial.println(ambient);
  float IR1 = (measureIR() - ambient) / 1024 * 5;
  Serial.println(IR1);
  delay(20);  
  int leftDist = checkDistanceUR();
  // Serial.println(leftDist);
  if (leftDist <= 6 && leftDist > 0)
  {
    // Serial.println("Nudging Right");
    led.setColorAt(1, 255, 255, 255);
    led.show();
    nudgeRight();
  }
  else if ((leftDist > 16 && leftDist <= 23) || IR1 < 3 ) // Nudge Left either when the ultrasonic sensor detects that the left distance is too far or IR sensor detects distance too small
  {
   // Serial.println("Nudging Left");
    led.setColorAt(0, 255, 255, 255);
    led.show();
    nudgeLeft();
  }
  led.setColor(0, 0, 0);
  led.show();
  delay(10);
}
void setBalance() {
  Serial.println("Put White Sample For Calibration ...");
  delay(5000);             //delay for five seconds for getting sample ready
  digitalWrite(LED, LOW);  //Check Indicator OFF during Calibration
  for (int c = 0; c <= 2; c++) {
    if (c == 0) {
      shineRed();
    } else if (c == 1) {
      shineGreen();
    } else {
      shineBlue();
    }
    delay(RGBWait);
    whiteArray[c] = getAvgReading(5);  //scan 5 times and return the average,
    Serial.println(whiteArray[c]);
    turnoff();
    delay(RGBWait);
  }
  //set black balance
  Serial.println("Put Black Sample For Calibration ...");
  delay(5000);  //delay for five seconds for getting sample ready
  //go through one colour at a time, set the minimum reading for red, green and blue to the black array
  for (int c = 0; c <= 2; c++) {
    if (c == 0) {
      shineRed();
    } else if (c == 1) {
      shineGreen();
    } else {
      shineBlue();
    }
    delay(RGBWait);
    blackArray[c] = getAvgReading(5);
        Serial.println(blackArray[c]);
    turnoff();
    delay(RGBWait);
    //the differnce between the maximum and the minimum gives the range
    greyDiff[c] = whiteArray[c] - blackArray[c];
    Serial.println(greyDiff[c]);

  }
  //delay another 5 seconds for getting ready colour objects
  Serial.println("Colour Sensor Is Ready.");
  delay(10000);
}
int getAvgReading(int times) {
  //find the average reading for the requested number of times of scanning LDR
  int reading;
  int total = 0;
  //take the reading as many times as requested and add them up
  for (int i = 0; i < times; i++) {
    reading = analogRead(LDR);
    total = reading + total;
    delay(LDRWait);
  }
  //calculate the average and return it
  return total / times;
}