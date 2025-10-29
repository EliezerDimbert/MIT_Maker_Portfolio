void handleButtons() {
  if (!digitalRead(nextButton)) {
    nextButtonHoldTime++;
  } else {
    nextButtonHoldTime = 0;
  }
  if (!digitalRead(repeatButton)) {
    repeatButtonHoldTime++;
  } else {
    repeatButtonHoldTime = 0;
  }
  Serial.print(" ||| " + String(nextButtonHoldTime) + ", " + String(repeatButtonHoldTime));
  dictateButtonAction(nextButtonHoldTime, repeatButtonHoldTime);
}

void dictateButtonAction(uint8_t RBHoldTime, uint8_t NBHoldTime) {
  int actionDelay = 50;
  if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
    delay(100);
    if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
      Serial.println(F("FORCED NEXT DIRECTION"));
      playNextDirection();  //Goto direction funcs
      step++;
    }

  } else if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
    delay(100);
    if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
      Serial.println(F("PLAY CURR DIRECTION"));
      playCurrentDirection();
    }


  } else if (RBHoldTime >= 30 && NBHoldTime >= 30) {
    Serial.println(F("NEW ROOM"));
    nextButtonHoldTime = 60;
    repeatButtonHoldTime = 60;
    selectNewRoom();
  }
}


/*
void dictateButtonAction(uint8_t RBHoldTime, uint8_t NBHoldTime) {
  int actionDelay = 200;
  if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
    delay(100);
    if (NBHoldTime >= actionDelay && RBHoldTime < actionDelay) {
      Serial.println(F("FORCED NEXT DIRECTION"));
      playNextDirection();  //Goto direction funcs
      step++;
    } else if (NBHoldTime >= actionDelay && RBHoldTime >= actionDelay) {
      selectNewRoom();
    }
  } else if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
    delay(100);
    if (RBHoldTime >= actionDelay && NBHoldTime < actionDelay) {
      playCurrentDirection();
    } else if (RBHoldTime >= actionDelay && NBHoldTime >= actionDelay) {
      selectNewRoom();
    }
  }
}
*/