const bool debug = true;

// *******************************************************************************************************
void setup() {
  Serial.begin(9600);
  audioSetup();
  huskeybegin();
  Serial.println();
  playSound("Srt");
  delay(7000);

}



// *******************************************************************************************************
void loop() {
  processHuskey();

  // Incoming characters from the serial (Serial Monitor) are accommodated for processing and then sent to the mp3 player module.
  if (Serial.available()) {
    playSound(readSerial());
  }

  // Check response.
  if (checkAudio()) {
    Serial.println(decodeMP3Answer());
  }



  delay(100);
}