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
const byte NUM_ROOMS = 13;
/* 
Best if even # bc we only need to to half of the rooms
b/c getting from room 2 -> room 1 is just room 1 -> room 2 reversed
EDIT: Was good idea but too complicated. Scrapped.
Rooms:
 Stairs
 Elevator
 Main Entrence
 R 1-10
 Total: 13
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
  switchFloors(1);
}



//********************LOOP********************
void loop() {

  processHuskey();
  handleButtons();
  Serial.println(F(""));
  delay(10);
}
