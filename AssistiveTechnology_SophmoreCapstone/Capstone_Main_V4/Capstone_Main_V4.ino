const bool debug = true;

const int repeatButton = 30;
const int nextButton = 52;
uint16_t repeatButtonHoldTime = 0;
uint16_t nextButtonHoldTime = 0;

uint8_t destination = 0;
uint8_t startingPoint = 0;
bool routeEnd = true;
bool WWBuffer = false;

//********************DIRECTION VARS********************
int step = 0;
int room = 0;
const byte NUM_ROOMS = 12;
/* 
Best if even # bc we only need to to half of the rooms
b/c getting from room 2 -> room 1 is just room 1 -> room 2 reversed
EDIT: Was good idea but too complicate. Scrapped.
*/

const byte MAX_STEPS = 11;

//********************SETUP********************
void setup() {
  pinMode(repeatButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);

  Serial.begin(9600);
  audioSetup();
  huskeySetup();

  Serial.println();
  playSound("Srt");
  selectNewRoom();
}



//********************LOOP********************
void loop() {

  processHuskey();
  handleButtons();
  Serial.println(F(""));
  delay(10);
}

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
  int actionDelay = 60;
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


void selectNewRoom() {
  bool selectionDone = false;
  routeEnd = false;
  Serial.println(F("Started selecting new room"));
  playSound("KnS");
  delay(1000);

  while (!selectionDone) {  //Switch starting
    Serial.println(F("Selecting new startingPoint"));
    int currentReading = analogRead(A9);
    int startingPointToSwitchTo = map(currentReading, 30, 1027, 0, NUM_ROOMS - 1);
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
  changeFacingDirectionToNewRoom(startingPoint);
  selectionDone = false;
  playSound("KnE");
  while (!selectionDone) {  //Switch destination
    Serial.println(F("Selecting new destination"));
    int currentReading = analogRead(A9);  // Need to change
    int destinationToSwitchTo = map(currentReading, 30, 1020, 0, NUM_ROOMS - 1);
    if (destinationToSwitchTo != destination) {
      delay(100);
      destination = destinationToSwitchTo;
      playRoom(destination);
    }
    if (!digitalRead(nextButton) || !digitalRead(repeatButton)) {
      selectionDone = true;
      Serial.println("DESTINATION POINT CHANGED TO " + String(destination));
      delay(1000);
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
