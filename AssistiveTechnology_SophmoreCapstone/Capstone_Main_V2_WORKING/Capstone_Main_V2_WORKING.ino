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
  // Check response.
  if (checkAudio()) {
    Serial.println(decodeMP3Answer());
  }



  delay(100);
}