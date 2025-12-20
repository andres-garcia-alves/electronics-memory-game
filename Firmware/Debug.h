#ifndef DEBUG_H
#define DEBUG_H

// enable/disable debuging
#define DEBUG       false


#if DEBUG
void sizeofCommandStruct() {

  Serial.print("sizeof(stCommand): ");
  Serial.println(sizeof(stCommand));
}
#endif

#if DEBUG
void debugColorArrays() {
  String message;

  message = "colorSequence: ";
  for (byte i = 0; i < GAME_LEVELS - 1; i++) {
    message += (byte)colorSequence[i];
    message += ", ";
  }
  message += (byte)colorSequence[GAME_LEVELS - 1];
  Serial.println(message);

  message = "playerSequence: ";
  for (byte i = 0; i < GAME_LEVELS - 1; i++) {
    message += (byte)playerSequence[i];
    message += ", ";
  }
  message += (byte)playerSequence[GAME_LEVELS - 1];
  Serial.println(message);
}
#endif

#endif
