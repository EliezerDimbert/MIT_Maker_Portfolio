
const int NUM_ROOMS = 11;
/* 
Best if even # bc we only need to to half of the rooms
b/c getting from room 2 -> room 1 is just room 1 -> room 2 reversed
*/
const int MAX_STEPS = 8;

const byte UP = byte(1);
const byte DOWN = byte(-1);  //Saved as 255 or 11111111
const byte RIGHT = byte(10);
const byte LEFT = byte(-10);  //Saved as 246 or 11110110

char facingDirection = 'N';
char lastFacingDirection = 'N';

int step = 0;
int room = 0;

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
    {},                                               //To Entrence
    { LEFT, DOWN },                                   //To R1
    { LEFT, LEFT, DOWN },                             //To R2
    { LEFT, LEFT, UP, RIGHT },                        //To R3
    { LEFT, LEFT, UP, LEFT },                         //To R4
    { LEFT, LEFT, UP, UP, RIGHT },                    //To R5
    { RIGHT, DOWN, RIGHT, DOWN, RIGHT },              //To R6
    { RIGHT, DOWN, RIGHT, DOWN, RIGHT, UP },          //To R7
    { RIGHT, DOWN, RIGHT, DOWN, RIGHT, DOWN },        //To R8
    { RIGHT, DOWN, RIGHT, DOWN, RIGHT, DOWN, LEFT },  //To R9
    { RIGHT, DOWN, RIGHT, DOWN, LEFT, DOWN },         //To R10
  }
  // {
  //   //R1
  //   {UP, RIGHT},
  //   {},

  // }
};

void playNextDirection() {
  int myNextDirection = pgm_read_byte(&roomToRoomDirections[0][room][step]);

  if (myNextDirection == 255) {
    myNextDirection = -1;
  } else if (myNextDirection == 246) {
    myNextDirection = -10;
  }

  Serial.println("myNextDirection = " + String(myNextDirection));
  playSound(cacPlaySound(myNextDirection, facingDirection));  //Goto Audio_Funcs
}

void playCurrentDirection() {
  int myCurrentDirection = pgm_read_byte(&roomToRoomDirections[0][room][step - 1]);

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