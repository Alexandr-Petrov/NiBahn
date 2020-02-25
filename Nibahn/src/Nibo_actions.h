/**
*	@file Nibo_actions.h
*	@author Alexandr Petrov
*	@brief "Header file for the Nibo_action.c"
*	@version 07.12.2019
*/

#include"protokoll.h"
#include <nibo/uart0.h>

#ifndef ACTIONS_DEFINITION // Does not allows to read program twice
#define ACTIONS_DEFINITION

/**
 * @brief This function increases the speed of the Nibo to 7 if Nibo was not moving or sets it to 0 if Nibo was moving backward
 *
 * @param "Speed" is the current speed of Nibo
 *
 * @return increased Speed of Nibo
 */

short Speedup(short Speed);

/**
 * @brief This function decreases the speed of the Nibo to -7 if Nibo was not moving or sets it to 0 if Nibo was moving forward
 *
 * @param "Speed" is the current speed of Nibo
 *
 * @return decreased Speed of Nibo
 */

short Slowdown(short Speed);

/**
 * @brief this function changes the direction of the Nibo by turning 180 degrees right
 */

void Directionchange_right();

/**
 * @brief this function changes the direction of the Nibo by turning 180 degrees left
 */

void Directionchange_left();

/**
 * @brief this function turns nibo 90 degrees right
 */

void Turn_right();

/**
 * @brief this function turns nibo 90 degrees left
 */

void Turn_left();

/**
 * @brief his function forces reelection process to change the order of Nibo ID accordingly to the new direction
 * @param "ownId" is the current ID of Nibo
 * @param "reelection_delay" is the predefined reelection delay for all Nibos
 * @param "maxnibos" is the max number of Nibos in the chain
 *
 * @return 0b01 to make Nibo go through normal ID claim process
 */

u8_t Reelection_turn(u8_t ownId, short reelection_delay, u8_t maxnibos);

/**
 * @brief This function forces reelection process intended to be used to return excluded from the
 * chain Nibo back in the chain or to restore the structure of the chain if some Nibo is down
 *
 * @param "ownId" is the current ID of Nibo
 * @param "reelection_delay" is the predefined reelection delay for all Nibos
 * @param "maxnibos" is the max number of Nibos in the chain
 *
 * @return 0b01 to make Nibo go through the normal ID claim process
 */

u8_t Reelection_forced(u8_t ownId, short reelection_delay, u8_t maxnibos);

#endif /* ACTIONS_DEFINITION */

