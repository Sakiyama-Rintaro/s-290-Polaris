#include"mbed.h"
#include"TextOLED.h"

Serial pc(USBTX,USBRX);
TextOLED pilot_oled(p9,p10,p11,p12,p13,p14);// I/Oバッファ 接続 RS E DB4 DB5 DB6 DB7

int main(){
    int column=0;
    while(1){
        pilot_oled.locate(column,0);
        pilot_oled.printf("%d",column);

        wait(3);
        column++;
    }
}
