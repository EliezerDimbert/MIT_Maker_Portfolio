const byte UP = byte(1);
const byte DOWN = byte(-1);  //Saved as 255 or 11111111
const byte RIGHT = byte(10);
const byte LEFT = byte(-10);  //Saved as 246 or 11110110

char facingDirection = 'N';
char lastFacingDirection = 'N';


/*
________________________
|-23 -13 -3  7 17 27 37 |
|-24 -14 -4  6 16 26 36 |
|-25 -15 -5  5 15 25 35 |
|-26 -16 -6  4 14 24 34 |
|-27 -17 -7  3 13 23 33 |
|-28 -18 -8  2 12 22 32 | 
|-29 -19 -9  1 11 21 31 |
|-30 -20 -10 0 10 20 30 | 
|____________^___________

(floor 2 could just be +100 or smthn)
*/
const byte roomToRoomDirections[NUM_ROOMS][NUM_ROOMS][MAX_STEPS] PROGMEM = {
  {
    //Entrence
    {},                                              //To Entrence
    { DOWN, DOWN },                                  //To R1
    { DOWN, RIGHT, UP },                             //To R2
    { DOWN, RIGHT, RIGHT, UP },                      //To R3
    { DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { UP, UP, RIGHT },                               //To R7
    { UP, UP, UP, LEFT, UP },                        //To R8
    { UP, UP, LEFT, LEFT },                          //To R9
    { UP, LEFT, UP },                                //To R10
    { UP, LEFT, DOWN }                               // elevator
  },
  {
    //R1
    { UP, RIGHT },                             //To Entrence
    {},                                        //To R1
    { RIGHT, UP },                             //To R2
    { RIGHT, RIGHT, UP },                      //To R3
    { RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { UP, UP, UP, RIGHT },                     //To R7
    { UP, UP, UP, UP, LEFT, UP },              //To R8
    { UP, UP, UP, LEFT, LEFT },                //To R9
    { UP, UP, LEFT, UP },                      //To R10
    { UP, UP, LEFT, DOWN }                     //ELEVATOR
  },
  {
    //R2
    { LEFT, UP, RIGHT },                 //To Entrence
    { LEFT, DOWN },                      //To R1
    {},                                  //To R2
    { RIGHT, UP },                       //To R3
    { RIGHT, DOWN, RIGHT, UP },          //To R4
    { RIGHT, DOWN, DOWN, RIGHT },        //To R5
    { RIGHT, DOWN, DOWN, DOWN, LEFT },   //To R6
    { LEFT, UP, UP, UP, RIGHT },         //To R7
    { LEFT, UP, UP, UP, UP, LEFT, UP },  //To R8
    { LEFT, UP, UP, UP, LEFT, LEFT },    //To R9
    { LEFT, UP, UP, LEFT, UP },          //To R10
    { LEFT, UP, UP, LEFT, DOWN }         //ELEVATOR
  },
  {
    //R3
    { LEFT, LEFT, UP, RIGHT },                 //To Entrence
    { LEFT, LEFT, DOWN },                      //To R1
    { LEFT, UP },                              //To R2
    {},                                        //To R3
    { DOWN, RIGHT, UP },                       //To R4
    { DOWN, DOWN, RIGHT },                     //To R5
    { DOWN, DOWN, DOWN, LEFT },                //To R6
    { LEFT, LEFT, UP, UP, UP, RIGHT },         //To R7
    { LEFT, LEFT, UP, UP, UP, UP, LEFT, UP },  //To R8
    { LEFT, LEFT, UP, UP, UP, LEFT, LEFT },    //To R9
    { LEFT, LEFT, UP, UP, LEFT, UP },          //To R10
    { LEFT, LEFT, UP, UP, LEFT, DOWN }         //ELEVATOR
  },
  {
    //R4
    { LEFT, UP, LEFT, LEFT, UP, RIGHT },                 //To Entrence
    { LEFT, UP, LEFT, LEFT, DOWN },                      //To R1
    { LEFT, LEFT, UP, UP },                              //To R2
    { LEFT, UP, UP },                                    //To R3
    {},                                                  //To R4
    { LEFT, DOWN, RIGHT },                               //To R5
    { LEFT, DOWN, DOWN, LEFT },                          //To R6
    { LEFT, UP, LEFT, LEFT, UP, UP, UP, RIGHT },         //To R7
    { LEFT, UP, LEFT, LEFT, UP, UP, UP, UP, LEFT, UP },  //To R8
    { LEFT, UP, LEFT, LEFT, UP, UP, UP, LEFT, LEFT },    //To R9
    { LEFT, UP, LEFT, LEFT, UP, UP, LEFT, UP },          //To R10
    { LEFT, UP, LEFT, LEFT, UP, UP, LEFT, DOWN }         //elevator
  },
  {
    //R5
    { UP, UP, LEFT, LEFT, UP, RIGHT },                 //To Entrence
    { UP, UP, LEFT, LEFT, DOWN },                      //To R1
    { UP, UP, LEFT, UP },                              //To R2
    { UP, UP, UP },                                    //To R3
    { UP, RIGHT, UP },                                 //To R4
    {},                                                //To R5
    { DOWN, LEFT },                                    //To R6
    { UP, UP, LEFT, LEFT, UP, UP, UP, RIGHT },         //To R7
    { UP, UP, LEFT, LEFT, UP, UP, UP, UP, LEFT, UP },  //To R8
    { UP, UP, LEFT, LEFT, UP, UP, UP, LEFT, LEFT },    //To R9
    { UP, UP, LEFT, LEFT, UP, UP, LEFT, UP },          //To R10
    { UP, UP, LEFT, LEFT, UP, UP, LEFT, DOWN }         //elevator
  },
  {                                                            //R6
    { UP, UP, UP, LEFT, LEFT, UP, RIGHT },                     //To Entrence
    { UP, UP, UP, LEFT, LEFT, DOWN },                          //To R1
    { UP, UP, UP, LEFT, UP },                                  //To R2
    { UP, UP, UP, UP },                                        //To R3
    { UP, UP, RIGHT, UP },                                     //To R4
    { UP, RIGHT },                                             //To R5
    {},                                                        //To R6
    { UP, UP, UP, LEFT, LEFT, UP, UP, UP, RIGHT },             //To R7
    { UP, UP, UP, LEFT, LEFT, UP, UP, UP, UP, LEFT, UP },      //To R8
    { UP, UP, UP, LEFT, LEFT, UP, UP, LEFT, LEFT, UP, LEFT },  //To R9
    { UP, UP, UP, LEFT, LEFT, UP, UP, LEFT, UP },              //To R10
    { UP, UP, UP, LEFT, LEFT, UP, UP, LEFT, DOWN } },
  {
    //R7
    { DOWN, DOWN, RIGHT },                                       //To Entrence
    { DOWN, DOWN, DOWN, DOWN },                                  //To R1
    { DOWN, DOWN, DOWN, RIGHT, UP },                             //To R2
    { DOWN, DOWN, DOWN, RIGHT, RIGHT, UP },                      //To R3
    { DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    {},                                                          //To R7
    { UP, LEFT, UP },                                            //To R8
    { LEFT, LEFT },                                              //To R9
    { DOWN, LEFT, UP },                                          //To R10
    { DOWN, LEFT, DOWN }                                         //elevator
  },
  {
    //R8
    { RIGHT, DOWN, DOWN, DOWN, RIGHT },                                       //To Entrence
    { RIGHT, DOWN, DOWN, DOWN, DOWN, DOWN },                                  //To R1
    { RIGHT, DOWN, DOWN, DOWN, DOWN, RIGHT, UP },                             //To R2
    { RIGHT, DOWN, DOWN, DOWN, DOWN, RIGHT, RIGHT, UP },                      //To R3
    { RIGHT, DOWN, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { RIGHT, DOWN, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { RIGHT, DOWN, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { RIGHT, DOWN, RIGHT },                                                   //To R7
    {},                                                                       //To R8
    { LEFT, DOWN, LEFT },                                                     //To R9
    { LEFT, DOWN, DOWN, RIGHT, UP },                                          //To R10
    { LEFT, DOWN, DOWN, RIGHT, DOWN }                                         //elevator
  },


  {
    //R9
    { RIGHT, DOWN, DOWN, RIGHT },                                       //To Entrence
    { RIGHT, DOWN, DOWN, DOWN, DOWN },                                  //To R1
    { RIGHT, DOWN, DOWN, DOWN, RIGHT, UP },                             //To R2
    { RIGHT, DOWN, DOWN, DOWN, RIGHT, RIGHT, UP },                      //To R3
    { RIGHT, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { RIGHT, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { RIGHT, DOWN, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { RIGHT, RIGHT },                                                   //To R7
    { UP, RIGHT, UP },                                                  //To R8
    {},                                                                 //To R9
    { DOWN, RIGHT, UP },                                                //To R10

    { DOWN, RIGHT, DOWN }  // elevator
  },
  {
    //R10
    { RIGHT, DOWN, RIGHT },                                       //To Entrence
    { RIGHT, DOWN, DOWN, DOWN },                                  //To R1
    { RIGHT, DOWN, DOWN, RIGHT, UP },                             //To R2
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, UP },                      //To R3
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { RIGHT, UP, RIGHT },                                         //To R7
    { RIGHT, UP, UP, LEFT, UP },                                  //To R8
    { LEFT, UP, LEFT },                                           //To R9
    {},                                                           //To R10
    { DOWN }                                                      // Elevator
  },
  {
    //Elevator
    { RIGHT, DOWN, RIGHT },                                       //To Entrence
    { RIGHT, DOWN, DOWN, DOWN },                                  //To R1
    { RIGHT, DOWN, DOWN, RIGHT, UP },                             //To R2
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, UP },                      //To R3
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, RIGHT, UP },         //To R4
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, RIGHT },       //To R5
    { RIGHT, DOWN, DOWN, RIGHT, RIGHT, DOWN, DOWN, DOWN, LEFT },  //To R6
    { RIGHT, UP, RIGHT },                                         //To R7
    { RIGHT, UP, UP, LEFT, UP },                                  //To R8
    { LEFT, UP, LEFT },                                           //To R9
    { UP },                                                       //To R10
    {},                                                           // ELEvator
  }
};





void playNextDirection() {
  int myNextDirection = pgm_read_byte(&roomToRoomDirections[startingPoint][destination][step]);

  if (myNextDirection == 255) {
    myNextDirection = -1;
  } else if (myNextDirection == 246) {
    myNextDirection = -10;
  }

  Serial.println("myNextDirection = " + String(myNextDirection));
  playSound(cacPlaySound(myNextDirection, facingDirection));  //Goto Audio_Funcs
}

void playCurrentDirection() {
  int myCurrentDirection = pgm_read_byte(&roomToRoomDirections[startingPoint][destination][step - 1]);

  if (myCurrentDirection == 255) {
    myCurrentDirection = -1;
  } else if (myCurrentDirection == 246) {
    myCurrentDirection = -10;
  }

  Serial.println("myCurrentDirection = " + String(myCurrentDirection));
  playSound(cacPlaySound(myCurrentDirection, lastFacingDirection));  //Goto Audio_Funcs
}

String cacPlaySound(int intDirection, char direction) {

  Serial.println("Passing " + String(intDirection) + " thru cacPlaySound with direction " + facingDirection);
  switch (direction) {
    case 'N':
      lastFacingDirection = 'N';
      if (intDirection == 1) {
        return "Fwd";
      } else if (intDirection == 10) {
        facingDirection = 'E';
        return "Rht";
      } else if (intDirection == -10) {
        facingDirection = 'W';
        return "Lft";
      } else if (intDirection == -1) {
        facingDirection = 'S';
        return "Bck";
      }
      break;
    case 'S':
      lastFacingDirection = 'S';
      if (intDirection == -1) {
        return "Fwd";
      } else if (intDirection == -10) {
        facingDirection = 'W';
        return "Rht";
      } else if (intDirection == 10) {
        facingDirection = 'E';
        return "Lft";
      } else if (intDirection == 1) {
        facingDirection = 'N';
        return "Bck";
      }
      break;
    case 'E':
      lastFacingDirection = 'E';
      if (intDirection == 10) {
        return "Fwd";
      } else if (intDirection == -1) {
        facingDirection = 'S';
        return "Rht";
      } else if (intDirection == 1) {
        facingDirection = 'N';
        return "Lft";
      } else if (intDirection == -10) {
        facingDirection = 'W';
        return "Bck";
      }
      break;
    case 'W':
      lastFacingDirection = 'W';
      if (intDirection == -10) {
        return "Fwd";
      } else if (intDirection == 1) {
        facingDirection = 'N';
        return "Rht";
      } else if (intDirection == -1) {
        facingDirection = 'S';
        return "Lft";
      } else if (intDirection == 10) {
        facingDirection = 'E';
        return "Bck";
      }
      break;
    default:
      return "ERROR 2";
      break;
  }
  return "ERROR 1";
}