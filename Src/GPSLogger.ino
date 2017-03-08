#include <MapleFreeRTOS821.h>
#include <Adafruit_SSD1306_STM32.h>
#include <TinyGPS++.h>

#include "ScreenManager.h"
#include "Buttons.h"

//TinyGPSPlus gps;

void vLEDFlashTask(void *pvParameters) 
{
	for (;;) 
	{
		vTaskDelay(1000);
		digitalWrite(PC13, HIGH);
		vTaskDelay(150);
		digitalWrite(PC13, LOW);
	}
}


// the setup function runs once when you press reset or power the board
void setup()
{
	pinMode(PC13, OUTPUT);
	
	Serial.begin(115200);

	initDisplay();
	initButtons();
	initScreens();	
	
	// Set up threads
	// TODO: Consider encapsulating init and task functions into a class(es)
	xTaskCreate(vLEDFlashTask, "LED Task",	configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vDisplayTask, "Display Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);
	xTaskCreate(vButtonsTask, "Buttons Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL);

	// Run scheduler and all the threads
	vTaskStartScheduler();
}

// Arduino boilerplate function. Do not write any code here, it would not execute.
void loop()
{
}

