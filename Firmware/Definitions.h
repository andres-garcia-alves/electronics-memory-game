#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// digit-selector & display 7-segment pins
#define DISPLAY_DIGIT_1 6   // left digit
#define DISPLAY_DIGIT_0 13  // right digit

#define DISPLAY_LED_A   9
#define DISPLAY_LED_B   7
#define DISPLAY_LED_C   A5
#define DISPLAY_LED_D   A3
#define DISPLAY_LED_E   A4
#define DISPLAY_LED_F   A1
#define DISPLAY_LED_G   A2

// LEDs, bottons & other pins
#define LED_RED         12
#define LED_BLUE        8
#define LED_YELLOW      5
#define LED_GREEN       4
#define BUTTON_RED      11
#define BUTTON_BLUE     10
#define BUTTON_YELLOW   3
#define BUTTON_GREEN    2

#define BUZZER          0
#define RANDOM_NOISE    A0

// misc
#define GAME_LEVELS     50  // less than 600 free bytes of dynamic memory turns into a stack overflow
#define QUEUE_SIZE      155 // GAME_LEVELS * 3 + 5

#define FRECUENCY_FACTOR  10
#define DURATION_FACTOR   10

// enums
enum class eGameMode : byte { NONE = 0, STARTING = 1, SEQUENCE_MODE = 2, PLAYER_MODE = 3, WRONG_INPUT = 4, ENDING = 5 };

enum class eCmdType : byte { INIT = 0, GAME_MODE = 1, WAIT = 2, DEBOUNCE = 3, BUTTON = 4, LED = 5, BEEP = 6, WRONG = 7, END = 8 };
enum class eWait : byte { ZERO = 0, DEBOUNCE = 5, ANIM_HALF = 20, ANIM_FULL = 40, START = 150, WRONG = 255 }; // values x 10
enum class eColor : byte { NONE = 0, RED = 1, BLUE = 2, YELLOW = 3, GREEN = 4 };

enum class eToneFrecuency : byte { WRONG = 10, RED = 50, BLUE = 60, YELLOW = 70, GREEN = 80 };  // values x 10
enum class eToneDuration : byte { ANIM_HALF = 20, ANIM_FULL = 40, WRONG = 255, END = 255 };     // values x 10

// data structures
struct stInput { bool hasData; bool redButton; bool blueButton; bool yellowButton; bool greenButton; };
struct stBuzzer { byte frecuency; byte duration; };
struct stCommand { eCmdType cmdType; eWait wait; eGameMode gameMode; byte input; eColor color; stBuzzer buzzer; };

// variables
bool debounced;
byte currentLevel;
eGameMode gameMode = eGameMode::STARTING;
eColor colorSequence[GAME_LEVELS];
eColor playerSequence[GAME_LEVELS];

// aux variables
byte emptyInput;
stBuzzer emptyBuzzer;

#endif
