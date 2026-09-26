#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <linux/i2c.h>
#include <i2c/smbus.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include "mpu6050.h"
// i2cdetect -l
//cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
//cmake --build build

int main(){
    int file;
    char filename[20];
    int adapter_nr = 1;
    int error = 0;

    snprintf(filename, 19 , "/dev/i2c-%d", adapter_nr);
    file = open(filename, O_RDWR);

    if (file < 0){
        perror("Failed to open i2c");
        return -1;
    }

    mpu6050_t mpu = {
        .addr = 0x68,
        .file = file,
        .accel_range = RANGE_2G,
        .gyro_range = RANGE_250DPS,
    };



    error = ioctl(file, I2C_SLAVE, mpu.addr);

    if(error < 0){
        perror("Failed connecting");
        close(file);
        return -2;
    }

    mpu6050_init(&mpu);

    uint8_t id = mpu6050_who_am_i();
    mpu6050_get_accel(&mpu);
    printf("Aceleraciones: %f, %f, %f", mpu.accel_x, mpu.accel_y, mpu.accel_z);
    printf("El ID del sensor es: 0x%02X\n", id);
    close(file);
    return 0;
}