// CSE325 - Project 4
// Authors: Ashish Datta <adatta4@asu.edu>, Shane Nelson <L 0 L >
// File: i2c.h
// ASU 
 
#ifndef I2C_H
#define I2C_H
#include "support_common.h"
#include "dtim.h"
typedef enum 
{
    i2c_mod_0 = 0,
    i2c_mod_1 = 1
} i2c_mod;
 
/*  The R/W bit is set for a read operation */
#define I2C_READ 1
/*   The R/W bit is cleared for a write operation */
#define I2C_WRITE 0


/*
    Busy-waits until the I2C bus is idle
*/
void i2c_acquire_bus(i2c_mod n);
/*
    Initializes the ColdFire I2C module per the pseudocode.
*/
void i2c_init(i2c_mod n, int frequency , int addr);
/*
    Enables the I2C module, makes the MCF52259 a slave-receiver, disables I2C interrupts,
    and disables the generation of repeated start bits.
*/
void i2c_reset();
/* 
     Receive n data bytes from an I2C peripheral per the pseudocode
*/
void i2c_rx(i2c_mod n, uint8 addr, int count, int delay_us, uint8 *data);
/* 
    Will receive one byte from an I2C peripheral per the pseudocode.
*/
uint8 i2c_rx_byte(i2c_mod n , int delay_us);
/*
    Send a stop bit
*/
void i2c_send_stop(i2c_mod n);
/*
    Will transmit n data bytes to an I2C peripheral
*/
void i2c_tx(i2c_mod n, uint8 addr, int count, int delay_us, uint8 *data);
/*  
    Will transmit the slave address and the read/write bit to an I2C peripheral.
*/
void i2c_tx_addr(i2c_mod n, uint8 addr, uint8 rw , int delay_us);
/* 
    Transmit one byte to an I2C peripheral
*/
void i2c_tx_byte(i2c_mod n, uint8 tx_byte, int delay_us);
/*
    Returns true if a transfer has completed and false if it has not. 
*/
int i2c_tx_complete(i2c_mod n);
 
 
 
 
 
 
#endif