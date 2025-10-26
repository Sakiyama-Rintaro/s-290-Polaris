/*---シリアル通信評価プログラム---*/
/*---高度---*/

#include"mbed.h"

Serial com(USBTX,USBRX);
Serial to_android(p28,p27);

DigitalOut led1(LED1);
DigitalOut led2(LED2);

AnalogIn alt(p20);

double altitude_raw = 0;//高度 生データ
int altitude_2 = 0;//高度を10倍したデータ

int altPacket[6];
int altCk;

int spdPacket[6]; 

void dataGenerate();
void dataShape();
void send();

int main(){
    to_android.baud(115200);

    while(1){
        led1 = 1;
        // A 0 0 0 X X
        // [0]識別子, [1~3]ペイロード, [4~5]チェックサム
        dataGenerate();
        wait(0.4);
        led1 = 0;
        wait(0.1);
    }
}

void dataGenerate()
{
    altitude_raw = alt.read()*3.3*1000/1.6/100;
    com.printf("Altitude: %.1lf m\r\n",altitude_raw);

    altitude_2 = altitude_raw * 10; 

    dataShape();   
}

void dataShape()
{


    //altPacket[0]識別子, altPacket[1~3]ペイロード. altPacket[4~5]チェックサム
    altPacket[0] = 'A';

    altPacket[3] = altitude_2 % 10;
    altitude_2 /= 10;
    altPacket[2] = altitude_2 % 10;
    altitude_2 /= 10;
    altPacket[1] = altitude_2 % 10;

    altCk = altPacket[1] + altPacket[2] + altPacket[3];
    altPacket[4] = altCk / 10;
    altPacket[5] = altCk % 10;

    /*--------*/

    spdPacket[0] = 'S';
    spdPacket[3] = 0;
    spdPacket[2] = 0;
    spdPacket[1] = 0;
    spdPacket[4] = 0;
    spdPacket[5] = 0;

    send();
}

void send()
{
    for(int i = 0; i < 6; i++){
        to_android.putc(spdPacket[i]);
    }

    for(int i = 0; i < 6; i++){
        to_android.putc(altPacket[i]);
    }
}
