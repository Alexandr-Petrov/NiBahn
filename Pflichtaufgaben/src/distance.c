/**
 * @file distance.c
 *
 * @brief
 * Functions for locating hindrances and finding a free path.
 * Functions read information from the distance sensors of the Nibo2
 *
 * @author Arina Lavrova
 * @version 11.2019
 */


#include "main.h"

/*
 * @brief
 *
 * Function for guiding the Nibo by determining the position of hindrances
 *
*/
void findDirection()
{
	int r;
	drive(); 	///Nibo goes forward
	showNibo(); ///Shows Nibo on display

	static int flag; 	/*
						 * flag - variable to determine if the robot reached the end of the tunnel
						 * 1 - reached
						 * 0 - not reached (or Nibo left the tunnel)
						 */
	static int timer=0; /*
						 * timer - variable for counter: how long the Nibo
						 * rode from beginning to end of the tunnel
						 */
	///Tunnel
	/// If Nibo reached the end of the tunnel:
	if (copro_distance[0]/256 > 200 &&
		copro_distance[2]/256 > 150 &&
		copro_distance[4]/256 > 200)
		{
			copro_stop();
			flag=1; /// set flag to 1
		}
	///If Nibo rides forward through the tunnel:
	if (copro_distance[0]/256 > 150 &&
		copro_distance[4]/256 > 150)
			{
				timer++; ///counter increases

				/*
				 * If Nibo reached the end of the tunnel and the counter is not equal -2:
				 *
				 */
				if(flag==1 && timer!=-2)
				{
					goBack(); ///Nibo goes back
					LEDShow('r', 0, 1); /// sets LEDs 0-1 to red
					timer--; ///counter decreases
				}
			}
	///If Nibo left the tunnel:
	else
	{
		leds_set_status(LEDS_OFF, 0); /// switch off right back LED
		leds_set_status(LEDS_OFF, 1); /// switch off left back LED
	}
	/// Exit from the tunnel. If a wall is on the right side:
	if (copro_distance[0]/256 > 50 &&
		copro_distance[4]/256 < 50 &&
		flag==1)
		{
			turnLeft();/// Nibo turns left
			LEDShow('g', 0, 1); /// sets LEDs 0-1 to green
			delay(1500); /// wait 1 second, Nibo turns
			flag=0; /// set flag to 0
			timer=0; /// reset counter

		}
	/// Exit from the tunnel. Wall is on the left side:
	if (copro_distance[4]/256 > 50 &&
		copro_distance[0]/256 < 50 &&
		flag==1)
		{
			turnRight(); /// Nibo turns right
			LEDShow('g', 0, 1); /// sets LEDs 0-1 to green
			delay(1500); /// wait 1 second, Nibo turns
			flag=0; ///  set flag to 0
			timer=0; /// reset counter
		}
	/// Exit from the tunnel. no walls, Nibo randomly chooses where to turn:
	if (copro_distance[4]/256 < 50 &&
		copro_distance[0]/256 < 50 &&
		flag==1)
		{
			r = rand() % 2; /// generate a number between 0 and 1
			if(r==0){
				turnLeft(); /// if the number is "0", Nibo turns left
			}
			else{
				turnRight();/// if the number is not "0", Nibo turns right
			}
			LEDShow('g', 0, 1); /// sets LEDs 0-1 to green
			delay(1500); /// wait 1 second, Nibo turns
			flag=0; /// set flag to 0
			timer=0;/// reset counter
		}
		///Hindrance is right:
		if (copro_distance[0]/256 > 150 &&
			copro_distance[1]/256 > 100 &&
			copro_distance[2]/256 > 170 &&
			flag==0)
		{
			LEDShow('r', 5, 7); ///set LEDs 5-7 to red
			turnLeft(); /// Nibo turns left on 90 degrees
			hindranceShow(40, 50);///show the position of Hindrance
			hindranceShow(40, 30);
			hindranceShow(65, 50);
		}
		else
		{
			LEDShow('g', 5, 7); /// if Hindrance is not right, set LEDs 5-7 to green
		}

		///Hindrance is top-right
		if (copro_distance[1]/256 > 180 &&
			//copro_distance[0]/256 < 150 &&
			flag==0 )
		{
			LEDShow('r', 6, 6); ///set LED 6 to red
			turnHalfLeft(); /// Nibo turns left on 45 degrees
			hindranceShow(40, 50); ///Show the position of Hindrance
	     }
		else {LEDShow('g', 6, 6);}///set LED 6 to green

		///Hindrance is left
		if (copro_distance[4]/256 > 150 &&
			copro_distance[3]/256 > 100 &&
			copro_distance[2]/256 > 170 &&
			flag==0)
		{
			LEDShow('r', 2, 4);///set LEDs 2-4 to red
			turnRight(); /// Nibo turns right on 90 degrees
			hindranceShow(90, 50); ///show the position of Hindrance
			hindranceShow(90, 30);
			hindranceShow(65, 50);
		}
		else
		{
			LEDShow('g', 2, 4);///set LEDs 2-4 to green
		}
		///Hindrance is top-left
		if (copro_distance[3]/256 > 180 &&
			//copro_distance[0]/256 < 150 &&
		    flag==0)
		{
			LEDShow('r', 3, 3);///set LED 3 to red
			turnHalfRight(); /// Nibo turns right on 45 degrees
			hindranceShow(85, 50);//Show the position of Hindrance
		 }
		else {LEDShow('g', 3, 3);}///set LED 3 to green

		///Hindrance is ahead
			/// (Left)
		if (copro_distance[2]/256 > 170 &&
			copro_distance[1]/256 > 60 &&
			copro_distance[4]/256 < 50 &&
			copro_distance[0]/256 < 50)
		{
			LEDShow('r', 4, 5);///set LEDs 4-5 to red
			turnLeft(); /// Nibo turns left
		}
			/// (Right)
		if (copro_distance[2]/256 > 170 &&
			copro_distance[3]/256 > 60 &&
			copro_distance[4]/256 < 50 &&
			copro_distance[0]/256 < 50)
		{
			LEDShow('r', 4, 5); ///set LEDs 4-5 to red
			turnRight();/// Nibo turns right
		}
			/// (Ahead)
		if (copro_distance[2]/256 > 220 &&
			copro_distance[4]/256 < 50 &&
			copro_distance[0]/256 < 50)
		{
			LEDShow('r', 4, 5); ///set LEDs 4-5 to red
			copro_setTargetRel(-54, 54, 20);/// Nibo turns on 180 degrees
		}
}
