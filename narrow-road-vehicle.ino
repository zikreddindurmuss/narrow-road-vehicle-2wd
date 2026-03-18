#include <Arduino.h>

// ----------- MOTOR PINLERI -----------
const int IN1 = 5;
const int IN2 = 6;
const int ENA = 9;
const int IN3 = 7;
const int IN4 = 8;
const int ENB = 10;

// ----------- SENSOR PINLERI -----------
const int trigPinSag = 2;
const int echoPinSag = 3;
const int trigPinSol = 4;
const int echoPinSol = 11;
const int trigPinOn = 12;
const int echoPinOn = 13;

// ----------- DEGISKENLER -----------
int mesafeOn, mesafeSag, mesafeSol;

// ----------- MESAFE OKUMA -----------
int mesafeOku(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long sure = pulseIn(echoPin, HIGH, 25000);
  if (sure == 0) return 300;
  return sure * 0.034 / 2;
}

// ----------- SENSOR OKUMA -----------
void sensorHepsiniOku() {
  mesafeSag = mesafeOku(trigPinSag, echoPinSag);
  delay(20);
  mesafeOn = mesafeOku(trigPinOn, echoPinOn);
  delay(20);
  mesafeSol = mesafeOku(trigPinSol, echoPinSol);
  delay(20);
}

// ----------- CIKMAZ SOKAK -----------
bool cikmazSokakKontrol() {
  int sayac = 0;
  for (int i = 0; i < 5; i++) {
    sensorHepsiniOku();
    if (mesafeOn <= 15 && mesafeSag < 15 && mesafeSol < 15) {
      sayac++;
    }
    delay(40);
  }
  return (sayac >= 4);
}

// ----------- MOTOR KONTROL -----------
void motorDur() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW); analogWrite(ENA, 0);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW); analogWrite(ENB, 0);
}

void motorIleri() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 180);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 180);
}

void motorYavas() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 130);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 130);
}

void motorSag() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 180);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 70);
}

void motorSol() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); analogWrite(ENA, 70);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 180);
}

void motorTamDonus() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); analogWrite(ENA, 160);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); analogWrite(ENB, 160);
  delay(600);
  motorDur();
}

// ----------- ANA LOOP -----------
void setup() {
  Serial.begin(9600);
  pinMode(trigPinSag, OUTPUT); pinMode(echoPinSag, INPUT);
  pinMode(trigPinSol, OUTPUT); pinMode(echoPinSol, INPUT);
  pinMode(trigPinOn, OUTPUT);  pinMode(echoPinOn, INPUT);
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT); pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT); pinMode(ENB, OUTPUT);
  motorDur();
}

void loop() {
  sensorHepsiniOku();

  Serial.print("ON: ");
  Serial.print(mesafeOn);
  Serial.print(" | SAG: ");
  Serial.print(mesafeSag);
  Serial.print(" | SOL: ");
  Serial.println(mesafeSol);

  if (mesafeOn > 25) {
    motorIleri();
  }
  else if (mesafeOn > 15) {
    motorYavas();
  }
  else {
    if (cikmazSokakKontrol()) {
      Serial.println("CIKMAZ SOKAK -> U DONUS");
      motorTamDonus();
    }
    else {
      if (mesafeSag > mesafeSol && mesafeSag >= 15) {
        motorSag();
      }
      else if (mesafeSol > mesafeSag && mesafeSol >= 15) {
        motorSol();
      }
      else {
        motorDur();
      }
    }
  }

  delay(100);
}