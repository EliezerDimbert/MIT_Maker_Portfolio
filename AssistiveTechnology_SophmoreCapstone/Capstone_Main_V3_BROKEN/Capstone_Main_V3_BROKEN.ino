const bool debug = true;

const int repeatButton = 26;
const int nextButton = 24;
uint8_t destination = 0;

String stringInput = "";
bool processed = false;
String Serialdata = "";

// *******************************************************************************************************
void setup() {
  pinMode(repeatButton, INPUT_PULLUP);
  pinMode(nextButton, INPUT_PULLUP);

  Serial.begin(9600);
  audioSetup();
  huskeySetup();
  dabble("setup");

  Serial.println();
  playSound("Srt");
  delay(7000);
}



// *******************************************************************************************************
void loop() {
  dabble("loop");

  processHuskey();

  if (stringInput != "" && processed == false) {
    destination = atoi(stringInput.c_str());
    debugLog("New destination = " + String(destination));
    processed = true;
    stringInput = "";
  }

  // Check response.
  if (checkAudio()) {
    Serial.println(decodeMP3Answer());
  }

  if (!digitalRead(repeatButton)) {
    playCurrentDirection();
  }


  delay(100);
}