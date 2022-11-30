#include <XInput.h>

// SETUP
const boolean UseLeftJoystick = true;
const boolean InvertLeftYAxis = false;

const int ADC_Max = 1023;  // 10 bit

// Joystick Pins
// Set up the analogic pins
const int Pin_LeftJoyX = A1;
const int Pin_LeftJoyY = A0;

// Button Pins
// Set up the digital pins
const int Pin_ButtonA = 2;
const int Pin_ButtonB = 3;
const int Pin_ButtonX = 4;
const int Pin_ButtonY = 5;

void setup() {
  // Set buttons as inputs, using internal pull-up resistors
	pinMode(Pin_ButtonA, INPUT_PULLUP);
	pinMode(Pin_ButtonB, INPUT_PULLUP);
	pinMode(Pin_ButtonX, INPUT_PULLUP);
	pinMode(Pin_ButtonY, INPUT_PULLUP);

  XInput.setJoystickRange(0, ADC_Max);
	XInput.setAutoSend(false);

	XInput.begin();
}

void loop() {
  boolean buttonA = digitalRead(Pin_ButtonA);
	boolean buttonB = digitalRead(Pin_ButtonB);
	boolean buttonX = digitalRead(Pin_ButtonX);
	boolean buttonY = digitalRead(Pin_ButtonY);

  // Set XInput buttons
  // Convert the input into the Xbox respective
	XInput.setButton(BUTTON_A, buttonA);
	XInput.setButton(BUTTON_B, buttonB);
	XInput.setButton(BUTTON_X, buttonX);
	XInput.setButton(BUTTON_Y, buttonY);

  // Set left joystick
	if (UseLeftJoystick == true) 
  {
		int leftJoyX = analogRead(Pin_LeftJoyX);
		int leftJoyY = analogRead(Pin_LeftJoyY);

		boolean invert = !InvertLeftYAxis;

		XInput.setJoystickX(JOY_LEFT, leftJoyX);
		XInput.setJoystickY(JOY_LEFT, leftJoyY, invert);
	}

	XInput.send();
}
