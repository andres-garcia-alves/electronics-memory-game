#include "Commands.h"
#include "Queue.h"

#ifndef COMMANDS_MANAGER_H
#define COMMANDS_MANAGER_H

Queue _queue;

bool _commandRunning = false;
unsigned long int _currentMillis;
unsigned long int _commandEndMillis;

void enqueueCommand(stCommand command) 
{
  _queue.push(command);
}

bool runCommands()
{
  _currentMillis = millis();
  if (_commandRunning == true && _currentMillis < _commandEndMillis) { return false; }
  if (_commandRunning == true && _currentMillis >= _commandEndMillis) { _commandRunning = false; }
  if (_queue.count() == 0) { return false; }

  // pop a pending command from queue
  stCommand command = _queue.pop();

  _commandRunning = true;
  _commandEndMillis = _currentMillis + (byte)command.wait * DURATION_FACTOR;

  switch(command.cmdType) {
    case eCmdType::INIT:      initializeCommand();                  break;
    case eCmdType::GAME_MODE: gameModeCommand(command.gameMode);    break;
    case eCmdType::WAIT:      waitOperationCommand();               break;
    case eCmdType::DEBOUNCE:  debounceFlagCommand();                break;
    case eCmdType::BUTTON:    buttonPressedCommand(command.input);  break;
    case eCmdType::LED:       showColorCommand(command.color);      break;
    case eCmdType::BEEP:      toneCommand(command.buzzer.frecuency, command.buzzer.duration); break;
    case eCmdType::WRONG:     wrongInputCommand();                  break;
  }

  return true;
}

bool noPendingCommands() {
  return (_queue.count() + _commandRunning == 0) ? true : false;
}

byte countCommands() {
  return _queue.count();
}

void clearCommands() {
  _queue.clear();
}

#endif
