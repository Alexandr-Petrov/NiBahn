/**
 * @file drive.c
 * @brief Functions for Nibo's movement (driving and turning)
 *
 * @author Arina Lavrova
 * @version 11.2019
 */

#include "main.h"

/**
 * @brief
 *
 * Nibo goes forward
 */
void drive()
{
	copro_setSpeed(10, 10); ///Set same speed for the two motors. The wheels spin forward
}

/**
 * @brief
 *
 * Nibo turns left
 */
void turnLeft()
{
	copro_setTargetRel(-27, 27, 15); ///rotate 90 degrees left with 15 ticks/s
	copro_resetOdometry(0, 0);//Reset odometry values to specified values (0)
}

/**
 * @brief
 *
 * Nibo turns half left
 */
void turnHalfLeft()
{
	copro_setTargetRel(-13, 13, 15); ///rotate 45 degrees left with 15 ticks/s
	copro_resetOdometry(0, 0);
}

/**
 * @brief
 *
 * Nibo turns right
 */
void turnRight()
{
	copro_setTargetRel(27, -27, 15); ///rotate 90 degrees right with 15 ticks/s
	copro_resetOdometry(0, 0);
}

/**
 * @brief
 *
 * Nibo turns half right
 */
void turnHalfRight()
{
	copro_setTargetRel(13, -13, 15); ///rotate 45 degrees right with 15 ticks/s
	copro_resetOdometry(0, 0);
}

/**
 *  @brief
 *
 * Nibo goes back
 */
void goBack()
{
	copro_setSpeed(-10, -10); ///Set same speed for the two motors. The wheels spin back
	copro_resetOdometry(0, 0);
}

