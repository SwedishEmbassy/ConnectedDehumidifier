const int buttonPin = 3;
const int onPin = A0;
const int fullPin = A1;

bool isOn = false;
bool isFull = false;

void setup() {
  // Set button pin to HIGH immediately, otherwise humidifier toggles state on start.
  pinMode(buttonPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);
  
  Serial.begin(9600);
}

void loop() {
  String command = readSerial();
  
  if (command == "toggle_power") {
    togglePower();
  }
  
  bool readIsOn = readOnState();
  bool readIsFull = readFullState();
  
  if(readIsOn != isOn) {
    isOn = readIsOn;
    Serial.println("{\"event\": \"on_state_changed\", \"new_value\": " + String(isOn) + "}");
  }

  if(readIsFull != isFull) {
    isFull = readIsFull;
    Serial.println("{\"event\": \"full_state_changed\", \"new_value\": " + String(isFull) + "}");
  }
  
  delay(1000);

}

String readSerial() {
  String command = "";
  
  while(Serial.available()) {
    char character = Serial.read();
    command.concat(character); 
  }

  return command;
}

void togglePower() {  
  // Fake user holding down button.
  digitalWrite(buttonPin, LOW);
  
  delay(200);
  
  // Fake user releasing button.
  digitalWrite(buttonPin, HIGH);

  Serial.println("{\"event\": \"power_toggled\"}");
}

bool readOnState() {  
  int value = analogRead(onPin);
  float voltage = convertValueToVoltage(value);

  if(voltage > 4.5) {
    return false;
  } else {
    return true;
  }
}

bool readFullState() {  
  int value = analogRead(fullPin);
  float voltage = convertValueToVoltage(value);

  if(voltage > 4.5) {
    return false;
  } else {    
    return true;
  }
}

float convertValueToVoltage(int value) {
  return value * (5.0 / 1023.0);
}

