#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include "mpu6050.h"

const char *dev = "/dev/i2c-1";
int addr = 0x68;
mpu6050_t mpu;

int main(){

    int fd = open(dev, 0_RDWR);
    int res = 0;

    if(fd < 0){
        perror("open");
        return;
    }

    if(ioctl(fd, I2C_SLAVE, addr) < 0){
        perror("ioctl I2C_SLAVE");
        close(fd);
        return 1;
    }

    mpu6050_init(&mpu);

    // printf("Hello!");
    while(true){
        mpu6050_get_accel(mpu);
        printf("acel_x: %.2f, acel_y: %.2f, acel_z: %.2f\n", mpu.accel_x, mpu.accel_y, mpu.accel_z);
        usleep(1e6);
    }
    return 0;
}