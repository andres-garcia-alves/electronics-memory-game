#ifndef DISPLAY_7S_2D_H
#define DISPLAY_7S_2D_H

byte currentDigit;
byte maskedBits;

// functions declaration
void displayCharacter(char);
void setLedsByMaskedBits(byte);


void updateDisplay(byte currentLevel) {

  // enable current digit (LOW enable, HIGH disable)
  digitalWrite(DISPLAY_DIGIT_0, (currentDigit == 1) ? LOW : HIGH);  // left digit
  digitalWrite(DISPLAY_DIGIT_1, (currentDigit == 0) ? LOW : HIGH);  // right digit

  // build string to display
  String currentLevelText = (currentLevel < 10) ? "0" + String(currentLevel) : String(currentLevel);
  if (currentLevel == GAME_LEVELS)  { currentLevelText = "--"; }

  // display character for the current digit
  displayCharacter(currentLevelText.charAt(currentDigit));

  // move to next digit (valid range 0-1)
  currentDigit = (++currentDigit) % 2;
}

void displayCharacter(char character) {

  switch(character) {      //.GFEDCBA (1 = ON, 0 = OFF)
    case '0': maskedBits = 0b00111111; break;
    case '1': maskedBits = 0b00000110; break;
    case '2': maskedBits = 0b01011011; break;
    case '3': maskedBits = 0b01001111; break;
    case '4': maskedBits = 0b01100110; break;
    case '5': maskedBits = 0b01101101; break;
    case '6': maskedBits = 0b01111101; break;
    case '7': maskedBits = 0b00000111; break;
    case '8': maskedBits = 0b01111111; break;
    case '9': maskedBits = 0b01100111; break;
    case '-': maskedBits = 0b01000000; break;
    default:  maskedBits = 0b00000000;
  }

  setLedsByMaskedBits(maskedBits);
}

// set individuals leds ON/OFF by mask (format: '.GFEDCBA')
void setLedsByMaskedBits(byte maskedBits) {

  digitalWrite(DISPLAY_LED_A, maskedBits & 1);
  digitalWrite(DISPLAY_LED_B, maskedBits & 2);
  digitalWrite(DISPLAY_LED_C, maskedBits & 4);
  digitalWrite(DISPLAY_LED_D, maskedBits & 8);
  digitalWrite(DISPLAY_LED_E, maskedBits & 16);
  digitalWrite(DISPLAY_LED_F, maskedBits & 32);
  digitalWrite(DISPLAY_LED_G, maskedBits & 64);
}

#endif
