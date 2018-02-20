int crojo = 13;
int camarillo = 12;
int cverde = 11;
int projo = 6;
int pverde = 7;
int pulsador = 2;;
int state = LOW;
int frec = 1000;

void setup() {
  // put your setup code here, to run once:
  pinMode(crojo, OUTPUT);
  pinMode(camarillo, OUTPUT);
  pinMode(cverde, OUTPUT);
  pinMode(projo, OUTPUT);
  pinMode(pverde, OUTPUT);
  pinMode(pulsador, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  frec = analogRead(A0);
  digitalWrite(projo, HIGH);
  digitalWrite(cverde, HIGH);
  if (digitalRead(pulsador) == LOW) {
    state = HIGH;
  } else {
    state = LOW;
  }
  if (state == HIGH) {
    delay(frec);
    digitalWrite(cverde, LOW);
    digitalWrite(camarillo, HIGH);
    delay(frec);
    digitalWrite(camarillo, LOW);
    digitalWrite(projo, LOW);
    digitalWrite(pverde, HIGH);
    digitalWrite(crojo, HIGH);
    delay(frec);
    digitalWrite(crojo, LOW);
    digitalWrite(pverde, LOW);
    state = LOW;
  } else {
    digitalWrite(projo, HIGH);
    digitalWrite(cverde, HIGH);
  }
}
