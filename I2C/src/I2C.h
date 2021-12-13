/**
 * @file I2C.h
 *
 * @author ClefaMedia
 *
 * @version 1.0
 *
 * @copyright Copyright ClefaMedia 2021 
 * All Rights GNU GLP Licensed.
 *
 * @brief This library was created to use the I2C as
 * master using the hardware I2C interface.
 */

#ifndef _I2C_H                  // prevents duplicate
#define _I2C_H   1              // forward declarations

#include <avr/io.h>                 // requires AVR Input/Output
#include <inttypes.h>               // requires Inttypes

/** defines the data direction (reading from I2C device) */
#define I2C_READ        1
/** defines the data direction (writing to I2C device) */
#define I2C_WRITE       0

/** ===================================================
 * @brief function initialize the I2C-Bus
 * with setting the prescaler and clockspeed
 * 
 * @param scl_clk clockspeed of I2C-bus
 */
void I2C_init(uint32_t scl_clk);

/**  ===================================================
 * @brief function to start a communication 
 * on the I2C-Bus to a given address
 * 
 * @param addr slaveaddress
 * @return uint8_t success
 */
uint8_t I2C_start(uint8_t addr);

/** ===================================================
 * @brief function to start a communication 
 * with a loop to wait until the bus is free
 * 
 * @param addr slaveaddress
 * @return uint8_t success
 */
uint8_t I2C_startWait(uint8_t addr);

/** ===================================================
 * @brief function to send the start flag again
 * 
 * @param addr slaveaddress
 * @return uint8_t success
 */
uint8_t I2C_repStart(uint8_t addr);

/** ===================================================
 * @brief function to write one byte over the I2C-Bus
 * to a slave device
 * 
 * @param data 1 byte data which would be send
 * @return uint8_t success
 */
uint8_t I2C_write(uint8_t data);

/** ===================================================
 * @brief function to read from the bus
 * and send back an acknowledge 
 * or an not acknowledge
 * 
 * @param ack ack/nak
 * @return uint8_t success
 */
uint8_t I2C_read(uint8_t ack);

/** ===================================================
 * @brief function to stop the currently running 
 * communication on the I2C-Bus
 */
void I2C_stop();


#endif                  // end prevent duplicate forward
/* _I2C_H */            // declarations block

/**
 * This file is part of I2C
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
