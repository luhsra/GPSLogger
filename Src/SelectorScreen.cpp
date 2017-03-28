#include <Adafruit_SSD1306_STM32.h>

#include "8x12Font.h"
#include "SelectorScreen.h"
#include "ScreenManager.h"

extern Adafruit_SSD1306 display;

SelectorScreen::SelectorScreen(const char ** items, uint8 cnt)
{
	itemsList = items;
	count = cnt;
	currentIdx = 0;
}

void SelectorScreen::drawScreen() const
{
	Serial.println("SelectorScreen::drawScreen()");
	
	display.setFont(&Monospace8x12Font);
	if(currentIdx != count)
		drawCentered(itemsList[currentIdx], 26);
	else
		drawCentered("Back", 26);
}

void SelectorScreen::drawCentered(const char * str, uint8 y) const
{
	uint8 x = display.width() / 2 - strlen(str) * 8 / 2;
	display.setCursor(x, y);
	display.print(str);
}

void SelectorScreen::onSelButton()
{
	currentIdx++;
	currentIdx %= (count + 1); // +1 to account 'Back' value
}

void SelectorScreen::onOkButton()
{
	// Perform an action associated with selected item
	if(currentIdx < count)
		applySelection(currentIdx);
	
	// Reset the index so user starts from the beginning next time
	currentIdx = 0;	
	
	// Back to previous screen
	backToParentScreen();
}

const char * SelectorScreen::getSelButtonText() const
{
	static const char text[] PROGMEM = "NEXT";
	return text;
}

const char * SelectorScreen::getOkButtonText() const
{
	static const char text[] PROGMEM = "OK";
	return text;
}