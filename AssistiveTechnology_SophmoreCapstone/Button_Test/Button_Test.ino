const int repeatButton = 30;
const int nextButton = 52;
uint32_t repeatButtonHoldTime = 0;
uint32_t nextButtonHoldTime = 0;

void setup() {
  pinMode(repeatButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);

  Serial.begin(9600);
  Serial.println("Setup done");
}

void loop() {
  handleButtons();
}

void handleButtons() {
  if (!digitalRead(nextButton)) {
    nextButtonHoldTime++;
    Serial.println(nextButtonHoldTime);
  } else {
    nextButtonHoldTime = 0;
  }

  if (!digitalRead(repeatButton)) {
    repeatButtonHoldTime++;
    Serial.println("\t" + String(repeatButtonHoldTime));
  } else {
    repeatButtonHoldTime = 0;
  }
  dictateButtonAction(nextButtonHoldTime, repeatButtonHoldTime);
}

void dictateButtonAction(uint8_t RBHoldTime, uint8_t NBHoldTime) {
  int actionDelay = 200;
  if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
    delay(100);
    if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
      Serial.println(F("FORCED NEXT DIRECTION"));
    }

  } else if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
    delay(100);
    if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
      Serial.println(F("PLAY CURR DIRECTION"));
    }


  } else if (RBHoldTime >= 50 && NBHoldTime >= 50) {
    Serial.println(F("NEW ROOM"));
    nextButtonHoldTime = 60;
    repeatButtonHoldTime = 60;
  }
}
