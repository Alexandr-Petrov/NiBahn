/**
 * @file presentation.c
 * @brief File with functions for visualizing the location of a hindrance relative to Nibo
 *
 * @author Arina Lavrova
 * @version 11.2019
 */

#include "main.h"

/**
 * @brief
 *
 * Function for showing the location
 * of a hindrance relative to Nibo with LEDs
 *
 * @param color Color of LED (r-red, g-green)
 * @param start Number of start LED
 * @param end Number of end LED
 */
void LEDShow(char color, int start, int end){
	for(int i=start; i<=end; i++){
		/// For all LEDs between start and end LEDs (including start end LEDs):
		if(color=='r'){ leds_set_status(LEDS_RED, i);} ///If the first parameter is "r", set LED number i to red
		else leds_set_status(LEDS_GREEN, i); ///If the first parameter is "g", set LED number i to green
	}
}

/**
 * @brief
 *
 * Function for showing Nibo on display
 */
void showNibo()
{
	/// Nibo's picture
	gfx_move(53, 12); ///Sets the point from which to draw (53, 12)
	gfx_box(4, 6);    ///Draws the box. First argument is width=4, second is height=6

	gfx_move(75, 12); ///Sets the point from which to draw (75, 12)
	gfx_box(4, 6);	  ///Draws the box. First argument is width=4, second is height=6

	gfx_move(59, 14); ///Sets the point from which to draw (59, 14)
	gfx_box(14, 8);	  ///Draws the box. First argument is width=14, second is height=8

	gfx_move(61, 22); ///Sets the point from which to draw (61, 22)
	gfx_box(10, 3);	  ///Draws the box. First argument is width=10, second is height=3
}


/**
 * @brief
 *
 * Function for showing the location
 * of a hindrance relative to Nibo on display.
 * Draws one triangle with an exclamation mark inside.
 *
 * @param x Abscissa starting point
 * @param y Ordinate starting point
 */
void hindranceShow(int x, int y){
	gfx_move(x, y); ///Sets the point from which to draw (x - function parameter, y - function parameter)
	gfx_lineTo(x+7,y-17); ///Draws a line from x, y to x+7,y-17
	gfx_lineTo(x-7,y-17);///Draws a line from  x+7,y-17 to x-7,y-17
	gfx_lineTo(x, y); ///Draws a line from x-7,y-17 to start point x,y
	gfx_move(x, y-7);///Sets the point from which to draw (x, y-7)
	gfx_lineTo(x,y-13);///Draws a line from x,y-7 to start point x,y-13
	gfx_move(x, y-15); ///Sets the point from which to draw (x, y-15)
	gfx_hline(1); ///Draws a horizontal line from the current position to the right - makes one point

}
