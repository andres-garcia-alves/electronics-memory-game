#ifndef UTILITIES_H
#define UTILITIES_H

byte packInput(stInput input) {

  byte packedInput;
  packedInput += (input.hasData)      ? 0b10000000 : 0b00000000;
  packedInput += (input.redButton)    ? 0b00001000 : 0b00000000;
  packedInput += (input.blueButton)   ? 0b00000100 : 0b00000000;
  packedInput += (input.yellowButton) ? 0b00000010 : 0b00000000;
  packedInput += (input.greenButton)  ? 0b00000001 : 0b00000000;
  
  return packedInput;
}

stInput unpackInput(byte packedInput) {

  stInput input;
  input.hasData       = packedInput & 0b10000000;
  input.redButton     = packedInput & 0b00001000;
  input.blueButton    = packedInput & 0b00000100;
  input.yellowButton  = packedInput & 0b00000010;
  input.greenButton   = packedInput & 0b00000001;
  
  return input;
}

#endif
