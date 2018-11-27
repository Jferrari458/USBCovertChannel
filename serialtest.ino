// Simple test of USB Host
//
// This example is in the public domain


// This is an example file from the USBHost_t36 library, the code below was what I used to get the keyboard to pass through 
// after connecting the keyboard to a hub, then the hub to the teensy, then the teensy to the host

#include "USBHost_t36.h"

USBHost myusb;
USBHub hub1(myusb);
USBHub hub2(myusb);
USBHub hub3(myusb);
KeyboardController keyboard1(myusb);
KeyboardController keyboard2(myusb);
MIDIDevice midi1(myusb);

void setup()
{
	while (!Serial) ; // wait for Arduino Serial Monitor
	Serial.println("USB Host Testing");
	myusb.begin();
	keyboard1.attachPress(OnPress);
	keyboard2.attachPress(OnPress);
	midi1.setHandleNoteOff(OnNoteOff);
	midi1.setHandleNoteOn(OnNoteOn);
	midi1.setHandleControlChange(OnControlChange);
}


void loop()
{
	myusb.Task();
	midi1.read();
	// implement a last input timer, if input = 1, reset timer and clear input to 0. if seconds > x and input == 0, open shell
}


void OnPress(int key) // This is where key strokes are processed. This is where we can validate password, implement a last input timer
{
	Serial.print("key '");
	Serial.print((char)key);
	Serial.print("'  ");
	Serial.println(key);
	//Serial.print("key ");
	//Serial.print((char)keyboard1.getKey());
	//Serial.print("  ");
	//Serial.print((char)keyboard2.getKey());
	//Serial.println();
}

// Still not sure how this works at all

void OnNoteOn(byte channel, byte note, byte velocity)
{
	Serial.print("Note On, ch=");
	Serial.print(channel);
	Serial.print(", note=");
	Serial.print(note);
	Serial.print(", velocity=");
	Serial.print(velocity);
	Serial.println();
}

void OnNoteOff(byte channel, byte note, byte velocity)
{
	Serial.print("Note Off, ch=");
	Serial.print(channel);
	Serial.print(", note=");
	Serial.print(note);
	//Serial.print(", velocity=");
	//Serial.print(velocity);
	Serial.println();
}

void OnControlChange(byte channel, byte control, byte value)
{
	Serial.print("Control Change, ch=");
	Serial.print(channel);
	Serial.print(", control=");
	Serial.print(control);
	Serial.print(", value=");
	Serial.print(value);
	Serial.println();
}

