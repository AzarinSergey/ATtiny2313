#include <avr/io.h>
#include "attiny2313.h"

void SwitchDebugLed(void);
void SwitchClockedLed(void);

#define DEBUG_LED (1 << PD0)
#define DEBUG_LED_ENABLE (PORTD |= DEBUG_LED)
#define DEBUG_LED_DISABLE (PORTD &= ~DEBUG_LED)

#define DEBUG_BUTTON (1 << PD1)
#define DEBUG_BUTTON_PRESSED !(PIND & DEBUG_BUTTON)

#define CLOCKED_LED (1 << PD6)
#define CLOCKED_LED_ENABLE (PORTD |=  CLOCKED_LED)
#define CLOCKED_LED_DISABLE (PORTD &= ~CLOCKED_LED)
  


int main(void)
{
	//set as output
	DDRD |= (DEBUG_LED | CLOCKED_LED);
	
	// set as input (PIND) with pull up resistor
	DDRD &= ~DEBUG_BUTTON; //set
	PORTD |= DEBUG_BUTTON; //enable pull up resistor (+5 v on pin)
	
	CLOCK_MODE_CTC; // Clock mode: Clear Timer on Compare Match (CTC) mode.
	CLOCK_MODE_FREQ_PRESCALER_1024; //0x05; The frequency of clock. Clock source CLK/1024, start timer
	CLOCK_NUMBER_TO_COUNT_UP_TO  = 0xFF;      // number to count up to - 255. The counter will count up to the value in this register and then trigger.
	
	while(1)
	{
		SwitchDebugLed();
		
		SwitchClockedLed();
	}
}

void SwitchDebugLed(void)
{
	if(DEBUG_BUTTON_PRESSED)
	{
		DEBUG_LED_ENABLE;
	}
	else
	{
		DEBUG_LED_DISABLE;
	}
}

char clockedLedToggle = 0;
void SwitchClockedLed()
{
	if (CLOCK_TIMED_OUT) {      // timer timed out?
		CLOCK_RESET;       // reset timer flag. OCF0A in TIFR register is cleared by writing a logic one to the flag
		// toggle LED each time the timer times out
		if (clockedLedToggle) {
			clockedLedToggle = 0;
			CLOCKED_LED_ENABLE;
		}
		else {
			clockedLedToggle = 1;
			CLOCKED_LED_DISABLE;
		}
	}
}

