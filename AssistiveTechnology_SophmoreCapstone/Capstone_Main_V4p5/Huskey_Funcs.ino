#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11);  // RX, TX
//HUSKYLENS green line >> Pin 10; blue line >> Pin 11
int lastIdRead = -1;


const byte roomToRoomTags[NUM_ROOMS][NUM_ROOMS][MAX_STEPS] PROGMEM = {

  //From stairs
  {
    //stairs
    {},
    { 2, 3 },                 //1
    { 2, 3, 4 },              //2
    { 2, 3, 4, 5 },           //3
    { 2, 3, 4, 5, 6, 17 },    //4
    { 2, 3, 4, 5, 6, 7 },     //5
    { 2, 3, 4, 5, 6, 7, 8 },  //6
    { 2, 9, 10 },             //7
    { 2, 9, 10, 11, 15 },     //8
    { 2, 9, 10, 13 },         //9
    { 2, 9, 16 },             //10
    { 2, 9, 16 }              //elevator

  },

  //From  1
  {
    { 3, 2 },                 //stairs
    {},                       //1
    { 3, 4 },                 //2
    { 3, 4, 5 },              //3
    { 3, 4, 5, 6, 17 },       //4
    { 3, 4, 5, 6, 7 },        //5
    { 3, 4, 5, 6, 7, 8 },     //6
    { 3, 2, 9, 10 },          //7
    { 3, 2, 9, 10, 11, 15 },  //8
    { 3, 2, 9, 10, 13 },      //9
    { 3, 2, 9, 16 },          //10
    { 3, 2, 9, 16 }           //elevator

  },

  //From 2
  {

    { 4, 3, 2 },                 // stairs
    { 4, 3 },                    //1
    {},                          //2
    { 4, 5 },                    //3
    { 4, 5, 6, 17 },             //4
    { 4, 5, 6, 7 },              //5
    { 4, 5, 6, 7, 8 },           //6
    { 4, 3, 2, 9, 10 },          //7
    { 4, 3, 2, 9, 10, 11, 15 },  //8
    { 4, 3, 2, 9, 10, 13 },      //9
    { 4, 3, 2, 9, 16 },          //10
    { 4, 3, 2, 9, 16 }           //elevator
  },

  //From 3
  {
    { 5, 4, 3, 2 },              // stairs
    { 5, 4, 3 },                 //1
    { 5, 4 },                    //2
    {},                          //3
    { 5, 6, 17 },                //4
    { 5, 6, 7 },                 //5
    { 5, 6, 7, 8 },              //6
    { 5, 4, 3, 2, 9, 10 },       //7
    { 5, 4, 3, 2, 10, 11, 15 },  //8
    { 5, 4, 3, 2, 9, 10, 13 },   //9
    { 5, 4, 3, 2, 9, 16 },       //10
    { 5, 4, 3, 2, 9, 16 }        //elevator
  },

  // FROM 4
  {

    { 17, 6, 5, 4, 3, 2 },                 //stairs
    { 17, 6, 5, 4, 3, 1 },                 //1
    { 17, 6, 5, 4 },                       //2
    { 17, 6, 5 },                          //3
    {},                                    //4
    { 17, 6, 7 },                          //5
    { 17, 6, 7, 8 },                       //6
    { 17, 6, 5, 4, 3, 2, 9, 10 },          //7
    { 17, 6, 5, 4, 3, 2, 9, 10, 11, 15 },  //8
    { 17, 6, 5, 4, 3, 2, 9, 10, 13 },      //9
    { 17, 6, 5, 4, 3, 2, 9, 16 },          //10
    { 17, 6, 5, 4, 3, 2, 9, 16 }           //elevator
  },

  //From 5
  {

    { 7, 6, 5, 4, 3, 2 },                 //stairs
    { 7, 6, 5, 4, 3 },                    //1
    { 7, 6, 5, 4 },                       //2
    { 7, 6, 5 },                          //3
    { 7, 6, 17 },                         //4
    {},                                   //5
    { 7, 8 },                             //6
    { 7, 6, 5, 4, 3, 2, 9, 10 },          //7
    { 7, 6, 5, 4, 3, 2, 9, 10, 11, 15 },  //8
    { 7, 6, 5, 4, 3, 2, 9, 10, 13 },      //9
    { 7, 6, 5, 4, 3, 2, 9, 16 },          //10
    { 7, 6, 5, 4, 3, 2, 9, 16 },          //elevator
  },

  //FROM 6
  {
    { 8, 7, 6, 5, 4, 3, 2 },                 //stairs
    { 8, 7, 6, 5, 4, 3 },                    //1
    { 8, 7, 6, 5, 4 },                       //2
    { 8, 7, 6, 5 },                          //3
    { 8, 7, 6, 17 },                         //4
    { 8, 7 },                                //5
    {},                                      //6
    { 8, 7, 6, 5, 4, 3, 2, 9, 10 },          //7
    { 8, 7, 6, 5, 4, 3, 2, 9, 10, 11, 15 },  //8
    { 8, 7, 6, 5, 4, 3, 2, 9, 10, 13 },      //9
    { 8, 7, 6, 5, 4, 3, 2, 9, 16 },          //10
    { 8, 7, 6, 5, 4, 3, 2, 9, 16 },          //elevator
  },

  //From 7
  {
    { 10, 9, 2 },                    //stairs
    { 10, 9, 2, 3, 1 },              //1
    { 10, 9, 2, 3, 4 },              //2
    { 10, 9, 2, 3, 4, 5 },           //3
    { 10, 9, 2, 3, 4, 5, 6, 17 },    //4
    { 10, 9, 2, 3, 4, 5, 6, 7 },     //5
    { 10, 9, 2, 3, 4, 5, 6, 7, 8 },  //6
    {},                              //7
    { 10, 11, 15 },                  //8
    { 10, 13 },                      //9
    { 10, 9, 16 },                   //10
    { 10, 9, 16 }                    //Elevator
  },

  //From 8
  {
    { 15, 11, 10, 9, 2 },                    //stairs
    { 10, 9, 2, 3, 1 },                      //1
    { 15, 11, 10, 9, 2, 3, 4 },              //2
    { 15, 11, 10, 9, 2, 3, 4, 5 },           //3
    { 15, 11, 10, 9, 2, 3, 4, 5, 6, 17 },    //4
    { 15, 11, 10, 9, 2, 3, 4, 5, 6, 7 },     //5
    { 15, 11, 10, 9, 2, 3, 4, 5, 6, 7, 8 },  //6
    { 15, 11, 10 },                          //7
    {},                                      //8
    { 15, 12, 13 },                          //9
    { 12, 13, 14, 16 },                      //10
    { 12, 13, 14, 16 }                       //elevator

  },

  //From 9
  {
    { 13, 10, 9, 2 },                    //stairs
    { 13, 10, 9, 2, 3, 1 },              //1
    { 13, 10, 9, 2, 3, 4 },              //2
    { 13, 10, 9, 2, 3, 4, 5 },           //3
    { 13, 10, 9, 2, 3, 4, 5, 6, 17 },    //4
    { 13, 10, 9, 2, 3, 4, 5, 6, 7 },     //5
    { 13, 10, 9, 2, 3, 4, 5, 6, 7, 8 },  //6
    { 13, 10 },                          //7
    { 13, 12, 15 },                      //8
    {},                                  //9
    { 13, 14, 16 },                      //10
    { 13, 14, 16 }                       //elevator

  },

  //From 10
  {
    { 16, 9, 2 },                    //stairs
    { 16, 9, 2, 3, 1 },              //1
    { 16, 9, 2, 3, 4 },              //2
    { 16, 9, 2, 3, 4, 5 },           //3
    { 16, 9, 2, 3, 4, 5, 6, 17 },    //4
    { 16, 9, 2, 3, 4, 5, 6, 7 },     //5
    { 16, 9, 2, 3, 4, 5, 6, 7, 8 },  //6
    { 16, 9, 10 },                   //7
    { 16, 9, 10, 11, 15 },           //8
    { 16, 14, 13 },                  //9
    {},                              //10
    { 16 }                           //elevator
  },

  //From elevator
  {
    { 16, 9, 2 },                    //entrance
    { 16, 9, 2, 3, 1 },              //1
    { 16, 9, 2, 3, 4 },              //2
    { 16, 9, 2, 3, 4, 5 },           //3
    { 16, 9, 2, 3, 4, 5, 6, 17 },    //4
    { 16, 9, 2, 3, 4, 5, 6, 7 },     //5
    { 16, 9, 2, 3, 4, 5, 6, 7, 8 },  //6
    { 16, 9, 10 },                   //7
    { 16, 9, 10, 11, 15 },           //8
    { 16, 14, 13 },                  //9
    { 16 },                          //10
    {}                               //elevator

  }


};

