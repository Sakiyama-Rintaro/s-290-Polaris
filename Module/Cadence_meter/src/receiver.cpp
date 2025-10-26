#include"mbed.h"
#define ReceptLength 6//受信データ長(ヘッダを除いた6つ)

Serial pc(USBTX,USBRX);
Serial twe(p9,p10);

char recept[ReceptLength] = {};

int rpm = 0;

void receive();
void call();

int main()
{
    pc.baud(115200);
    twe.baud(115200);

    twe.attach(receive,Serial::RxIrq);

    while(1){

    }
}

void receive()//無線データ受信用関数
{
    if(twe.getc() == 0xA5){
        if(twe.getc() == 0x5A){

            for(int i = 0; i < ReceptLength; i++){
                recept[i] = twe.getc();//ヘッダ以降のデータ格納
            }

        }
    }

    call();

}

void call()//データ復元用関数
{
    if(recept[2] == 0x02){//送信機ID
        rpm = recept[5] - '0';//char型からint型に変換
    }

    pc.printf("RPM: %d \r\n",rpm);
}
