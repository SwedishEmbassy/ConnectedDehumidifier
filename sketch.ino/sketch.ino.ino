const int buttonPin = 2;
const int ledOnPin = A0;
const int ledFullPin = A1;

void setup() {
  // Set button pin to HIGH immediately, otherwise humidifier toggles state on start.
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  
  Serial.begin(9600);
}

void toggleOn() {
  Serial.println("Toggling power for Humidifier.");
  
  // Fake user holding down button.
  digitalWrite(buttonPin, LOW);
  Serial.println("Faked LOW");
  delay(200);

  // Fake user releasing button.
  digitalWrite(buttonPin, HIGH);
  Serial.println("Faked HIGH");

  Serial.println("Power toggled.");
}

void loop() {
  readOnState();
  readFullState();
  Serial.println();
  delay(1000);
}

void readOnState() {  
  int value = analogRead(ledOnPin);
  float voltage = convertValueToVoltage(value);
  
  if(voltage > 4.5) {
    Serial.println("Humidifier is OFF");
  } else {
    Serial.println("Humidifier is ON");
  }
}

void readFullState() {  
  int value = analogRead(ledFullPin);
  float voltage = convertValueToVoltage(value);
  
  if(voltage > 4.5) {
    Serial.println("Humidifier is NOT FULL");
  } else {
    Serial.println("Humidifier is FULL");
  }
}

float convertValueToVoltage(int value) {
  return value * (5.0 / 1023.0);
}
