#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);  // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
int lastIdRead = 0;


const byte roomToRoomTags[NUM_ROOMS][NUM_ROOMS][MAX_STEPS] PROGMEM = {
  {
    //Entrence
    {},              //To entrence
    { 2, 3 },        //To R1
    { 4, 5, 6 },     //To R2
    { 7, 8, 9, 10 },  //To R3
  }
};

void setupTagNames() {
  String tagNames[] = { "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "H10", "H11", "H12", "H13", "H14", "H15", "H16", "H17", "H18", "H19", "H20", "H21", "H22", "H23", "H24" };

  for (int i = 0; i < 24; i++) {
    huskylens.setCustomName(tagNames[i], i + 1);
  }
}

void huskeybegin() {
  mySerial.begin(9600);
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("HUSKEY failed!"));
  }
  setupTagNames();
}

bool checkArrival() {
  if (pgm_read_byte(&roomToRoomTags[0][room][step]) == 0) {
    return true;
  }
  return false;
}

bool tagCorrect(int tagID, int nextTagToRead) {
  if (tagID == nextTagToRead) {  //Simple test to see if tag that is read is next tag in order
    Serial.println(F("CORRECT TAG FOUND"));
    return true;
  } else {
    Serial.println(F("WRONG TAG FOUND "));
    return false;
  }
}

void processHuskey() {
  int nextTagToRead = pgm_read_byte(&roomToRoomTags[0][room][step]);
  if (nextTagToRead == 0) {
    step = 0;
    room++;
    facingDirection = 'N';
    Serial.println("****ARRIVED****");
    playSound("Arr");
    delay(2000);
    return;
  }
  HUSKYLENSResult result;
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if (huskylens.available()) result = huskylens.read();
  if (lastIdRead != result.ID) {
    Serial.println("ID = " + String(result.ID));
    lastIdRead = result.ID;

    if (result.ID == nextTagToRead) {  //Simple test to see if tag that is read is next tag in order
      Serial.println("CORRECT TAG FOUND");
      playNextDirection();  //Goto direction funcs
      step++;
    } else {
      Serial.print("WRONG TAG FOUND ");
    }
  } else if (!huskylens.available()) Serial.println("LOOKING FOR TAG " + String(nextTagToRead));
}
