/*

Put this file in your libraries folder along with MomentaryButton.h

Written by Mark Fickett
Modified by Julian Loiacono December '14
*/

#include "mButton.h"

// Switch S2 behaviour
//#define __S2_To_HIGH__
//#define __S2_To_LOW__  // default to this, as original
//#define __MULTI_PUSH_S2__

MomentaryButton::MomentaryButton(int inputPin)
	: wasClosed(false), pin(inputPin)
{}

void MomentaryButton::setThreshold(unsigned long newThreshold)
{
	holdThreshold = newThreshold;
}

void MomentaryButton::setup()
{
	pinMode(pin, INPUT);
#if defined (__S2_To_HIGH__)
	digitalWrite(pin, LOW);  // setting this to LOW, with pull down resistors, as the button S2 now pulls up.
#else 
  digitalWrite(pin, HIGH);  // setting this to HIGH, with pull up resistors, as the button S2 now pulls down.
#endif

	holdThreshold = 250;
	bounceThreshold = 50;
}

void MomentaryButton::check()
{
	unsigned long currentTimeMillis = millis();
#if defined (__S2_To_HIGH__)
  boolean isClosed = (digitalRead(pin) == HIGH);
#else
  boolean isClosed = (digitalRead(pin) == LOW);
#endif
	if (isClosed & !wasClosed)
	{
		closeTimeMillis = currentTimeMillis;
	}
	else if (!isClosed & wasClosed)
	{
		held = (currentTimeMillis - closeTimeMillis) >= holdThreshold;
		clicked = (!held && (currentTimeMillis - closeTimeMillis) >= bounceThreshold);
	}

	wasClosed = isClosed;
}

boolean MomentaryButton::wasClicked() {
	if (clicked){
		clicked = false;
		return true;
	}
	else{
		return false;
	}
}

boolean MomentaryButton::wasHeld() {
	if (held){
		held = false;
		return true;
	}
	else{
		return false;
	}
}
