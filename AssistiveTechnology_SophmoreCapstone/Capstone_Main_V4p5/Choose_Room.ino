// Upstairs Array
const byte switchingFloorTags[2][2][9] PROGMEM{
  {
    //From Entrance
    { 18, 19, 20, 21 },         //to stairs
    { 18, 19, 20, 21, 22, 23 }  // to elevator
  },

  {
    // From elevator
    { 23, 22, 21, 20, 19, 18 },  // to entrance
    { 21, 20, 19, 18 }           // to stairs
  }
};

bool useUpstairTags = 0;




void selectNewRoom() {
  bool selectionDone = false;
  routeEnd = false;
  Serial.println(F("Started selecting new room"));
  playSound("KnS");
  playSound("Cnfrm");
  delay(1000);

  while (!selectionDone) {  //Switch starting
    Serial.println(F("Selecting new startingPoint"));
    int currentReading = analogRead(A11);
    int startingPointToSwitchTo = map(currentReading, 30, 1027, 0, NUM_ROOMS);
    if (startingPointToSwitchTo != startingPoint) {
      startingPoint = startingPointToSwitchTo;
      playRoom(startingPoint);
    }
    if (!digitalRead(nextButton) || !digitalRead(repeatButton)) {
      selectionDone = true;
      Serial.println("STARTING POINT CHANGED TO " + String(startingPoint));
      delay(1000);
    }
    delay(100);
  }

  selectionDone = false;
  playSound("KnE");
  while (!selectionDone) {  //Switch destination
    Serial.println(F("Selecting new destination"));
    int currentReading = analogRead(A11);  // Need to change
    int destinationToSwitchTo = map(currentReading, 30, 1020, 0, NUM_ROOMS);
    if (destinationToSwitchTo != destination) {
      delay(100);
      destination = destinationToSwitchTo;
      playRoom(destination);
    }
    if (!digitalRead(nextButton) || !digitalRead(repeatButton)) {
      if (startingPoint == destination) {
        playSound("Inv");
        Serial.println("INVALID DESTINATION SELECTION");
      } else {
        selectionDone = true;
        Serial.println("DESTINATION POINT CHANGED TO " + String(destination));
        delay(1000);
      }
    }
    delay(100);
  }

  WWBuffer = false;
  Serial.println(F("DONE CHANGING ROOM"));
  step = 0;
  playNextDirection();
  step++;
  delay(1000);
}

void selectWayDwn() {
  int chosenWayDwn = 0;

  useUpstairTags = 1;
  bool selectionDone = false;
  routeEnd = false;
  Serial.println(F("Started selecting way dwn"));
  delay(1000);

  startingPoint = 1;  // Since we are using upstairs Tags, this means starting point = main entrence

  playSound("KnE");         //Need another sound. "Select way Down"
  while (!selectionDone) {  //Switch destination
    Serial.println(F("Selecting new destination"));
    int currentReading = analogRead(A11);  // Need to change
    int chosenWayDwnToSwitchTo = map(currentReading, 30, 1020, 0, 2);
    if (chosenWayDwnToSwitchTo != chosenWayDwn) {
      delay(100);
      chosenWayDwn = chosenWayDwnToSwitchTo;
      playWayDwn(chosenWayDwn);
    }
    if (!digitalRead(nextButton) || !digitalRead(repeatButton)) {
      selectionDone = true;
      Serial.println("DESTINATION POINT CHANGED TO " + String(chosenWayDwn));
      delay(1000);
    }
    delay(100);

    destination = chosenWayDwn - 1;  // 0 or 1 for "to stairs" and "to entrence"

    WWBuffer = false;
    Serial.println(F("DONE CHANGING ROOM"));
    step = 0;
    playNextDirection();
    step++;
    delay(1000);
  }

  void switchFloors(int currFloor) {
    switch (currFloor) {
      case 1:  //Starting Up
        selectWayDwn();
        break;

      case 0:  //Starting Dwn

        break;

      default:
        Serial.println(F("ERROR SWITCHING FLOORS"));
        break;
    }
  }
