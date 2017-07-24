/*

Put this file in your libraries folder along with MomentaryButton.h

Written by Mark Fickett
Modified by Julian Loiacono December '14
*/

#include "mButton.h"


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
	digitalWrite(pin, HIGH);
	holdThreshold = 250;
	bounceThreshold = 50;
}

void MomentaryButton::check()
{
	unsigned long currentTimeMillis = millis();
	boolean isClosed = (digitalRead(pin) == LOW);

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
