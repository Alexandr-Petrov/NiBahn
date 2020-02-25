/**
*	@file Nibo_actions.c
*	@author Alexandr Petrov
*	@brief Set of functions used to control movements of Nibo
*	@version 07.12.2019
*/

#include <stdio.h>
#include "Nibo_actions.h"

short Speedup(short Speed)
{
	if(Speed < 0)
	{
		/// Set Speed to 0 effectively stopping Nibo
		Speed = 0;
	}
	else
	{
		/// Set Speed to 7
		Speed = 7;
	}
	return Speed;
}


short Slowdown(short Speed)
{
	/// if Speed was > 0
	if(Speed > 0)
	{
		/// Set Speed to 0 effectively stopping Nibo
		Speed = 0;
	}
	else
	{
		/// make Nibo go backwards
		Speed = -7;
	}
	return Speed;
}


u8_t Reelection_forced(u8_t ownId, short reelection_delay, u8_t maxnibos)
{
	/// if ID of the Nibo is 0 (nibo was not taking part in the election
	if (ownId == 0)
	{
		/// set ID as the max possible ID
		return maxnibos;
	}
	/// disables uart0 port so Nibo would not recieve bytes from other Nibos before delay ends
	uart0_disable();
	/// time of the delay depends on the ID of the Nibo. Nibos with lower IDs will be able to participate sooner
	/// in this function all Nibos will return to their previous Roles if no changes were made to the chain before reelection
	delay(reelection_delay*ownId);
	/// enables the uart0 port and now Nibo can recieve and send messages to other Nibos
	uart0_enable();
	return 0b01;
}

u8_t Reelection_turn(u8_t ownId, short reelection_delay, u8_t maxnibos)
{
	/// disables uart0 port so Nibo would not recieve bytes from other Nibos before delay ends
	uart0_disable();
	/// in this function all Nibos will get the opposite Roles if no changes were made to the chain before reelection because delay for the Nibos with lower IDs will be Higher
	delay(reelection_delay*(maxnibos-ownId));
	/// enables the uart0 port and now Nibo can recieve and send messages to other Nibos
	uart0_enable();
	return 0b01;
}

void Directionchange_right()
{
	copro_setTargetRel(-56, 56, 10);
	///delay allows to complete the operation without interruption
	delay(5000);
}


void Directionchange_left()
{
	copro_setTargetRel(56, -56, 10);
	///delay allows to complete the operation without interruption
	delay(5000);
}

void Turn_left()
{
	copro_setTargetRel(-28, 28, 10);
	///delay allows to complete the operation without interruption
	delay(5000);
}


void Turn_right()
{
	copro_setTargetRel(28, -28, 10);
	///delay allows to complete the operation without interruption
	delay(5000);
}
