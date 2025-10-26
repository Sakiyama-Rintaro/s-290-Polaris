#include"mbed.h"

Serial twe(dp16,dp15);
InterruptIn rpmcount(dp25);

Timer t;
Ticker t1;

int counter = 0;
int rpm = 0;

double time_r = 0;

char send_data;

void rpm_count_f();
void rpm_cal();
void rpm_send();

int main()
{
    twe.baud(115200);

    t1.attach(&rpm_cal,0.5);
    t.start();

    rpmcount.rise(&rpm_count_f);

    while(1){

    }
}

void rpm_count_f()//フォトインタラプタ反応回数計測
{
    counter++;
}

void rpm_cal()
{
    time_r = t.read_ms();
    t.stop();
    // 反応回数 / スリット数 = counter / 50
    // 1秒あたりの回転数 = (反応回数 / スリット数) / 計測時間(s)
    // 1分あたりの回転数 = 1秒あたりの回転数 * 60 

    rpm = counter*60000/time_r/50;


    rpm_send();

    counter = 0;

    t.reset();
    t.start();
}

void rpm_send()//データ送信用関数
{
    send_data = rpm + '0';

    twe.putc(0xA5);//ヘッダ
    twe.putc(0x5A);//ヘッダ
    twe.putc(0x80);//送信するデータ長を指定するコマンド
    twe.putc(0x04);//送信するデータ長(4)

    twe.putc(0x00);//受信機(メイン)ID
    twe.putc(0x00);
    twe.putc(0x00);
    twe.putc(send_data);//送信したいデータ

    twe.putc(send_data);//チェックサム
}
