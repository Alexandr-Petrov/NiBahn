/*! \mainpage Pflichtaufgaben (Version 2.1)
 *
 * \section intro_sec Introduction
 * \subsection info_sec Project Information
 * In Embedded Systems and Robotics 1 at TH-Wildau,
 * we've got small robots controlled by a main controller and co-controller, lots of sensors, can move around
 * and also show the data on the display. As tasks we have received mandatory and cure tasks.
 * The mandatory tasks that have been solved:
 * 1. Recognizing and avoiding obstacles
 * 2. Entrance and exit from the tunnel
 * 3. Visualization using the display and LED
 *
 * \subsection software_sec Used Software
 * Setting up an EclipseCDT project for Nibo programming is complicated,
 * as a lot of information needs to be entered at specific locations in the IDE.
 * VMWare Image already provides a deployed project in EclipseCDT. This was used as a template for own projects.
 * \subsection hardware_sec Used Hardware
 * |    ID           |    Component            |    Name and parameters                             |    Purpose                                             |    Principle of operation                               |
 * |-----------------|-------------------------|----------------------------------------------------|--------------------------------------------------------|---------------------------------------------------------|
 * |    ID_1         |    Main processor       |    ATmega128A, 128kByte Flash , 16MHz              |    Execution of the program                            |    Electronic                                           |
 * |    ID_2         |    Coprocessor          |    ATmega88A, 8kByte Flash , 16MHz                 |    Motor   control and distance measurement            |    Electronic                                           |
 * |    ID_3         |    Distance sensors     |    5 *   IR emitter /sensors, reflection method    |    Measurement of distances                            |    Measurement of reflection of the infrared light    |
 * |    ID_4         |    Actuators            |    2 motors   (a 1.5W) with 1:25 ratio             |    Movement of wheels                                  |    Electromagnetic induction                            |
 * |    ID_5         |    Odometry             |    4 IR sensors                                    |    Measurement of direction of rotation and speed      |    Measurement of reflection of the infrared light    |
 * |    ID_6         |    LEDs                 |    8 two-color LEDs ( red/green )                  |    Display of obstacles                                |    Measurement of reflection of the infrared light    |
 * \section file_sec Description of project files
 * |    №    |    Name              |    Beschreibung                                                                                                                                           |
 * |---------|----------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
 * |    1    |    Main.c            |    Hauptdatei.   Enthält unendliche Schleife.                                                                                                             |
 * |    2    |    Main.h            |    Enthält   grundlegende Typedefs, globale Makros und alle Includes, die man für den   Nibo2 braucht.                                                    |
 * |    3    |    Distance.c        |    Funktionen zum   Auffinden von Hindernissen und zum Finden eines freien Pfades. Funktionen   lesen Informationen von den Abstandssensoren des Nibo2    |
 * |    4    |    Drive.c           |    Funktionen für   Nibos Bewegung (Fahren und Wenden)                                                                                                    |
 * |    5    |    Start.c           |    Funktionen mit   dem Countdown vor dem Start des Hauptprogramms.                                                                                       |
 * |    6    |    Presentation.c    |    Funktionen zur Visualisierung der Position eines   Hindernisses in Bezug auf Nibo                                                                      |
 *
 *
 */


/**
 * @file main.c
 * @brief Main Function of the Project
 *
 * @author Arina Lavrova
 * @version 11.2019
 */

#include "main.h"

/* @brief
 *
 * Main Function
*/
int main() {

		/// turn on the interrupts. Needed for the PWM
		sei();

		/// initialization of the robot (always necessary)
		bot_init();

		/// Initialization of the SPI interface
		spi_init();

		/// Initialization of the speaker
		sound_init();

		/// Initialization of the LEDs
		leds_init();

		/// Initialization of the pulse width modulation
		pwm_init();

		/// Initialization of display and graphics functions
		display_init();
		gfx_init();

		/// Switch on distance measurement
		copro_ir_startMeasure();

		/// Function for launching a program by a user
		start();

		/// Endless loop:
		while (1 == 1) {
			/// empty the display
			gfx_fill(0);

			/// update coprocessor values
			copro_update();
			/// function for navigation
			findDirection();

			/// wait 0,5s
			delay(500);
		}
}

