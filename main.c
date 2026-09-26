#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "mpu6050.h"

const char *dev = "/dev/i2c-1";
int addr = 0x68;

int main(){

    int fd = open(dev, O_RDWR);
    int res = 0;

    mpu6050_t mpu = {
        .accel_range = RANGE_8G,
        .gyro_range = RANGE_250DPS,
        .addr = addr,
        .i2c = fd
    };


    if(fd < 0){
        perror("open");
        return -1;
    }

    res = ioctl(fd, I2C_SLAVE, addr);

    if(res){
        perror("ioctl I2C_SLAVE");
        close(fd);
        return -1;
    }

    mpu6050_init(&mpu);

    // printf("Hello!");
    // while(1){
        mpu6050_get_accel(&mpu);
        printf("acel_x: %.2f, acel_y: %.2f, acel_z: %.2f\n", mpu.accel_x, mpu.accel_y, mpu.accel_z);
    //     sleep(1);
    // }
    return 0;
}