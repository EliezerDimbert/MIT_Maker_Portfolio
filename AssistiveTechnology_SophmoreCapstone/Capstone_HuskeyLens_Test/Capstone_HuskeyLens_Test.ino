#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

const int NUM_ROOMS = 11;
const int MAX_STEPS = 8;

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);  // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
void printResult(HUSKYLENSResult result);
int lastIdRead = 0;
int step = 0;
int room = 0;

const byte tagsRoomToRoom[NUM_ROOMS][NUM_ROOMS][MAX_STEPS] PROGMEM = {
  {
    //Entrence
    {},                 //To entrence
    { 1, 2, 3, 4 },     //To R1
    { 5, 6, 7, 8 },     //To R2
    { 9, 10, 11, 12 },  //To R3
  }
};

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  while (!huskylens.begin(mySerial)) {
    Serial.println(F("Begin failed!"));
  }
  setupTagNames();
}

void loop() {
  int nextTagToRead = pgm_read_byte(&tagsRoomToRoom[0][room][step]);
  if (nextTagToRead == 0) {
    step = 0;
    room++;
    Serial.println("****ARRIVED****");
    delay(2000);
  }
  HUSKYLENSResult result;
  if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
  else if (huskylens.available()) result = huskylens.read();
  if (lastIdRead != result.ID) {
    Serial.println("ID = " + String(result.ID));
    lastIdRead = result.ID;

    if (result.ID == nextTagToRead) {  //Simple test to see if tag that is read is next tag in order
      Serial.println("CORRECT TAG FOUND");
      
      step++;
    } else {
      Serial.print("WRONG TAG FOUND ");
    }
  } else if (!huskylens.available()) Serial.println("LOOKING FOR TAG " + String(nextTagToRead));
  
}

/*
void printResult(HUSKYLENSResult result) {
  if (result.command == COMMAND_RETURN_BLOCK) {
    Serial.println(String() + F("Block:xCenter=") + result.xCenter + F(",yCenter=") + result.yCenter + F(",width=") + result.width + F(",height=") + result.height + F(",ID=") + result.ID);
  } else if (result.command == COMMAND_RETURN_ARROW) {
    Serial.println(String() + F("Arrow:xOrigin=") + result.xOrigin + F(",yOrigin=") + result.yOrigin + F(",xTarget=") + result.xTarget + F(",yTarget=") + result.yTarget + F(",ID=") + result.ID);
  } else {
    Serial.println("Object unknown!");
  }
}
*/