#include"mbed.h"

Serial SD_gps(dp16,dp15);//tx: SDカード, main_lpc1768 rx: gpsモジュール

DigitalIn sign(dp4);//main_lpc1768 からの合図

int main()
{
    SD_gps.baud(9600);

    while(1){
        
        if(sign == 1){
            SD_gps.putc(SD_gps.getc());
        }
    }
}
