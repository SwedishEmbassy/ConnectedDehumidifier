const int buttonPin = 3;
const int ledOnPin = A0;
const int ledFullPin = A5;

int isOn = 0;
int isFull = 0;

int isOnUpdated = false;
int isFullUpdated = false;

int toggleOn(String extra);
int readOn(String extra);
int readFull(String extra);

void setup() {
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);

  Particle.variable("isOn", isOn);
  Particle.variable("isFull", isFull);

  Particle.function("toggleOn", toggleOn);
  Particle.function("readOn", readOn);
  Particle.function("readFull", readFull);
}

void loop() {
  int readIsOn = readOn("");
  int readIsFull = readFull("");

  if(readIsOn != isOn || !isOnUpdated) {
      isOn = readIsOn;
      isOnUpdated = Particle.publish("isOnChanged", String(readIsOn), 60, PRIVATE);
  }

  if(readIsFull != isFull || !isFullUpdated) {
      isFull = readIsFull;
      isFullUpdated = Particle.publish("isFullChanged", String(readIsFull), 60, PRIVATE);
  }

  delay(1000);
}

int toggleOn(String extra) {
  Serial.println("Toggling power for Humidifier.");

  // Fake user holding down button.
  digitalWrite(buttonPin, LOW);
  Serial.println("Faked LOW");
  delay(200);

  // Fake user releasing button.
  digitalWrite(buttonPin, HIGH);
  Serial.println("Faked HIGH");

  Serial.println("Power toggled.");

  return 1;
}

int readOn(String extra) {
  int value = analogRead(ledOnPin);
  float voltage = convertValueToVoltage(value);

  if(voltage > 4.5) {
    Serial.println("Humidifier is OFF");
    return 0;
  } else {
    Serial.println("Humidifier is ON");
    return 1;
  }
}

int readFull(String extra) {
  int value = analogRead(ledFullPin);
  float voltage = convertValueToVoltage(value);

  if(voltage > 4.5) {
    Serial.println("Humidifier is NOT FULL");
    return 0;
  } else {
    Serial.println("Humidifier is FULL");
    return 1;
  }
}

float convertValueToVoltage(int value) {
  return value * (5.0 / 1023.0);
}