void huskeySetup() {
  mySerial.begin(9600);
  if (!huskylens.begin(mySerial)) {
    Serial.println(F("HUSKEY failed!"));
  }
}

bool checkArrival() {
  if (pgm_read_byte(&roomToRoomTags[startingPoint][destination][step]) == 0) {
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

void inverseFacingDirection() {
  switch (facingDirection) {
    case 'N':
      facingDirection = 'S';
      break;
    case 'E':
      facingDirection = 'W';
      break;
    case 'S':
      facingDirection = 'N';
      break;
    case 'W':
      facingDirection = 'E';
      break;
  }
  lastFacingDirection = 'X';
}

void processHuskey() {
  if (routeEnd == false) {
    if (!useUpstairTags) {
      int nextTagToRead = pgm_read_byte(&roomToRoomTags[startingPoint][destination][step]);
    } else if (useUpstairTags) {
      int nextTagToRead = pgm_read_byte(&switchingFloorTags[startingPoint][destination][step]);
    }
    if (nextTagToRead == 0) {
      step = 0;
      startingPoint = 0;
      inverseFacingDirection();
      Serial.println("****ARRIVED****");
      playSound("Arr");
      playRoom(destination);
      destination = 0;
      routeEnd = true;
      return;
    }

    HUSKYLENSResult result;
    // if (!huskylens.request()) Serial.println(F("Fail to request data from HUSKYLENS, recheck the connection!"));
    // else
    if (huskylens.available()) result = huskylens.read();
    if (lastIdRead != result.ID && (result.ID != 0 || result.ID != 1)) {
      Serial.println("ID = " + result.ID);
      lastIdRead = result.ID;

      if (result.ID == nextTagToRead) {  //Simple test to see if tag that is read is next tag in order
        Serial.println("CORRECT TAG FOUND");
        playNextDirection();  //Goto direction funcs
        step++;
      } else {
        if (WWBuffer) {
          Serial.print("WRONG TAG FOUND ");
          playSound("Bck");
        } else {
          WWBuffer = true;
          Serial.println(F("BUFFER ACTIVATED"));
        }
      }
    } else if (!huskylens.available()) {
      Serial.print("LOOKING FOR TAG " + String(nextTagToRead));
    } else {
      Serial.println(F("NOT LOOKING FOR TAGS B/C NO ROUT SELECTED"));
    }
  }
}
