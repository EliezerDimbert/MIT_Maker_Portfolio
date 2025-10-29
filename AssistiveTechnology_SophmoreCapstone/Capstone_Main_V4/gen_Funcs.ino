int findIndexOfInt(int whichInstance, int query, int myArray[], int mySize) {
  int k = 0;
  for (int i = 0; i < mySize; i++) {
    if (query == myArray[i]) {
      k++;
      if (k == whichInstance){
        debugLog("findIndexOfInt returned " + String(i) + " with query " + String(query) + " and trying to find the " + String(whichInstance) + " instance");
        return i;
      }
    }
  }
  Serial.println("findIndexOfInt HAS RUN: ERROR! NO INT FOUND");
  return -1;
}

int findAmtOfInt(int query, int myArray[], int mySize) {
  int totalAmt = 0;
  for (int i = 0; i < mySize; i++) {
    if (query == myArray[i]) {
      totalAmt++;
    }
  }
  debugLog("findAmtOfInt returned " + String(totalAmt) + " with query " + String(query));
  return totalAmt;
}

void printArray(int xLength, int yLength, const int myArray[]) {
  Serial.println("");
  for (int i = 0; i < yLength; i++) {
    for (int j = 0; j < xLength; j++) {
      Serial.print(myArray[i * xLength + j]);  // Adjusted indexing
      Serial.print(" ");
      delay(10);
    }
    Serial.println("");
  }
}

void debugLog(String message){
  if (debug == true){
    Serial.println(message);
  }
}
