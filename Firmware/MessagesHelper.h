#include "CommandsManager.h"

#ifndef COMMANDS_HELPER_H
#define COMMANDS_HELPER_H

// functions declaration
stBuzzer buildSound(stInput, eToneDuration);
stBuzzer buildSound(eColor, eToneDuration);
stBuzzer buildSound(eToneFrecuency, eToneDuration);
stBuzzer buildSound(byte, byte);
stCommand buildCommand(eCmdType, eWait, eGameMode, byte, eColor, stBuzzer);


void initializeMessage() {

  enqueueCommand(buildCommand(eCmdType::INIT, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::SEQUENCE_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

void createGameModeCommand(eGameMode gameMode) {

  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, gameMode, emptyInput, eColor::NONE, emptyBuzzer));
}

void sequenceMessage() {

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::START, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));

  for (int i = 0; i <= currentLevel; i++) {
    stBuzzer buzzer = buildSound(colorSequence[i], eToneDuration::ANIM_FULL);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIM_FULL, eGameMode::NONE, emptyInput, colorSequence[i], emptyBuzzer));

    enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIM_FULL, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  }

  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::PLAYER_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

void debounceMessage() {

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::DEBOUNCE, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::DEBOUNCE, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
}

void processInputMessage(stInput input) {

  stBuzzer buzzer = buildSound(input, eToneDuration::ANIM_FULL);
  enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));

  byte packedInput = packInput(input);
  enqueueCommand(buildCommand(eCmdType::BUTTON, eWait::ANIM_FULL, eGameMode::NONE, packedInput, eColor::NONE, emptyBuzzer));

  enqueueCommand(buildCommand(eCmdType::LED, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
}

void wrongInputMessage() {

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIM_FULL, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));

  stBuzzer buzzer = buildSound(eToneFrecuency::WRONG, eToneDuration::WRONG);
  enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
  enqueueCommand(buildCommand(eCmdType::WRONG, eWait::WRONG, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));

  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::SEQUENCE_MODE, emptyInput, eColor::NONE, emptyBuzzer));
}

void endingMessage() {
  stBuzzer buzzer;

  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIM_FULL, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));

  for (int i = 0; i < 7; i++) {
    buzzer = buildSound(eColor::RED, eToneDuration::ANIM_HALF);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIM_HALF, eGameMode::NONE, emptyInput, eColor::RED, emptyBuzzer));

    buzzer = buildSound(eColor::BLUE, eToneDuration::ANIM_HALF);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIM_HALF, eGameMode::NONE, emptyInput, eColor::BLUE, emptyBuzzer));

    buzzer = buildSound(eColor::YELLOW, eToneDuration::ANIM_HALF);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIM_HALF, eGameMode::NONE, emptyInput, eColor::YELLOW, emptyBuzzer));

    buzzer = buildSound(eColor::GREEN, eToneDuration::ANIM_HALF);
    enqueueCommand(buildCommand(eCmdType::BEEP, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, buzzer));
    enqueueCommand(buildCommand(eCmdType::LED, eWait::ANIM_HALF, eGameMode::NONE, emptyInput, eColor::GREEN, emptyBuzzer));
  }
  
  enqueueCommand(buildCommand(eCmdType::WAIT, eWait::ANIM_FULL, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  
  enqueueCommand(buildCommand(eCmdType::INIT, eWait::ZERO, eGameMode::NONE, emptyInput, eColor::NONE, emptyBuzzer));
  enqueueCommand(buildCommand(eCmdType::GAME_MODE, eWait::ZERO, eGameMode::STARTING, emptyInput, eColor::NONE, emptyBuzzer));
}


// auxiliar functions
stBuzzer buildSound(stInput input, eToneDuration duration) {
  byte frecuency = 0;

  if (input.redButton)    { frecuency += (byte)eToneFrecuency::RED; }
  if (input.blueButton)   { frecuency += (byte)eToneFrecuency::BLUE; }
  if (input.yellowButton) { frecuency += (byte)eToneFrecuency::YELLOW; }
  if (input.greenButton)  { frecuency += (byte)eToneFrecuency::GREEN; }
  
  return buildSound(frecuency, (byte)duration);
}

stBuzzer buildSound(eColor color, eToneDuration duration) {
  byte frecuency = 0;

  if (color == eColor::RED)    { frecuency += (byte)eToneFrecuency::RED; }
  if (color == eColor::BLUE)   { frecuency += (byte)eToneFrecuency::BLUE; }
  if (color == eColor::YELLOW) { frecuency += (byte)eToneFrecuency::YELLOW; }
  if (color == eColor::GREEN)  { frecuency += (byte)eToneFrecuency::GREEN; }
  
  return buildSound(frecuency, (byte)duration);
}

stBuzzer buildSound(eToneFrecuency frecuency, eToneDuration duration) {
  return buildSound((byte)frecuency, (byte)duration);
}

stBuzzer buildSound(byte frecuency, byte duration) {
  stBuzzer buzzer;
  buzzer.frecuency = frecuency;
  buzzer.duration = duration;
  return buzzer;
}

stCommand buildCommand(eCmdType cmdType, eWait wait, eGameMode gameMode, byte input, eColor color, stBuzzer buzzer) {
  stCommand command;
  command.cmdType = cmdType;
  command.input = input;
  command.color = color;
  command.wait = wait;
  command.gameMode = gameMode;
  command.buzzer = buzzer;
  return command;
}

#endif
