/*! \mainpage Kueraufgaben (Version 07.12.2019)
 *
 * \section intro_sec Introduction
 * \subsection info_sec Project Information
 * As part of the T_17 group that enrolled in the course Embedded Systems and Robotics 1 at TH-Wildau,
 * we've got small robots controlled by a main controller and co-controller, lots of sensors, can move around.
 * and also show the data on the display. As a task we have received mandatory tasks and tasks that we were able to choose ourselves.
 * in the tasks that we have chosen we have implemented mandatory functions:
 * 1. Communication between the Nibo and PC using xBee
 * 2. Communication between Nibos using xBee
 * 3. Following the black line(extra function)
 * 4. Visualization of the role of the Nibo in the chain using the display and LEDs
 *
 * \subsection software_sec Used Software
 * 1. VMWare Image already provided by the Docent with a deployed projects HelloXBee and HelloxBee_PC in EclipseCDT that were used as the template for the own projects
 * 2. DIGI XCTU configuration and test utility for xBee module
 *
 * \subsection hardware_sec Used Hardware
 * |    ID           |    Component            |    Name and parameters                             |    Purpose                                             |    Principle of operation                               |
 * |-----------------|-------------------------|----------------------------------------------------|--------------------------------------------------------|---------------------------------------------------------|
 * |    ID_1         |    Main processor       |    ATmega128A, 128kByte Flash , 16MHz              |    Execution of the program                            |    Electronic                                           |
 * |    ID_2   		 |    Coprocessor          |    ATmega88A, 8kByte Flash , 16MHz                 |    Motor control and floor color measurement           |    Electronic                                           |
 * |    ID_3         |    Actuators            |    2 motors   (a 1.5W) with 1:25 ratio             |    Movement of wheels                                  |    Electromagnetic induction                            |
 * |    ID_4         |    odometry             |    2 IR line sensors                               |    Recognition of the black line			   		     |    Measurement   of reflection of the infrared light    |
 * |    ID_5         |    LEDs                 |    8 two-color LEDs ( red/green )                  |    Display of the Role of the Nibo                     |    Visible light Radiation			       |
 * |    ID_6         |    Communication module |    NXB2 xBee extension				    			|	 Communication with PC and other Nibos               |    Electromagnetic radiation  			       |
 * \section file_sec Description of project files
 * |    №    |    Name              |    Description                                                                                                                                          	|
 * |---------|----------------------|-----------------------------------------------------------------------------------------------------------------------------------------------------------|
 * |    1    |    Nibahn.c          |    Main file                                                                                                            					|
 * |    2    |    Nibo_actions.c    |    File with functions performing movement and communication funtions of Nibo  										|
 * |    3    |    Nibo_actions.h    |    Header file for Nibo_actions.c                                                                                                   			|
 * |    4    |    protokoll.c       |    File with functions used to form bytes in the predefined format for communication                                                                      |
 * |    5    |    protokoll.h       |    Header file for protokoll.c, also used to define data types for the communication                                                                      |
 * |    6    |    xBee.c            |    File with functions that allow to work with xBee module                                                                     				|
 * |    7    |    xBee.h    	    |    Header file for xBee.c                                                                     								|
 */

/**
 * @file Nibahn.c
 * @author Alexandr Petrov and Jan Bischof
 *
 * @version 04.12.2019
 *
 * @brief This is the main file of the Nibahn Project, used functions will be called from there
 */

/// libraries for standard functions of the Nibo2
#include <nibo/niboconfig.h>
#include <nibo/iodefs.h>
#include <nibo/bot.h>

/// library for standard input and output operations of the Nibo2
#include <stdio.h>

/// includes interrupts
#include <stdint.h>

/// delay functions
#include <nibo/delay.h>
#include <nibo/copro.h>

/// include delay operations
#include <nibo/delay.h>

/// includes library for interaction with floor sensors
#include <nibo/floor.h>

/// includes SPI communication library
#include <nibo/spi.h>

/// includes microcontroller hardware interrupts
#include <avr/interrupt.h>

/// library for control of the LEDs
#include <nibo/leds.h>

/// includes xBee Communication
#include "xBee.h"

/// includes functions and data types for xBee communication in Nibahn Project
#include "protokoll.h"

/// includes functions for Nibo
#include "Nibo_actions.h"

/**
 * @brief
 * Main function of the Nibahn.c file.
 * Does the main calculations and controls the behavior of Nibo
 */

