#include"mbed.h"
#define ReceptLength 6//受信データ長(ヘッダ2つを除いた6つ)

Serial pc(USBTX,USBRX);
Serial twe(p9,p10);

char recept[ReceptLength]={};

int speed_2;
double speed_1;

void receive();
void call();

int main(){
    pc.baud(115200);
    twe.baud(115200);

    twe.attach(receive,Serial::RxIrq);

    while(1)
    {
    }
}

void receive()//無線データ受信用関数
{
    if(twe.getc()==0xA5){
        if(twe.getc()==0x5A){

            pc.printf("success!\r\n");

            for(int i=0;i<ReceptLength;i++){
                recept[i]=twe.getc();//ヘッダ以降のデータ格納
            }

        }
    }
    call();
}

void call(){//データ復元用関数
    if(recept[2]==0x01)//送信機ID
    {
        speed_2 = recept[5] - '0';//char型からint型に変換

        speed_1 = (float)speed_2;
        speed_1 = speed_1 / 10;

        pc.printf("Air speed:%.1lf m/s\r\n",speed_1);
    }
}
