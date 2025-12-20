#ifndef COMMANDS_H
#define COMMANDS_H

// functions declaration
void buildRandomColorSequence();
byte getPlayerSequencePosition();
void clearPlayerSequence();


void initializeCommand() {

  currentLevel = 0;           // zero based
  clearPlayerSequence();      // clear player sequence
  buildRandomColorSequence(); // build a new random colore sequence
  // clearCommands();         // clear commands queue

  #if DEBUG
  sizeofCommandStruct();
  debugColorArrays();
  #endif
}

void gameModeCommand(eGameMode newGameMode) {
  gameMode = newGameMode;
}

void waitOperationCommand() {
  // the delay part is done by CommandsManager

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);
}

void debounceFlagCommand() {
  debounced = true;
}

void buttonPressedCommand(byte packedInput) { // stInput input
  debounced = false;
  stInput input = unpackInput(packedInput);

  // display pressed button
  digitalWrite(LED_RED, input.redButton);
  digitalWrite(LED_BLUE, input.blueButton);
  digitalWrite(LED_YELLOW, input.yellowButton);
  digitalWrite(LED_GREEN, input.greenButton);

  #if DEBUG
  debugColorArrays();
  #endif

  // basic validations
  byte sumButtons = input.redButton + input.blueButton + input.yellowButton + input.greenButton;
  if (sumButtons == 0) { return; }  // no buttom pressed (teorically unreachable)
  if (sumButtons >= 2) { gameMode = eGameMode::WRONG_INPUT; return; }  // more that a single buttom pressed

  // wrong buttom pressed validation
  byte playerPosition = getPlayerSequencePosition();
  eColor currentColor = (eColor)colorSequence[playerPosition];

  if (input.redButton && currentColor != eColor::RED || input.blueButton && currentColor != eColor::BLUE ||
      input.yellowButton && currentColor != eColor::YELLOW || input.greenButton && currentColor != eColor::GREEN) {
    clearPlayerSequence();
    gameMode = eGameMode::WRONG_INPUT; return;
  }

  // save color on player sequence
  playerSequence[playerPosition] = currentColor;

  // check increment of current level & change to sequence mode
  if (playerPosition == currentLevel) {
    currentLevel++;
    clearPlayerSequence();
    gameMode = eGameMode::SEQUENCE_MODE;
  }

  // check game completed
  if (currentLevel == GAME_LEVELS) {
    gameMode = eGameMode::ENDING;
  }
}

void showColorCommand(eColor color) {

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);
  digitalWrite(LED_YELLOW, LOW);
  digitalWrite(LED_GREEN, LOW);

  switch(color) {
    case eColor::RED:     digitalWrite(LED_RED, HIGH);    break;
    case eColor::BLUE:    digitalWrite(LED_BLUE, HIGH);   break;
    case eColor::YELLOW:  digitalWrite(LED_YELLOW, HIGH); break;
    case eColor::GREEN:   digitalWrite(LED_GREEN, HIGH);  break;
  }
}

void toneCommand(byte frecuency, byte duration) {

  tone(BUZZER, frecuency * FRECUENCY_FACTOR, duration * DURATION_FACTOR);
}

void wrongInputCommand() {

  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_BLUE, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, HIGH);
}

// auxiliar functions
void buildRandomColorSequence() {
  
  for (byte i = 0; i < GAME_LEVELS; i++)
    colorSequence[i] = (eColor)random(1, 5);
}

byte getPlayerSequencePosition() {

  for (byte i = 0; i < GAME_LEVELS; i++)
    if (playerSequence[i] == eColor::NONE) { return i; }
  return 0;
}

void clearPlayerSequence() {

  for (byte i = 0; i < GAME_LEVELS; i++) {
    playerSequence[i] = eColor::NONE;
  }
}

#endif
