/**
 @file: protokoll.h
 @author: Jan Bischof
 @date: 1.0
 @brief: Header file for protokoll.c
 * Created on: Nov 19, 2019
 */

#ifndef PROTOKOLL_H_
#define PROTOKOLL_H_

//////////////////////////////////////////////////////////////////////////////////////
// ---  Typedefs --- /////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////

typedef unsigned char   u8_t;
typedef signed char     i8_t;
typedef unsigned int    u16_t;
typedef signed int      i16_t;
typedef unsigned long   u32_t;
typedef signed long     i32_t;
typedef float           f32_t;

/**
 * @brief The function takes the receiver ID, the sender ID and the data and packs a byte from it.
 *
 * @param reciver Who should evaluate the data.
 * @param sender Who sent the data.
 * @param The user data consisting of function set and function.
 *
 * @return The ready-packed data is returned.
 */
u8_t buildSendData(u8_t reciver, u8_t sender, u8_t data);

/**
 * @brief The function extracts the transmitter from the transmission data.
 *
 * @param sendData The packed transmission data.
 *
 * @return The ID of the recipient.
 */
u8_t sendDataGetReciver(u8_t sendData);

/**
 * @brief Extracts the transmitter ID from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return The ID of the sender
 */
u8_t sendDataGetSender(u8_t sendData);
/**
 * @brief Extracts the complete payload data, consisting of function set and function, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the compiler payload data from the transmission data.
 */
u8_t sendDataGetData(u8_t sendData);

/**
 * @brief Extracts the function set from the payload data, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the function set.
 */
u8_t sendDataGetFunctionSet(u8_t sendData);

/**
 * @brief Extracts the function from the payload data, from the transmitted data.
 *
 * @param sendData The packed transmission data.
 *
 * @return Returns the function.
 */
u8_t sendDataGetFunction(u8_t sendData);

#endif /* PROTOKOLL_H_ */





