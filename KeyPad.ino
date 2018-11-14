#include <Keypad.h>

// initailize the keypad matrix
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {0, 1, 2, 3};
byte colPins[COLS] = {23, 22, 20, 19};

// define password related variables
const byte pLen = 5; // must include trailing \0
char password[pLen] = {'3', '2', '1', 'A', '\0'};
char input[pLen];
byte curPLen = 0;
bool inter = false; // Interactive mode flag


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  input[4] = '\0';
  //Serial.begin(9600); // for debugging serial monitor
}

void loop() {
  char key = customKeypad.getKey();
  if (key && inter == false) { // get a key, and make sure interactive mode is off
    Keyboard.print(key);
    keyrec(key);
  }
  if (key && inter == true) {
    switch (key) {
      case '1': // Data
        Keyboard.print("Two hunters are out in the woods when one of them collapses. He doesn't seem to be breathing and his eyes are glazed. The other guy whips out his phone and calls the emergency services. He gasps, \"My friend is dead! What can I do?\" The operator says \"Calm down. I can help. First, let's make sure he's dead.\" There is a silence, then a shot is heard. Back on the phone, the guy says \"OK, now what?\"");
        Keyboard.print("\nThere is roughly 52064 bytes left"); // reflects minimized code, still can improve
        break;
      case '2': // Python script
        Keyboard.print("with open(\"input.txt\") as toTrans:\n    text = toTrans.read().translate(str.maketrans({\"\\n\": r\"\\n\", \"\\\\\": r\"\\\\\", \"\\\"\": r\"\\\"\"}))\ntext_file = open(\"Translated.txt\", \"w\")\ntext_file.write(text)\ntext_file.close()\n");
        break;
      case '3': // Firmware
        Keyboard.print("#include <Keypad.h>\n\nconst byte ROWS = 4;\nconst byte COLS = 4;\nchar hexaKeys[ROWS][COLS] = {\n  {'1', '2', '3', 'A'},\n  {'4', '5', '6', 'B'},\n  {'7', '8', '9', 'C'},\n  {'*', '0', '#', 'D'}\n};\nbyte rowPins[ROWS] = {0, 1, 2, 3};\nbyte colPins[COLS] = {23, 22, 20, 19};\nconst byte pLen = 5;\nchar password[pLen] = {'3', '2', '1', 'A', '\\0'};\nchar input[pLen];\nbyte curPLen = 0;\nbool inter = false;\nKeypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);\nvoid setup() {\n  input[4] = '\\0';\n}\nvoid loop() {\n  char key = customKeypad.getKey();\n  if (key && inter == false) {\n    Keyboard.print(key);\n    keyrec(key);\n  }\n  if (key && inter == true) {\n    switch (key) {\n      case '1':\n        Keyboard.print(\"Data Here\");\n        break;\n      case '2':\n        Keyboard.print(\"with open(\\\"input.txt\\\") as toTrans:\\n    text = toTrans.read().translate(str.maketrans({\\\"\\\\n\\\": r\\\"\\\\n\\\", \\\"\\\\\\\\\\\": r\\\"\\\\\\\\\\\", \\\"\\\\\\\"\\\": r\\\"\\\\\\\"\\\"}))\\ntext_file = open(\\\"Translated.txt\\\", \\\"w\\\")\\ntext_file.write(text)\\ntext_file.close()\\n\");\n        break;\n      case '3':\n        Keyboard.print(\"Firmware\");\n        break;\n      case '#':\n        inter = false;\n        break;\n    }\n  }\n}\nvoid keyrec(char key) {\n  if (inter == false){\n    input[curPLen] = key;\n    curPLen++;\n  }\n  if ((curPLen) == (pLen - 1)) {\n    if (strcmp(input, password) == 0) {\n      inter = true;\n      Keyboard.println(\"\");\n      Keyboard.println(\"Interactive mode:\");\n      Keyboard.println(\"Press '1' to dump data\");\n      Keyboard.println(\"Press '2' to dump input translate script (python3)\");\n      Keyboard.println(\"Press '3' to dump firmware (arduino)\");\n      Keyboard.println(\"Press '#' to return to default state\");\n      curPLen = 0;\n    }\n    else {\n      curPLen = 0;\n    }\n  }\n}");
        break;
      case '#':
        inter = false;
        break;
    }
  }
}

void keyrec(char key) { //password input and checking function
  if (inter == false){
    input[curPLen] = key;
    curPLen++;
  }
  if ((curPLen) == (pLen - 1)) {
    if (strcmp(input, password) == 0) {
      inter = true;
      Keyboard.println("");
      Keyboard.println("Interactive mode:");
      Keyboard.println("Press '1' to dump data");
      Keyboard.println("Press '2' to dump input translate script (python3)");
      Keyboard.println("Press '3' to dump firmware (arduino)");
      Keyboard.println("Press '#' to return to default state");
      curPLen = 0;
    }
    else {
      curPLen = 0;
    }
  }
}
