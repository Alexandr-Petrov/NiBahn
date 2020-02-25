#include "main.h"
/**
 * @file start.c
 * @brief File with functions with the countdown before starting the main program.
 *
 * @author Arina Lavrova
 * @version 11.2019
 */

/**
 *
 * @brief Function from the Project "HelloSound" for creating sounds on the Nibo
 *
 * @author Daniel Wittekind
 *
 */
int tone(int frequency, int duration) {
	int interval = (50000 / frequency);
	duration = duration * 100;

	while (duration) {
		int i = interval;
		clear_output_bit(IO_AUDIO);
		while (duration && i) {
			duration--;
			i--;
			delay_us(10);
		}
		i = interval;
		set_output_bit(IO_AUDIO);
		while (duration && i) {
			duration--;
			i--;
			delay_us(10);
		}
	}

	return 1;
}
/**
 * @brief
 *
 * Function for visual and sound representation of a countdown.
 * After 4 signals (3 red and 1 green), the main program starts
 *
 * @author Arina Lavrova
 * @version 11.2019
 */

void start(){

	/// Initialization of LEDs numbers
	int led1=2; /// led1 - start left LED
	int led2=7; /// led2 - start right LED

	leds_set_headlights(250); /// Turn on the two headlights.

	/// Show user info
	gfx_move(4, 0);///Sets the point from which to write
	gfx_print_text("To start the program,"); /// write the welcome-text to the display
	gfx_move(4, 13);
	gfx_print_text("Press the S3 button");
	gfx_move(50, 23);
	gfx_print_text("----->");
	gfx_move(4, 35);
	gfx_print_text("To stop the program");
	gfx_move(4, 48);
	gfx_print_text("Press the S2 button");
	gfx_move(50, 55);
	gfx_print_text("<-----");
	deactivate_output_bit(IO_INPUT_1);
	while(get_input_bit(IO_INPUT_1)){ ///If S3 start-button not pressed, do nothing (only text on display)
	}

	if (!get_input_bit(IO_INPUT_1)) /// If S3 start button pressed
	{
		delay(800); /// wait 0,8s before start of the countdown
		for(int i=4; i>0; i--){ /// 4 steps before the program will be start
			if(i>1){ /// For first 3 steps:
				leds_set_status(LEDS_RED, led1); /// Sets the left LED to red
				leds_set_status(LEDS_RED, led2); /// Sets the right LED to red
				cli();	/// Atomic state: so that the sounds are played correctly.
				tone(392, 100);
				sei(); /// End of Atomic state: interrupts are now possible again
				leds_set_status(LEDS_OFF, led1); /// Switch off left LED
				leds_set_status(LEDS_OFF, led2);/// Switch off right LED
				led1++; ///change the number of left LED
				led2--; ///change the number of right LED
			}

			if(i==1){ /// For the last step:
				leds_set_status(LEDS_GREEN, led1); /// Sets the left LED to green
				leds_set_status(LEDS_GREEN, led2); /// Sets the left LED to green
				cli(); /// Atomic state: so that the sounds are played correctly.
				tone(800, 100);
				sei(); /// End of Atomic state: interrupts are now possible again
			}
			delay(500); /// wait 0,5s
		}
	}
	leds_set_headlights(0); /// In the end switch off headlight
}
