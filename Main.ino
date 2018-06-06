#include <Servo.h>
#define HALL 12

#define LINE_START 2
#define LINE_END 5
#define LINE_SIZE 4

#define TILT 7

#define SERVO 10

Servo steer;

bool skip = false; //KEEP THIS AT FALSE

bool prevLineSensor[LINE_SIZE];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(HALL, INPUT);
  pinMode(TILT, INPUT);
  for(int i = LINE_START; i <= LINE_END; i++)
    pinMode(i, INPUT);
    
  steer.attach(SERVO);
}

void loop() {
  // read sensors:
  bool hallSensor = readHallSensor();
  bool lineSensor[LINE_SIZE];
  readLineSensor(lineSensor);
  bool tiltSensor = readTiltSensor();

  
  int angle = getServoDegrees(lineSensor);
  //Serial.println(angle);

  if(!arraysEqual(lineSensor, prevLineSensor)) {
    if(skip) {
      skip = false;
    } else {
      skip = true;
      steer.write(angle);
      Serial.println("Yee");
    }
  }
  
  //analogWrite(SERVO, angle);
  
  delay(10);

  copyArray(lineSensor, prevLineSensor);
}


bool readHallSensor() {
  return digitalRead(HALL) == 0 ? true : false;
}

void readLineSensor(bool* input) {
  for(int i = 0; i < LINE_SIZE; i++)
    input[i] = digitalRead(i + LINE_START) == 0 ? true : false;
}

bool readTiltSensor() {
  return digitalRead(TILT) == 0 ? true : false;
}

int getServoDegrees(bool lineSensor[]) {
  //80: rechtdoor, 30: links, 110: rechts

  int rightSensors = 0;
  for(int i = 0; i < LINE_SIZE/2-1; i++) {
    if(lineSensor[i]) rightSensors++;
  }

  int leftSensors = 0;
  for(int i = LINE_SIZE - 1; i > LINE_SIZE/2; i--) {
    if(lineSensor[i]) leftSensors++;
  }

  if(leftSensors > rightSensors) return 30;
  else if(rightSensors > leftSensors) return 110;
  else return 80;
}

