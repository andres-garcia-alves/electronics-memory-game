/*
Memory Game v1.4

Created by: Andres Garcia Alves <andres.garcia.alves@gmail.com>
Microcontroller: Arduino Nano (ATMega328 @16Mhz)

Version 1.0, 2023.03.08 - Initial release.
Version 1.1, 2023.03.09 - Refactor for mudularity (adding concept of micro-commands for user inteccions).
Version 1.2, 2023.03.10 - Improved animations.
Version 1.3, 2023.03.15 - Pinout rearrange for easy soldering.
Version 1.4, 2023.03.18 - Adding game finished sequence.

This source code is licensed under GPL v3.0

Pinout (2 digit multiplexed 7-segment display):

      ***(A)***
  (F) *       * (B)
      ***(G)***
  (E) *       * (C)
      ***(D)***
*/

#include "Definitions.h"
#include "Debug.h"
#include "Utilities.h"
#include "Display_2d.h"
#include "MessagesHelper.h"

void setup() {

  #if DEBUG
  Serial.begin(9600);
  #endif

  pinMode(DISPLAY_DIGIT_1, OUTPUT); // left digit
  pinMode(DISPLAY_DIGIT_0, OUTPUT); // right digit

  pinMode(DISPLAY_LED_A, OUTPUT);
  pinMode(DISPLAY_LED_B, OUTPUT);
  pinMode(DISPLAY_LED_C, OUTPUT);
  pinMode(DISPLAY_LED_D, OUTPUT);
  pinMode(DISPLAY_LED_E, OUTPUT);
  pinMode(DISPLAY_LED_F, OUTPUT);
  pinMode(DISPLAY_LED_G, OUTPUT);
  
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(BUTTON_RED, INPUT_PULLUP);
  pinMode(BUTTON_BLUE, INPUT_PULLUP);
  pinMode(BUTTON_YELLOW, INPUT_PULLUP);
  pinMode(BUTTON_GREEN, INPUT_PULLUP);
  
  pinMode(BUZZER, OUTPUT);
  
  // get some noise value from A0
  randomSeed(analogRead(RANDOM_NOISE));
}

void loop() {

  runCommands();                // run generated commands
  updateDisplay(currentLevel);  // update display & move to next digit
  
  // game control
  if (gameMode == eGameMode::STARTING && noPendingCommands()) {
    initializeMessage();
  }
  else if (gameMode == eGameMode::SEQUENCE_MODE && noPendingCommands()) {
    sequenceMessage();
  }
  else if (gameMode == eGameMode::PLAYER_MODE && noPendingCommands()) {
    stInput input = checkInput();
    if (input.hasData && !debounced)      { debounceMessage(); }
    else if (input.hasData && debounced)  { processInputMessage(input); }
  }
  else if (gameMode == eGameMode::WRONG_INPUT && noPendingCommands()) {
    wrongInputMessage();
  }
  else if (gameMode == eGameMode::ENDING && noPendingCommands()) {
    endingMessage();
  }

  delay(10);
}

stInput checkInput() {

  bool redButton = !digitalRead(BUTTON_RED);
  bool blueButton = !digitalRead(BUTTON_BLUE);
  bool yellowButton = !digitalRead(BUTTON_YELLOW);
  bool greenButton = !digitalRead(BUTTON_GREEN);

  stInput input;
  input.hasData = redButton || blueButton || yellowButton || greenButton;
  input.redButton = redButton;
  input.blueButton = blueButton;
  input.yellowButton = yellowButton;
  input.greenButton = greenButton;

  return input;
}