int main(){

	/// initialize the LEDs
	leds_init();

    /// initialize the robot
    bot_init();

    /// initialize spi-port
    spi_init();

    /// initialize the floor sensors
	floor_init();

    /// declare and initialize a variable for storing received bytes
    uint8_t x=0;

    /// initialize xBee Module
    xBee_init();

    /// for saving the values gotten from the sensors
    unsigned int current_floorL = 0, current_floorR = 0;
    /// for saving the current Speed value and setting the reelection_delay
    short Speed = 0, reelection_delay = 2000;
    /// for saving the flag values
	short flag_id_established = 0, ignore_line = 0;
	/// for saving the ID of the Nibo and maximum number of Nibos in the chain
	u8_t ownId = 0b01, maxnibos = 0b11;
	delay(10000);

    /// Operation loop
    while (1) {

    	/// if Nibo is the master
    	if ((int)ownId == 1)
			{
    			/// Sets the front LEDs Orange
				leds_set_status(LEDS_ORANGE, 4);
				leds_set_status(LEDS_ORANGE, 5);
			}
    	/// if Nibo is not participating in the chain
    	else if((int)ownId == 0)
			{
    		/// Sets the front LEDs Red
				leds_set_status(LEDS_RED, 4);
				leds_set_status(LEDS_RED, 5);
			}
    	/// if Nibo is not a master
    	else
			{
    			/// Sets the front LEDs Red
				leds_set_status(LEDS_GREEN, 4);
				leds_set_status(LEDS_GREEN, 5);
			}
    	/// if send buffer is not full and the ID of this Nibo was not established yet
    	if(xBee_readyToSend() && flag_id_established == 0)
			{
    			/// sets the flag of ID to established
				flag_id_established = 1;
				/// forms the byte to claim the ID
				x = buildSendData(ownId, ownId, 0b1000);
				/// sends the formed byte
				xBee_sendByte(x);
			}
        /// if the receive buffer is not empty
        if (xBee_receivedData())
        {
            /// -> get next received data byte of the buffer
            x = xBee_readByte();

            /// if it's a broadcast and not with the command from the second set or if it's sent to the ID of this Nibo
            if(((sendDataGetReciver(x) == 0b00) && (sendDataGetFunctionSet(x) != 0b01)) || (sendDataGetReciver(x) == ownId))
            	{
            		/// if it's sent from PC, Master or from the Nibo with the ID of this Nibo
					if((sendDataGetSender(x) == 0b00) || (sendDataGetReciver(x) == ownId) || (sendDataGetSender(x) == 0b01))
						{
							/// if received byte has 00 in the commands set section and nibo participates in the chain
							/// commands set 1
							if (sendDataGetFunctionSet(x) == 0b00 && ownId!=0)
								{
									/// line will not be ignored if nibo gets anything from this set of commands
									ignore_line = 0;
									/// if received byte has 00 in the commands section
									if (sendDataGetFunction(x) == 0b00)
										{
											/// speed of the Nibo will be increased
											Speed = Speedup(Speed);
										}
									/// if received byte has 01 in the commands section
									else if (sendDataGetFunction(x) == 0b01)
										{
											/// speed of the Nibo will be decreased
											Speed = Slowdown(Speed);
										}
									/// if received byte has 10 in the commands section
									else if  (sendDataGetFunction(x) == 0b10)
										{
											/// setting the flag to 0 to mark that ID is not established
											flag_id_established = 0;
											/// Nibo will turn 180 degrees left
											Directionchange_left();
											/// Nibo will enter the reelection mode and get the starting ID (1) later, to participate in the reelection
											ownId = Reelection_turn(ownId,reelection_delay,maxnibos);
										}
									/// if received byte has 11 in the commands section
									else if (sendDataGetFunction(x) == 0b11)
										{
											/// setting the flag to 0 to mark that ID is not established
											flag_id_established = 0;
											/// Nibo will turn 180 degrees right
											Directionchange_right();
											/// Nibo will will enter the reelection mode and get the starting ID (1) later, to participate in the reelection
											ownId = Reelection_turn(ownId,reelection_delay,maxnibos);
										}
								}
							/// if received byte has 01 in the commands set section
							/// commands Set 2
							else if(sendDataGetFunctionSet(x) == 0b01)
								{
									/// line will be ignored if nibo gets anything from this set of commands
									ignore_line = 1;
									/// if received byte has 00 in the commands section
									if (sendDataGetFunction(x) == 0b00)
										{
											/// Speed of the Nibo will be increased
											Speed = Speedup(Speed);
										}
									/// if received byte has 01 in the commands section
									else if (sendDataGetFunction(x) == 0b01)
										{
											/// Speed of the Nibo will be decreased
											Speed = Slowdown(Speed);
										}
									/// if received byte has 10 in the commands section
									else if  (sendDataGetFunction(x) == 0b10)
										{
											/// Nibo will turn 90 degrees left
											Turn_left();
										}
									/// if received byte has 11 in the commands section
									else if (sendDataGetFunction(x) == 0b11)
										{
											/// Nibo will turn 90 degrees right
											Turn_right();
										}
								}
							/// if received byte has 10 in the commands set section
							/// commands set 3
							 else if(sendDataGetFunctionSet(x) == 0b10)
								{
								 	/// if received byte has 00 in the commands section
									if (sendDataGetFunction(x) == 0b00)
										{
											/// if send buffer is not full
											if(xBee_readyToSend())
											{
												/// the byte to force other Nibo to select another ID is formed
												x = buildSendData(ownId, ownId, 0b1001);
												/// byte sent
												xBee_sendByte(x);
											}
										}
								 	/// if received byte has 01 in the commands section
									/// this will be true only if some other Nibo claimed current ID of this Nibo before
									else if (sendDataGetFunction(x) == 0b01 && sendDataGetSender(x) == ownId)
										{
											/// increment own ID
											ownId = ownId+1;
											/// setting the flag to 0 to mark that ID is not established
											flag_id_established = 0;
										}
								 	/// if received byte has 10 in the commands section
									else if (sendDataGetFunction(x) == 0b10)
										{
											/// will start the forced reelection process
											ownId = Reelection_forced(ownId,reelection_delay,maxnibos);
											/// setting the flag to 0 to mark that ID is not established
											flag_id_established = 0;
										}
								 	/// if received byte has 11 in the commands section
									else if (sendDataGetFunction(x) == 0b11)
										{
										/// if send buffer is not full
										if(xBee_readyToSend())
											/// set the ID of the Nibo 00 effectively switching it off from the chain
											ownId = 0b00;
											{
												/// forms the byte that will start reelection through the broadcast
												x = buildSendData(0b00, ownId, 0b1010);
												/// send the formed byte
												xBee_sendByte(x);
											}
										}
								}
							/// if received byte has 11 in the commands set section
							/// commands set 4
							 else if(sendDataGetFunctionSet(x) == 0b11)
							 	 {
								 /// If received byte has 00 in the commands section and ID of the sender Nibo is lower than of this Nibo
								 if (sendDataGetFunction(x) == 0b00 && sendDataGetSender(x) < ownId && current_floorR > 40 && current_floorL > 40)
									{
									 	 /// sets the speed to 0
									 	 copro_setSpeed(0,0);
									 	 /// speed of the wheels will be 0 for the fixed period of time
									 	 delay(350);
									}
								 	 /// Reserved for new functions
							 	 }
							}
						}
            		}
                		/// get the actual values from the floor sensors
                		floor_update();
                		/// update the values in the coprocessor
                		copro_update();
                				/// get the values from the right sensor near the line
                				current_floorR = floor_relative[LINE_RIGHT];
                				/// if black line is detected by the right line sensor and flag states that line shouldn't be ignored
                				if (current_floorR < 33 && ignore_line!=1)
                					{
                					/// if send buffer is not full
										if(xBee_readyToSend())
											{
												/// forms the byte that will stop all Nibos with lower IDs
												x = buildSendData(0b00, ownId, 0b1100);
												/// sends the formed byte
												xBee_sendByte(x);
											}
										/// slightly turns to the right
                						copro_setTargetRel(4, 0, 14);
                					}
                				/// get the values from the left sensor near the line
                				current_floorL = floor_relative[LINE_LEFT];
                				/// if black line is detected by the left line sensor and flag states that line shouldn't be ignored
                				if (current_floorL < 33 && ignore_line!=1)
                					{
                						/// if send buffer is not full
                						if(xBee_readyToSend())
											{
                								/// forms the byte that will stop all Nibos with lower IDs
												x = buildSendData(0b00, ownId, 0b1100);
												/// sends the formed byte
												xBee_sendByte(x);
											}
                						/// slightly turns to the right
                						copro_setTargetRel(0, 4, 14);
                					}
                				/// if black line is not detected
                				if (current_floorR > 40 && current_floorL > 40)
                					{
                						/// set the speed to it's current value defined by the Speed variable
                						copro_setSpeed(Speed,Speed);
                					}
                				/// if both sensors simultaneously detect the black line and flag states that line shouldn't be ignored
                				if (current_floorR < 40 && current_floorL < 40 && ignore_line!=1)
                					{
                						/// move back a little
                						copro_setTargetRel(-10, -10, 14);
                					}
                				/// some delay to slow down any action and give some time to turn or roll back
                				delay(100);
            			}
    			/// end of the main program
                return 0;
            }
