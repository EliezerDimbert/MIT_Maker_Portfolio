
#define CUSTOM_SETTINGS
#define INCLUDE_TERMINAL_MODULE
#include <Dabble.h>
char arrayInput[10];

void dabble(String place) {  //should work :D
  if (place == "setup") {
    Dabble.begin(9600);
  } else if (place == "loop") {
    Dabble.processInput();
  }
}

void dabbleRead() {  //WORKS :3

  while (Serial.available()) {
    Serialdata += String(char(Serial.read()));
  }

  Serialdata = "";

  for (int i = 0; i < 10 && Terminal.available(); i++) {
    arrayInput[i] = Terminal.read();
    i++;
    processed = false;
  }

  if (!Terminal.available() && processed == false) {
    stringInput = arrayInput;
  }
  if (debug == 1) {
    Serial.println("dabbleRead HAS RUN AND stringInput = " + stringInput);
  }
}

bool terminalCheck() {  //:P
  return Terminal.available();
}