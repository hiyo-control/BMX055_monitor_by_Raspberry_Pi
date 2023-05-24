#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "arduino_acceleration.h"

static void get_uart_data(accel_val* this);
static void calc_acceleration(accel_val* this);

void accel_construct(accel_val* this)
{
    this->fd = serialOpen("/dev/ttyACM0",115200);    
    
    wiringPiSetup();
    fflush(stdout);
    
    if(this->fd<0){
        printf("Can not open serial port\n");
        exit(0);
    }
    delay(500);
}

void get_acceleration(accel_val* this)
{
    get_uart_data(this);
    calc_acceleration(this);
}

void get_uart_data(accel_val* this)
{
    this->val = serialGetchar(this->fd);
    if(this->val != -1)
    {
        if(this->val == 'H')
        {
            this->switch_value = serialGetchar(this->fd);
            for (int i=0; i<6; i++)
            {
                this->data[i] = serialGetchar(this->fd);
            }
        }
        else
        {
        }
    }
    else
    {
        printf("no data\n");
        exit(0);
    }
}

void calc_acceleration(accel_val* this)
{
    if(this->switch_value == 1)
    {
        int xAccl_buf = ((this->data[1]&0xFF)<<4) + ((this->data[0]&0xF0)>>4);
        if(xAccl_buf  > 2047)
        {
            xAccl_buf  -= 4096;
        }
        else
        {
        }
        
        int yAccl_buf  = ((this->data[3]&0xFF)<<4) + ((this->data[2]&0xF0)>>4);
        if(yAccl_buf  > 2047)
        {
            yAccl_buf  -= 4096;
        }

        int zAccl_buf  = ((this->data[5]&0xFF)<<4) + ((this->data[4]&0xF0)>>4);
        if(zAccl_buf  > 2047)
        {
            zAccl_buf  -= 4096;
        }

        this->xAccl = (float)xAccl_buf * 0.00958;
        this->yAccl = (float)yAccl_buf * 0.00958;
        this->zAccl = (float)zAccl_buf * 0.00958;
    }
    else
    {
        this->xAccl = 0;
        this->yAccl = 0;
        this->zAccl = 0;
    }
}

void acceleration_show(accel_val* this)
{
    printf("xAccl = %.3f", this->xAccl);
    printf(", ");
    printf("yAccl = %.3f", this->yAccl);
    printf(", ");
    printf("zAccl = %.3f", this->zAccl);
    printf("\n");
}