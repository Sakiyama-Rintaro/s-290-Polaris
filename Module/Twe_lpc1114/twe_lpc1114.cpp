#include"mbed.h"

#define addr1 0x01 //対気速度計の無線アドレス
#define addr2 0x02 //回転数計の無線アドレス
#define addr3 0x03 //姿勢角計の無線アドレス
#define addr4 0x04 //心拍計の無線アドレス(前部P)
#define addr5 0x05 //心拍計の無線アドレス(後部P)

#define ReceptLength 6 
#define SendLength 6

Serial main_twe(dp16,dp15);//tx: main_lpc1768 rx: twelite

DigitalOut led1(LED1);
DigitalOut led2(LED2);

Ticker ticker;

double airspeed = 0;

char rec_data[ReceptLength];
char send_data[6];

//プロトタイプ宣言
void recieve();
void check_addr();
void transmission();


/*main_lpc1768に送るデータ*/

// send_data[0] = 'A'    : 先頭文字
// send_data[1] = 'V'    : 対気速度データ
// send_data[2] = 'R'    : 回転数データ
// send_data[3] = 'P'    : 姿勢センサデータ
// send_data[4] = 'F'    : 心拍データ(前部P)
// send_data[5] = 'B'    : 心拍データ(後部P)
 

int main()
{
    led1 = 0;
    led2 = 0;

    main_twe.baud(115200);

    ticker.attach(&transmission,0.5);
    main_twe.attach(recieve,Serial::RxIrq);

    send_data[0] = 'A';

    while(1){

    }
}

void recieve()
{
    led1 = 0;

    if(main_twe.getc() == 0xA5){
        if(main_twe.getc() == 0x5A){

            led2 = 1;

            for(int i = 0; i < ReceptLength; i++){
                rec_data[i] = main_twe.getc();
            }

        }
    }

    check_addr();
}

void check_addr()
{
    /*-------------対気速度計---------------*/
    if(rec_data[2] == addr1){

        send_data[1] = rec_data[5];

    /*---------------回転数計---------------*/
    } else if(rec_data[2] == addr2){

        send_data[2] = rec_data[5];

    /*---------------姿勢角計---------------*/
    } else if(rec_data[2] == addr3){

        send_data[3] = rec_data[5];

    /*-------------心拍計(前部)-------------*/
    } else if(rec_data[2] == addr4){

        send_data[4] = rec_data[5];

    /*-------------心拍計(後部)-------------*/
    } else if(rec_data[2] == addr5){

        send_data[5] = rec_data[5];

    }
}

void transmission()
{
    led1 = 1;
    led2 = 0;

    for(int j = 0; j < SendLength; j++){
        main_twe.putc(send_data[j]);
    }
}
