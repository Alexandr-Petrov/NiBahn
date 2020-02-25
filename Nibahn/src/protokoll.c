/**
 * @file: protokoll.c
 * @author: Jan Bischof
 * @date: 1.0
 * @brief: The file protokoll.c provides the formatting functions for the communication protocol between the nibos.
 * Created on: Nov 19, 2019
 */


/// libary for standard input and output operations of the Nibo2
#include<stdio.h>

/// includes xBee Communication
/// be aware to include it locally with ""
#include "xBee.h"

/// includes own header
#include"protokoll.h"

/**
 * @brief The function takes the receiver ID, the sender ID and the data and packs a byte from it.
 *
 * @param reciver Who should evaluate the data. Size 2 bits.
 * @param sender Who sent the data. Size 2 bits.
 * @param The user data consisting of function set and function. Size 4 bits.
 *
 * @return The ready-packed data is returned.
 */
u8_t buildSendData(u8_t reciver, u8_t sender, u8_t data){
	u8_t output = 0;
	output = output + reciver; ///2 bit
	output = output << 2; ///shift to make room
	output = output + sender; ///2 bit
	output = output << 4; ///shift to make room
	output = output + data; ///4 bit
	return output;
}

/**
 * @brief The function extracts the transmitter from the transmission data.
 *
 * @param sendData The packed transmission data.
 *
 * @return The ID of the recipient.
 */
u8_t sendDataGetReciver(u8_t sendData){
	sendData = sendData >> 6; ///push to delete the last 6 bits.
	return sendData;
}

/**
 * @brief Extracts the transmitter ID from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return The ID of the sender
 */
u8_t sendDataGetSender(u8_t sendData){
	sendData = sendData << 2; ///push to delete the first 2 bits.
	sendData = sendData >> 6; ///push to delete the last 4 bits.
	return sendData;
}

/**
 * @brief Extracts the complete payload data, consisting of function set and function, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the compiler payload data from the transmission data.
 */
u8_t sendDataGetData(u8_t sendData){
	sendData = sendData & 15; /// zero set of the first 4 bits
	return sendData;
}

/**
 * @brief Extracts the function set from the payload data, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the function set.
 */
u8_t sendDataGetFunctionSet(u8_t sendData){
	sendData = sendData & 15; ///zero set of the first 4 bits
	sendData = sendData >> 2; ///push to delete the last 2 bits.
	return sendData;
}

/**
 * @brief Extracts the function from the payload data, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the function.
 */
u8_t sendDataGetFunction(u8_t sendData){
	sendData = sendData & 3; ///zero set of the first 6 bits
	return sendData;
}
