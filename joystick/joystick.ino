#include <XInput.h>

// SETUP
const boolean UseLeftJoystick = true;
const boolean InvertLeftYAxis = false;
const boolean UseRightJoystick = true;
const boolean InvertRightYAxis = false;

const int ADC_Max = 1023;  // 10 bit

// Joystick Pins
// Set up the analog pins
const int Pin_LeftJoyX = A1;
const int Pin_LeftJoyY = A0;
const int Pin_RightJoyX = A3;
const int Pin_RightJoyY = A2;

// Button Pins
// Set up the digital pins
const int Pin_ButtonA = 2;
const int Pin_ButtonB = 3;
const int Pin_ButtonX = 4;
const int Pin_ButtonY = 5;

// Directional Pad Pins
const int Pin_DpadUp    = 10;
const int Pin_DpadDown  = 11;
const int Pin_DpadLeft  = 12;
const int Pin_DpadRight = 13;

void setup() {
  // Set buttons as inputs, using internal pull-up resistors
	pinMode(Pin_ButtonA, INPUT_PULLUP);
	pinMode(Pin_ButtonB, INPUT_PULLUP);
	pinMode(Pin_ButtonX, INPUT_PULLUP);
	pinMode(Pin_ButtonY, INPUT_PULLUP);

  pinMode(Pin_DpadUp, INPUT_PULLUP);
	pinMode(Pin_DpadDown, INPUT_PULLUP);
	pinMode(Pin_DpadLeft, INPUT_PULLUP);
	pinMode(Pin_DpadRight, INPUT_PULLUP);

  XInput.setJoystickRange(0, ADC_Max);
	XInput.setAutoSend(false);

	XInput.begin();
}

void loop() {
  boolean buttonA = digitalRead(Pin_ButtonA);
	boolean buttonB = digitalRead(Pin_ButtonB);
	boolean buttonX = digitalRead(Pin_ButtonX);
	boolean buttonY = digitalRead(Pin_ButtonY);

  boolean dpadUp = digitalRead(Pin_DpadUp);
	boolean dpadDown = digitalRead(Pin_DpadDown);
	boolean dpadLeft = digitalRead(Pin_DpadLeft);
	boolean dpadRight = digitalRead(Pin_DpadRight);

  // Set XInput buttons
  // Convert the input into the Xbox respective
	XInput.setButton(BUTTON_A, buttonA);
	XInput.setButton(BUTTON_B, buttonB);
	XInput.setButton(BUTTON_X, buttonX);
	XInput.setButton(BUTTON_Y, buttonY);

  // Set XInput DPAD values
	XInput.setDpad(dpadUp, dpadDown, dpadLeft, dpadRight);

  // Set left joystick
	if (UseLeftJoystick == true) 
  {
		int leftJoyX = analogRead(Pin_LeftJoyX);
		int leftJoyY = analogRead(Pin_LeftJoyY);

		boolean invert = !InvertLeftYAxis;

		XInput.setJoystickX(JOY_LEFT, leftJoyX);
		XInput.setJoystickY(JOY_LEFT, leftJoyY, invert);
	}

  // Set right joystick
	if (UseRightJoystick == true) {
		int rightJoyX = analogRead(Pin_RightJoyX);
		int rightJoyY = analogRead(Pin_RightJoyY);

		boolean invert = !InvertRightYAxis;

		XInput.setJoystickX(JOY_RIGHT, rightJoyX);
		XInput.setJoystickY(JOY_RIGHT, rightJoyY, invert);
	}

	XInput.send();
}
