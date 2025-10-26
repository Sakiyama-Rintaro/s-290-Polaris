#include"mbed.h"

Serial pc(USBTX,USBRX);
Serial android(p13,p14);

DigitalOut led1(LED1);

char data[11];

int main()
{
    pc.baud(9600);
    android.baud(9600);
    android.format(8,Serial::None,1);

    data[0] = 'A';

    data[1] = 'H';
    data[2] = 'E';
    data[3] = 'L';
    data[4] = 'L';
    data[5] = 'O';

    data[6] = 'W';
    data[7] = 'O';
    data[8] = 'R';
    data[9] = 'L';
    data[10] = 'D';

    while(1){
        wait(0.2);

        led1 = 1;

        for(int i = 0; i < 11; i++){
            android.putc(data[i]);
        }

        led1 =0;

        wait(0.9);

    }
}
