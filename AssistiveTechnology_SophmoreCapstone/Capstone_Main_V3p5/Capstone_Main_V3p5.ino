const bool debug = true;

const int repeatButton = 30;
const int nextButton = 52;
uint8_t destination = 0;
uint8_t startingPoint = 0;
bool routeEnd = true;
bool WWBuffer = false;

//********************DIRECTION VARS********************
int step = 0;
int room = 0;
const byte NUM_ROOMS = 11; 
/* 
Best if even # bc we only need to to half of the rooms
b/c getting from room 2 -> room 1 is just room 1 -> room 2 reversed
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

  if (!digitalRead(nextButton) && !digitalRead(repeatButton)) { //Both buttons pressed
    selectNewRoom();
  } else if (!digitalRead(nextButton)) {
    Serial.println(F("FORCED NEXT DIRECTION"));
    playNextDirection();  //Goto direction funcs
    step++;
  } else if (!digitalRead(repeatButton)) {
    playCurrentDirection();
  }

  delay(10);
}

void selectNewRoom() {
  bool selectionDone = false;
  routeEnd = false;
  Serial.println(F("Started selecting new room"));
  playSound("KnS");
  delay(1000);

  while (!selectionDone) {  //Switch starting
    Serial.println(F("Selecting new startingPoint"));
    int currentReading = analogRead(A11);
    int startingPointToSwitchTo = map(currentReading, 30, 1027, 0, NUM_ROOMS);
    if (startingPointToSwitchTo != startingPoint) {
      startingPoint = startingPointToSwitchTo;
      playRoom(startingPoint);
    }
    if (!digitalRead(nextButton) && !digitalRead(repeatButton)) {
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
    int currentReading = analogRead(A11); // Need to change
    int destinationToSwitchTo = map(currentReading, 30, 1020, 0, NUM_ROOMS);
    if (destinationToSwitchTo != destination) {
      delay(100);
      destination = destinationToSwitchTo;
      playRoom(destination);
    }
    if (!digitalRead(nextButton) && !digitalRead(repeatButton)) {
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
