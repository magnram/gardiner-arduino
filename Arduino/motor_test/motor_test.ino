#include <util/atomic.h> // For the ATOMIC_BLOCK macro

#define ENCA 2 // YELLOW
#define ENCB 3 // WHITE

int motor1pin1 = 9;
int motor1pin2 = 10;
int motor2pin1 = 11;
int motor2pin2 = 12;

const int buttonPin = 8;
int buttonState = 0;
int a = true;

int pos = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENCA,INPUT);
  pinMode(ENCB,INPUT);
  pinMode(buttonPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(ENCA),readEncoder,RISING);

  digitalWrite(motor1pin1, HIGH);
  digitalWrite(motor1pin2, HIGH);
  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, HIGH);
  pinMode(motor1pin1, OUTPUT);
  pinMode(motor1pin2, OUTPUT);
  pinMode(motor2pin1, OUTPUT);
  pinMode(motor2pin2, OUTPUT);

  Serial.println("target pos");
}

void loop() {

  
  // put your main code here, to run repeatedly:   
  Serial.println(pos);
  buttonState = digitalRead(buttonPin);
  //Serial.println(buttonState == HIGH ? "HIGH" : "LOW");
  if (a) {
    digitalWrite(motor1pin1, LOW);
    digitalWrite(motor1pin2, HIGH);
    if (pos > 3000) {
      a = false;
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
      delay(2000);
    }
  } else {
    if (pos > 0) {
      digitalWrite(motor1pin1, HIGH);
      digitalWrite(motor1pin2, LOW);
    } else {
      digitalWrite(motor1pin1, LOW);
      digitalWrite(motor1pin2, LOW);
    }
  }
  /*

  digitalWrite(motor2pin1, HIGH);
  digitalWrite(motor2pin2, LOW);
  delay(1000);

  digitalWrite(motor1pin1, LOW);
  digitalWrite(motor1pin2, HIGH);

  digitalWrite(motor2pin1, LOW);
  digitalWrite(motor2pin2, HIGH);
  delay(1000);
  */
}

void readEncoder(){
  int b = digitalRead(ENCB);
  if(b > 0){
    pos++;
  }
  else{
    pos--;
  }
}
