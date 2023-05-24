#include <stdio.h>
#include <unistd.h>

#include "./include/arduino_acceleration.h"

int main(void)
{
    /* Initialization */
    accel_val accel_val;
    accel_construct(&accel_val);

    /* Show Acceleration */
    printf("Push Any Key\n");
    while(!getchar());

    while(1)
    {
        get_acceleration(&accel_val);
        acceleration_show(&accel_val);
    }
}